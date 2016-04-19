/*!
 * @file button_grinern.c
 * @brief KeyHandler is nice.
 *
 * Ideas for future version:
 * - Configure repeat/non-repeat for hold event.
 * - Configure hold time.
 * - Implement events based on multiple buttons (requires new chip with multiple
 *   interrupts).
 *    # Store active keys in a bit field parsed together with events to each of
 *      the callback functions. It makes the module more flexible for the user.
 *
 * @date 10/12/2014
 * @author Christian Salmony Olsen (COLSEN)
 *
 * Last changed by: $Author: $
 * Revision:        $Revision: $
 * Last changed:    $Date: $
 */

#include <ZW050x.h>
#include <ZW_typedefs.h>
#include <ZW_pindefs.h>
#include <ZW_uart_api.h>
#include <ZW_mem_api.h>
#include <ZW_timer_api.h>
#include <misc.h>

#include "button_driver.h"
#include "interrupt_driver.h"

#ifdef ZW_DEBUG_KEY_HANDLER
#define ZW_DEBUG_MYPRODUCT_SEND_BYTE(data) ZW_DEBUG_SEND_BYTE(data)
#define ZW_DEBUG_MYPRODUCT_SEND_STR(STR) ZW_DEBUG_SEND_STR(STR)
#define ZW_DEBUG_MYPRODUCT_SEND_NUM(data)  ZW_DEBUG_SEND_NUM(data)
#define ZW_DEBUG_MYPRODUCT_SEND_WORD_NUM(data) ZW_DEBUG_SEND_WORD_NUM(data)
#define ZW_DEBUG_MYPRODUCT_SEND_NL()  ZW_DEBUG_SEND_NL()
#else
#define ZW_DEBUG_MYPRODUCT_SEND_BYTE(data)
#define ZW_DEBUG_MYPRODUCT_SEND_STR(STR)
#define ZW_DEBUG_MYPRODUCT_SEND_NUM(data)
#define ZW_DEBUG_MYPRODUCT_SEND_WORD_NUM(data)
#define ZW_DEBUG_MYPRODUCT_SEND_NL()
#endif

#define WHICH_BUTTON_RESET          (0xFF)

// Thresholds in milliseconds
#define KEY_HOLD_THRESHOLD          (1000)
#define KEY_TRIPLE_PRESS_THRESHOLD  (1000)

typedef struct
{
  BYTE keyPin;
  VOID_CALLBACKFUNC(pEventCallbacks[NUMBER_OF_KEY_EVENTS])(KEY_NAME_T, KEY_EVENT_T, BYTE);
}
KEY_LIST_T;

static KEY_LIST_T keyList[NUMBER_OF_KEYS];

static BYTE whichButton;
static BOOL fKeyHoldThresholdExceeded;
static BYTE pressCount;
static BYTE holdCount;

void ZCB_EdgeCall(BYTE bLevelValue);
static void GetActiveButton();
static void ClearActiveButton(void);
void ZCB_KeyHeldTimerCallback(void);
void ZCB_KeyTriplePressTimerCallback(void);

void KeyHandlerInit(void)
{
  memset((BYTE *)keyList, NULL, (NUMBER_OF_KEYS * sizeof(KEY_LIST_T)));
  /*
  BYTE keyCount;
  BYTE eventCount;
  for (keyCount = 0; keyCount < NUMBER_OF_KEYS; keyCount++)
  {
    for (eventCount = 0; eventCount < NUMBER_OF_KEY_EVENTS; eventCount++)
    {
      keyList[keyCount].pEventCallbacks[eventCount] = NULL;
    }
  }
  */

  whichButton = WHICH_BUTTON_RESET;
  fKeyHoldThresholdExceeded = FALSE;
  pressCount = 0;
  holdCount = 0;

  /*
   * Initialize the interrupt module with a pointer to a function to call on
   * every edge change.
   */
  interruptInit(ZCB_EdgeCall);
}

void KeyHandlerRegisterCallback(KEY_NAME_T keyName, BYTE keyPin, KEY_EVENT_T keyEvent, VOID_CALLBACKFUNC(pCallback)(void))
{
  keyList[keyName].keyPin = keyPin;
  keyList[keyName].pEventCallbacks[keyEvent] = pCallback;
}

/**
 * @brief Function pointer for KEIL.
 */
code const void (code * ZCB_EdgeCall_p)(BYTE bLevelValue) = &ZCB_EdgeCall;
/**
 * @brief Called on every edge change.
 *
 * This function defines the different events and calls registered functions.
 *
 * @param[in] bLevelValue 1 for high, 0 for low.
 */
void
ZCB_EdgeCall(BYTE bLevelValue)
{
  static BYTE keyHeldTimerHandle;
  static BYTE keyTriplePressTimerHandle;

  if (0 == bLevelValue)
  {
    // Falling edge

    /*
     * Detect button only on falling edge. It makes no sense to check on rising
     * edge due to the hardware design.
     */
    GetActiveButton();

    ZW_DEBUG_MYPRODUCT_SEND_STR("S");
    ZW_DEBUG_MYPRODUCT_SEND_NUM(whichButton);

    if (NULL != keyList[whichButton].pEventCallbacks[KEY_DOWN])
    {
      (keyList[whichButton].pEventCallbacks[KEY_DOWN])(whichButton, KEY_DOWN);
    }
    ZW_DEBUG_MYPRODUCT_SEND_STR("DOWN");

    // Start a timer to detect whether the key is held.
    fKeyHoldThresholdExceeded = FALSE;
    keyHeldTimerHandle = TimerStart(ZCB_KeyHeldTimerCallback, (KEY_HOLD_THRESHOLD / 10), -1);
  }
  else
  {
    // Rising edge
    ZW_DEBUG_MYPRODUCT_SEND_STR("S");
    ZW_DEBUG_MYPRODUCT_SEND_NUM(whichButton);

    if (NULL != keyList[whichButton].pEventCallbacks[KEY_UP])
    {
      (keyList[whichButton].pEventCallbacks[KEY_UP])(whichButton, KEY_UP);
    }

    // When key goes up, cancel the held timer.
    TimerCancel(keyHeldTimerHandle);

    if (FALSE == fKeyHoldThresholdExceeded)
    {
      // The key was pressed.
      ZW_DEBUG_MYPRODUCT_SEND_STR("PRESS");

      if (0 == pressCount)
      {
        // Start a timer to detect if the triple press threshold is exceeded.
        keyTriplePressTimerHandle = TimerStart(ZCB_KeyTriplePressTimerCallback, (KEY_TRIPLE_PRESS_THRESHOLD / 10), 1);
      }

      pressCount++;
      if (3 == pressCount)
      {
        // Key has been pressed three times.
        TimerCancel(keyTriplePressTimerHandle);
        pressCount = 0;

        ZW_DEBUG_MYPRODUCT_SEND_STR("TRIPLE");

        if (NULL != keyList[whichButton].pEventCallbacks[KEY_TRIPLE_PRESS])
        {
          (keyList[whichButton].pEventCallbacks[KEY_TRIPLE_PRESS])(whichButton, KEY_TRIPLE_PRESS);
        }
      }

      if (NULL != keyList[whichButton].pEventCallbacks[KEY_PRESS])
      {
        (keyList[whichButton].pEventCallbacks[KEY_PRESS])(whichButton, KEY_PRESS);
      }
    }
    else
    {
      // The key was held.
      holdCount = 0;
    }
    ZW_DEBUG_MYPRODUCT_SEND_STR("UP");
    ClearActiveButton();
  }
}

/*!
 * @brief Detects the active button.
 *
 * TODO: Run through the index of keys instead of using hardcoded stuff.
 */
static void
GetActiveButton(void)
{
  /*
   * We're making the assumption that no key will never be pressed at the exact
   * same time (by a human). Thereby it's up to the application developer to
   * decide what should happen on "multiple" key presses.
   */
#ifdef NOT_USED
  BYTE keyIndex;
  for (keyIndex = 0; keyIndex < NUMBER_OF_KEYS; keyIndex++)
  {
    BYTE pin_hej = keyList[keyIndex].keyPin;
    if (!(PIN_GET(pin_hej)))
    {
      whichButton = keyIndex;
      return;
    }
  }
#endif
  if (!PIN_GET(P34))
  {
    whichButton = KEY06;
  }
  else if (!PIN_GET(P21))
  {
    whichButton = KEY05;
  }
  else if (!PIN_GET(P22))
  {
    whichButton = KEY04;
  }
  else if (!PIN_GET(P23))
  {
    whichButton = KEY03;
  }
  else if (!PIN_GET(P36))
  {
    whichButton = KEY02;
  }
  else if (!PIN_GET(P24))
  {
    whichButton = KEY01;
  }
}

/*!
 * @brief Clears the active button.
 */
static void
ClearActiveButton(void)
{
  whichButton = WHICH_BUTTON_RESET;
}

/**
 * @brief Called when the key held threshold is exceeded.
 */
PCB(ZCB_KeyHeldTimerCallback)(void)
{
  fKeyHoldThresholdExceeded = TRUE;

  // The key was held.
  ZW_DEBUG_MYPRODUCT_SEND_STR("HELD");

  if (NULL != keyList[whichButton].pEventCallbacks[KEY_HOLD])
  {
    holdCount++;
    (keyList[whichButton].pEventCallbacks[KEY_HOLD])(whichButton, KEY_HOLD, holdCount);
  }
}

/**
 * @brief Resets triple press counter.
 */
PCB(ZCB_KeyTriplePressTimerCallback)(void)
{
  pressCount = 0;
  ZW_DEBUG_MYPRODUCT_SEND_STR("RESET");
}
