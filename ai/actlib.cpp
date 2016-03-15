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
#define MAX_DISTANCE (kMapSize*2) // MAX_DISTANCE should be greater than any possible distance in the map


bool isFriendlyObjType(const Object & obj) {
	return (obj.type != PLAYER) && (obj.type != DEVOUR) && (obj.type != BOSS);
}

bool OnBoundary(const PlayerObject & playerObj, Axis::name axis)
{	
	double delta1, delta2;
	switch (axis) {
	case Axis::X :
		delta1 = playerObj.pos.x - playerObj.radius;
		delta2 = kMapSize - playerObj.pos.x - playerObj.radius;
		break;
	case Axis::Y :
		delta1 = playerObj.pos.y - playerObj.radius;
		delta2 = kMapSize - playerObj.pos.y - playerObj.radius;
		break;
	case Axis::Z :
		delta1 = playerObj.pos.z - playerObj.radius;
		delta2 = kMapSize - playerObj.pos.z - playerObj.radius;
		break;
	default:
		delta1 = MAX_DISTANCE;
		delta2 = MAX_DISTANCE;
		break;
	}
	return (delta1 < 2 * kMaxMoveSpeed) || (delta2 < 2 * kMaxMoveSpeed);
}

void MoveToClosest(
	const PlayerObject& playerObj,
	const Object*		ObjInMap,
	const int			ObjNumInMap,
	MoveUsage&			MovementToSet,
	const double		MaxSpeed = kMaxMoveSpeed
	)
{
	double shortest_dist = MAX_DISTANCE;
	int shortest_index = -1;
	MovementToSet.UserID = playerObj.id;

	for (int i = 0; i < ObjNumInMap; i++) {
		double dist_now = Distance(playerObj.pos, ObjInMap[i].pos);
		if (isFriendlyObjType(ObjInMap[i])) {
			if (dist_now < shortest_dist) {
				shortest_index = i;
				if (dist_now < MaxSpeed) {
					break;
				}
				shortest_dist = dist_now;
		}
		}
	}
	if (-1 != shortest_index) {
		MovementToSet.speed = Displacement(playerObj.pos, ObjInMap[shortest_index].pos);
	}
	else {
		Position middle = { kMapSize / 2,kMapSize / 2,kMapSize / 2 };
		MovementToSet.speed = Displacement(playerObj.pos, middle);
	}
}

void ModifySpeedNorm(Speed& speed, const double speedNorm = kMaxMoveSpeed)
{
	double NormNow = Norm(speed);

	if (ABS(NormNow) >= INF_SIMAL) {
		speed.x *= (speedNorm / NormNow);
		speed.y *= (speedNorm / NormNow);
		speed.z *= (speedNorm / NormNow);
	}
	else {
		speed.x = speedNorm;
		speed.y = 0;
		speed.z = 0;
	}
}

void ReverseSpeedAlongAxis(Speed& speed, Axis::name axis) {
	switch (axis) {
	case Axis::X :
		speed.x = -speed.x; break;
	case Axis::Y :
		speed.y = -speed.y; break;
	case Axis::Z :
		speed.z = -speed.z; break;
	default:
		break;
	}
}

void ReflectUponBoundary(const PlayerObject& playerObj, Speed& speed) {
	for (size_t i = 0; i < Axis::kAxisNum; i++) {
		if (OnBoundary(playerObj, (Axis::name)i)) {
			ReverseSpeedAlongAxis(speed, (Axis::name)i);
		}
	}
}