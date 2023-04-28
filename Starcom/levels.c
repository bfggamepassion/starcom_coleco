#include <coleco.h>

#define TILE_MOTHERSHIPV 0
#define TILE_MOTHERSHIPH 1
#define TILE_BLANK 2

const char* const levels_Pointer[] =
{
	level1,
	level2,
	level3,
	level4,
	level5,
	level6,
	level7,
	level9	
};


// OK
const char level9[] =
{
	TILE_MOTHERSHIPH,2+(1*2),5+(1*2),

	TILE_MOTHERSHIPV,5+(2*2),5+(2*2),
	TILE_MOTHERSHIPH,5+(2*2),5+(5*2),
	
	TILE_MOTHERSHIPV,2+(1*2),5+(6*2),
	TILE_MOTHERSHIPH,5+(6*2),5+(2*2),
	
	TILE_MOTHERSHIPV,5+(7*2),5+(1*2),
	TILE_MOTHERSHIPH,5+(6*2),5+(5*2),
	TILE_MOTHERSHIPV,5+(7*2),5+(6*2),
	-1	
};

/*
const char level8[] =
{
	TILE_MOTHERSHIPH,15,9,

	TILE_MOTHERSHIPV,18,11,
	TILE_MOTHERSHIPH,20,13,
	
	TILE_MOTHERSHIPV,12,11,
	TILE_MOTHERSHIPH,10,13,
	
	TILE_MOTHERSHIPV,10,16,
	TILE_MOTHERSHIPH,14,16,
	TILE_MOTHERSHIPV,18,16,
	-1	
};
*/

// OK
const char level7[] =
{
	TILE_MOTHERSHIPH,5+(3*2),0+(3*2),
	
	TILE_MOTHERSHIPV,5+(2*2),0+(4*2),
	TILE_MOTHERSHIPH,5+(5*2),0+(4*2), 
	
	TILE_MOTHERSHIPH,4+(1*2),0+(5*2),
	TILE_MOTHERSHIPV,8+(5*2),0+(5*2),
	
	TILE_MOTHERSHIPV,5+(2*2),0+(6*2),
	TILE_MOTHERSHIPH,5+(5*2),0+(6*2),
	
	TILE_MOTHERSHIPH,5+(3*2),1+(6*2),
	-1	
};

// OK
const char level6[] =
{
	TILE_MOTHERSHIPH,5+(2*2),2+(2*2),
	TILE_MOTHERSHIPV,9+(6*2),2+(2*2),//
	TILE_MOTHERSHIPH,5+(3*2),2+(4*2), 
	TILE_MOTHERSHIPV,8+(5*2),2+(4*2),
	
	TILE_MOTHERSHIPV,7+(4*2),2+(6*2),
	TILE_MOTHERSHIPH,7+(4*2),2+(7*2),
	TILE_MOTHERSHIPV,7+(4*2),2+(8*2),
	TILE_MOTHERSHIPH,7+(4*2),2+(9*2),
	-1	
};

// OK
const char level5[] =
{
	TILE_MOTHERSHIPH,5+(1*2),2+(4*2),
	TILE_MOTHERSHIPV,5+(2*2),2+(4*2),
	TILE_MOTHERSHIPH,5+(3*2),2+(4*2), 
	TILE_MOTHERSHIPV,5+(4*2),2+(4*2),
	
	TILE_MOTHERSHIPV,5+(3*2),2+(6*2),
	TILE_MOTHERSHIPH,5+(4*2),2+(6*2),
	TILE_MOTHERSHIPV,5+(5*2),2+(6*2),
	TILE_MOTHERSHIPH,5+(6*2),2+(6*2),
	-1	
};

// OK
const char level4[] =
{
	TILE_MOTHERSHIPH,5+(2*2),2+(2*2),

	TILE_MOTHERSHIPH,5+(4*2),2+(2*2),
	TILE_MOTHERSHIPH,5+(6*2),2+(2*2), //
	
	TILE_MOTHERSHIPV,5+(5*2),2+(4*2),
	TILE_MOTHERSHIPV,5+(3*2),2+(6*2),//
	
	TILE_MOTHERSHIPV,5+(2*2),2+(8*2),
	TILE_MOTHERSHIPH,5+(4*2),2+(8*2),
	TILE_MOTHERSHIPV,5+(6*2),2+(8*2),
	-1	
};

// OK
const char level3[] =
{
	TILE_MOTHERSHIPH,6+(3*2),2+(2*2),

	TILE_MOTHERSHIPH,5+(2*2),2+(4*2),
	TILE_MOTHERSHIPH,5+(5*2),2+(4*2), //
	
	TILE_MOTHERSHIPV,2+(1*2),2+(5*2),
	TILE_MOTHERSHIPV,6+(6*2),2+(5*2),//
	
	TILE_MOTHERSHIPV,5+(2*2),2+(7*2),
	TILE_MOTHERSHIPH,5+(3*2),2+(7*2),
	TILE_MOTHERSHIPV,7+(4*2),2+(7*2),
	-1	
};

// OK
const char level2[] =
{
	TILE_MOTHERSHIPH,5,10,
	TILE_MOTHERSHIPV,5,16,
	TILE_MOTHERSHIPH,20,13,
	TILE_MOTHERSHIPV,22,13,
	-1
};

// OK
const char level1[] =
{
	TILE_MOTHERSHIPH,12,9,
	TILE_MOTHERSHIPV,19,12,
	TILE_MOTHERSHIPH,13,16,
	-1
};


