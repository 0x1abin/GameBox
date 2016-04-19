/*!
 * @file button_grinern.h
 * @brief KeyHandler offering easy access to keys/button.
 *
 * Here's what this module does and does not:
 * - It does configure a given set of keys to trigger on certain events.
 * - It does offer the opportunity to add further keys than the six represented
 *   on the Z-Wave ZDP03A development platform.
 * - It does offer the opportunity to add further key events if you're willing
 *   to code a little.
 * - It does NOT trigger on several keys simultaneously due to the chip and
 *   hardware design.
 *
 * @date 10/12/2014
 * @author Christian Salmony Olsen (COLSEN)
 *
 * Last changed by: $Author: $
 * Revision:        $Revision: $
 * Last changed:    $Date: $
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <ZW_typedefs.h>
//#include <ZW_pindefs.h>

/*!
 * Holds the key names and the max number of keys. Add more keys before
 * NUMBER_OF_KEYS, if necessary.
 */
typedef enum
{
  KEY01,         //!< KEY01
  KEY02,         //!< KEY02
  KEY03,         //!< KEY03
  KEY04,         //!< KEY04
  KEY05,         //!< KEY05
  KEY06,         //!< KEY06
  NUMBER_OF_KEYS//!< NUMBER_OF_KEYS
}
KEY_NAME_T;

/*!
 * Holds the key events and the number of events. Add more events before
 * NUMBER_OF_KEY_EVENTS, if necessary.
 */
typedef enum
{
  KEY_DOWN,           //!< KEY_DOWN
  KEY_UP,             //!< KEY_UP
  KEY_PRESS,          //!< KEY_PRESS
  KEY_HOLD,           //!< KEY_HOLD
  KEY_TRIPLE_PRESS,   //!< KEY_TRIPLE_PRESS
  KEY_HOLD_10SEC,     //!< KEY_HOLD_10SEC
  NUMBER_OF_KEY_EVENTS//!< NUMBER_OF_KEY_EVENTS
}
KEY_EVENT_T;

/*!
 * @brief Register a callback function for a certain key event.
 * @param keyName   The name of the key in correspondence to the enumeration.
 * @param keyPin    Physical pin of the chip.
 * @param keyEvent  Key event in correspondence to the enumeration.
 * @param pCallback Pointer to callback function.
 */
void KeyHandlerRegisterCallback(KEY_NAME_T keyName, BYTE keyPin, KEY_EVENT_T keyEvent, VOID_CALLBACKFUNC(pCallback)(void));

/*!
 * @brief Initializes the button handler.
 */
void KeyHandlerInit(void);

#endif /* BUTTON_DRIVER_H_ */
