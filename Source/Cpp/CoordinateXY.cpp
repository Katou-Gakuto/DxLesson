#include "../Header/CoordinateXY.h"

/*
* @fn 
* @drief XYÀ•W‚Éfloat“ñ‚Â‚ğ•ÏŠ·
*/
COORDINATE_X_Y XYGet(float x, float y)
{
	COORDINATE_X_Y set;
	set.x = x;
	set.y = y;
	return set;
}

/*
* @fn
* @drief XYÀ•W‚Éint“ñ‚Â‚ğ•ÏŠ·
*/
COORDINATE_X_Y_INT XYGet_Int(int x, int y)
{
	COORDINATE_X_Y_INT set;
	set.x = x;
	set.y = y;
	return set;
}

/*
* @fn IntXY_Change_FloatXY
* @drief intŒ^‚ÌxyÀ•W‚ğfloatŒ^‚Ìxy‚É•ÏŠ·
*/
COORDINATE_X_Y IntXY_Change_FloatXY(COORDINATE_X_Y_INT intXY)
{
	return	XYGet(intXY.x, intXY.y);
}

/*
* @fn FloatXY_Change_IntXY
* @drief floatŒ^‚ÌxyÀ•W‚ğintŒ^‚Ìxy‚É•ÏŠ·
*/
COORDINATE_X_Y_INT FloatXY_Change_IntXY(COORDINATE_X_Y floatXY)
{
	return XYGet_Int(floatXY.x, floatXY.y);
}