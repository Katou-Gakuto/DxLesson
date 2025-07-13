#pragma once

typedef struct CoordinateXY {
	float x;
	float y;
}COORDINATE_X_Y;

typedef struct CoordinateXY_Int {
	int x;
	int y;
}COORDINATE_X_Y_INT;

extern COORDINATE_X_Y XYGet(float x, float y);
extern COORDINATE_X_Y_INT XYGet_Int(int x, int y);

extern COORDINATE_X_Y IntXY_Change_FloatXY(COORDINATE_X_Y_INT intXY);	// intŒ^‚ÌxyÀ•W‚ğfloatŒ^‚Ìxy‚É•ÏŠ·
extern COORDINATE_X_Y_INT FloatXY_Change_IntXY(COORDINATE_X_Y floatXY);	// floatŒ^‚ÌxyÀ•W‚ğintŒ^‚Ìxy‚É•ÏŠ·