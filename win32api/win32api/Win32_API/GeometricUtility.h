#pragma once


//라디안
#define PI 3.141592f
#define PI_2 (PI * 2)

namespace G_UTIL
{
	//두 점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	//두 점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
}