//
//actlib.h
//
// Some practical action mode.
// Functions here are precisely defined in actlib.cpp
//
#ifndef ACTLIB_H
#define ACTLIB_H

#include "teamstyle17.h"
#include "our_type.h"


// To judge whether a object is "friendly", i.e, is of type ENERGY or ADVANCED_ENERGY
bool isFriendlyObjType(const Object & obj);

// To judge whether a object is on boundary of the map.
bool isOnBoundary(const PlayerObject& playerObj, Axis::name axis);

// Return the weight of a object, according to its postion and type,
//	which is to be multiplied with the distance to player.
//double ObjDistWeight(const Object & obj);

// The closest "good type" object.
// If no such object exists, move towards the center of the map.
const Position ClosestObj(
	const PlayerObject& playerObj,
	const phase			NowPhase,
	const double		MaxSpeed = kMaxMoveSpeed
	);


bool Shake(
	Speed&				speed,
	const PlayerObject& playerObj,
	const double		MaxSpeed = kMaxMoveSpeed
	);


void ByPass(
	Speed&				speed,
	const PlayerObject& playerObj,
	const double		MaxSpeed = kMaxMoveSpeed);

// Modify the norm of speed to a given value(default Max Speed), while keeping its direction.
// Move along X axis positively with the given speed norm if the given speed vector = 0.
void ModifySpeedNorm(Speed& speed, const double speedNorm = kMaxMoveSpeed);
/*
void ReverseSpeedAlongAxis(Speed& speed, Axis::name axis);

// Reflect the speed upon meeting the boundary of the map.
void ReflectUponBoundary(const PlayerObject& playObj, Speed& speed);
*/

void Evolution(Action & ret);
Position JudgeDirection(const Position & pos);
void Attack(Action & ret);


#endif // !ACTLIB_H
