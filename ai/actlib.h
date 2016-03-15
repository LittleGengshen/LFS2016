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

// Move towards the closest friendly object.
// If no such object exists, move towards the center of the map.
// Not completed yet.
void MoveToClosest(
	const PlayerObject& playerObj,
	const Object*		ObjInMap,
	const int			ObjNumInMap,
	MoveUsage&			MovementToSet
	);

// Modify the norm of speed to a given value, while keeping its direction.
// Move towards the center of the map if the given speed vector = 0.
// Not completed yet.
void ModifySpeedNorm(Speed& speed, const double speedNorm);

#endif // !ACTLIB_H
