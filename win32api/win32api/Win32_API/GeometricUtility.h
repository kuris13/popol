#pragma once


//����
#define PI 3.141592f
#define PI_2 (PI * 2)

namespace G_UTIL
{
	//�� �� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	//�� �� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);
}