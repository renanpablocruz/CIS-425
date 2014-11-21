#include <math.h>
#include "Utils.h"

dir getDirForTank(float x1, float y1, float x2, float y2)
{
	dir ans;
	float ang = atan2(y2 - y1, x2 - x1); // [-PI, PI]

	if (ang < 3 * PI / 4 && ang > PI / 4) ans = UP;
	else if (ang < PI / 4 && ang > -PI / 4) ans = RIGHT;
	else if (ang < -PI / 4 && ang > -3 * PI / 4) ans = DOWN;
	else ans = LEFT;

	return ans;
}


dir getDirForBullet(float x1, float y1, float x2, float y2)
{
	dir ans;
	float ang = atan2(y2 - y1, x2 - x1); // [-PI, PI]
	if (ang <= PI && ang > PI / 2) ans = SO;
	else if (ang <= PI / 2 && ang > 0) ans = SE;
	else if (ang <= 0 && ang > - PI / 2) ans = NE;
	else ans = NO;

	return ans;
}