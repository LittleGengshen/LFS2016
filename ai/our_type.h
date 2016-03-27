//
//our_type.h
//
// Define some data types needed in ai.cpp, 
//  which deal with information and reaction.
//
#ifndef OUR_TYPE_H
#define OUR_TYPE_H

#include "teamstyle17.h"

// Axis in map coordinate.
namespace Axis {
	enum name {
		X, Y, Z, kAxisNum
	};
}

struct UpgradeUsage {
	bool toUpgradeSkill;	// Whether to upgrade the skill or not
	int UserID;
};

struct SkillUsage {
	bool toUseSkill;	// Whether to use the skill or not
	int UserID;
	int TargetID;
};

struct MoveUsage {
	Speed speed;
	int UserID;
};	// Usage of Move: Speed to move, the object ID to move

// Action to take, which is passed to perform
struct Action {
	int playerObjNum;
	UpgradeUsage skill_upgrade[kMaxPlayerObjectNumber][kSkillTypes];
	SkillUsage skill_usage[kMaxPlayerObjectNumber][kSkillTypes];
	MoveUsage movement[kMaxPlayerObjectNumber];
};
void PerformAction(const Action & act);


// Information detected, which is passed to analyse
struct Information {
	const Map* MapNow;
	const Status* StatusNow;
};
Action Analysis(const Information & info);	// Return the action to perform


// Grocery
enum phase {
	EARLY, LATE
};

#endif // !OUR_TYPE_H

