#include "setDefine.h"
#include "collisionFucntion.h"

bool collisionFucntion::collision(HDC hdc, RECT &player, RECT &monster)
{

	RECT tempRect3;
	if (IntersectRect(&tempRect3, &player, &monster))
	{
		return true;
	}

	return false;
}
