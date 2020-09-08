#include "setDefine.h"
#include "GeometricUtility.h"

float G_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x*x + y*y);
}

float G_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;


	float distance = sqrtf(x*x + y*y);
	float angle = acos(x / distance);
	
	if (endY > startY) angle = PI_2 - angle;
	
	return angle;
}
