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
	return (obj.type == ENERGY) || (obj.type == ADVANCED_ENERGY);
}

bool isOnBoundary(const PlayerObject& playerObj, Axis::name axis)
{	
	double delta1, delta2;
	const double tolerance = 3 * kMaxMoveSpeed;	// Min distance to be judged as being on boundary
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
	return (delta1 < tolerance) || (delta2 < tolerance);
}

/*double ObjDistWeight(const Object & obj) {
	return 1.;
}*/

const Position ClosestObj(
	const PlayerObject& playerObj,
	const Object*		ObjInMap,
	const int			ObjNumInMap,
	const phase			NowPhase,
	const double		MaxSpeed = kMaxMoveSpeed
	)
{
	double shortest_dist = MAX_DISTANCE;
	int shortest_index = -1;
	
	if (NowPhase == EARLY) {
		const double oneStepDist = MaxSpeed + playerObj.radius;
		for (int i = 0; i < ObjNumInMap; i++) {
			if (ObjInMap[i].type == ADVANCED_ENERGY) {
				double dist_now = Distance(playerObj.pos, ObjInMap[i].pos);
				if (dist_now < shortest_dist) {
					shortest_index = i;
					if (dist_now < oneStepDist) {
						break;
					}
					shortest_dist = dist_now;
				}
			}
		}
	}
	if (-1 != shortest_index) {
		return ObjInMap[shortest_index].pos;
	}
	else {
		int weight[8] = { 0 };
		Position centroid[8] = { 0 };
		Position displacementNow;
		for (int i = 0; i < ObjNumInMap; i++) {
			int j = 0;
			if (isFriendlyObjType(ObjInMap[i])) {
				displacementNow = Displacement(playerObj.pos, ObjInMap[i].pos);
				if (displacementNow.x >= 0) {
					j |= 1;
				}
				if (displacementNow.y >= 0) {
					j |= 2;
				}
				if (displacementNow.z >= 0) {
					j |= 4;
				}
				weight[j]++;
				centroid[j] = Displacement(Scale(-1, ObjInMap[i].pos), centroid[j]);
			}
		}
		double max_weight = weight[0];
		int max_weight_index = 0;
		for (int i = 1; i < 8; i++) {
			if (weight[i] > max_weight) {
				max_weight_index = i;
				max_weight = weight[i];
			}
		}
		//Position delta[8] = {
		//	{-1,-1,-1},
		//	{1,-1,-1},
		//	{-1,1,-1},
		//	{}
		//}
		return Scale((double)1 / weight[max_weight_index], centroid[max_weight_index]);
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
	for (int i = 0; i < Axis::kAxisNum; i++) {
		if (isOnBoundary(playerObj, (Axis::name)i)) {
			ReverseSpeedAlongAxis(speed, (Axis::name)i);
		}
	}
}