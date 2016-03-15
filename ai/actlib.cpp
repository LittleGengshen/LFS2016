//
//actlib.cpp
//
// See actlib.h
//
#include "teamstyle17.h"
#include "our_type.h"
#include <cstdlib>
#include <cmath>

#define INF_SIMAL 0.01
#define ABS(x) ((x)>0?(x):-(x))
#define MAX_DISTANCE (kMapSize*2) //MAX_DISTANCE should be greater than any possible distance in the map


bool isFriendlyObjType(const Object & obj) {
	return (obj.type != PLAYER) && (obj.type != DEVOUR) && (obj.type != BOSS);
}

void MoveToClosest(
	const PlayerObject& playerObj,
	const Object*		ObjInMap,
	const int			ObjNumInMap,
	MoveUsage &			MovementToSet
	)
{
	double shortest_dist = MAX_DISTANCE;
	int shortest_index = -1;
	MovementToSet.UserID = playerObj.id;

	for (int i = 0; i < ObjNumInMap; i++) {
		double dist_now = Distance(playerObj.pos, ObjInMap[i].pos);
		if (isFriendlyObjType(ObjInMap[i]) &&
			(dist_now < shortest_dist)) {
			shortest_dist = dist_now;
			shortest_index = i;
		}
	}
	if (-1 != shortest_index) {
		MovementToSet.speed = Displacement(playerObj.pos, ObjInMap[shortest_index].pos);
	}
	else {
		// To be completed...
	}
}

void ModifySpeedNorm(Speed& speed, const double speedNorm) {
	double NormNow = Norm(speed);
	if (ABS(NormNow) >= INF_SIMAL) {
		speed.x *= (speedNorm / NormNow);
		speed.y *= (speedNorm / NormNow);
		speed.z *= (speedNorm / NormNow);
	}
	else {
		// To be completed...
	}
}