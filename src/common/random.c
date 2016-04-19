#include <stdint.h>
#include <stdlib.h>


//! \brief random seed
static uint16_t s_hwRandomSeed = 0xAA55;
static uint8_t s_chRandomTable[] =
{
	0x12,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
	0xF1,0xE2,0xD3,0xC4,0xB5,0xA6,0x97,0x88
};


/*! \note set random generator seed
*  \param hwSeed random seed
*  \return none
*/
void set_random_seed( uint16_t hwSeed )
{
	s_hwRandomSeed ^= hwSeed;
}

/*! \note get a random integer
*  \param none
*  \return random integer value
*/
uint16_t get_random_u16( void )
{
	uint16_t *phwResult = (uint16_t *)&s_chRandomTable[(s_hwRandomSeed & 0x0E)];

	*phwResult += s_hwRandomSeed;
	s_hwRandomSeed ^= *phwResult;

	return *phwResult;
}

/*! \note get a random byte
*  \param none
*  \return random integer value
*/
uint8_t get_random_u8( void )
{
	return get_random_u16();
}