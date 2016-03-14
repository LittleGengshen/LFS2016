#include "teamstyle17.h"
#include <stdlib.h>


struct UpgradeUsage {
	bool toUpgradeSkill;	//Whether to upgrade the skill or not
	int UserID;
};

struct SkillUsage {
	bool toUseSkill;	//Whether to use the skill or not
	int UserID;
	int TargetID;
};

struct MoveUsage {
	Speed speed;
	int UserID;
};	//Usage of Move: Speed to move, the object ID to move

struct Action {
	int playerObjNum;
	UpgradeUsage skill_upgrade[kMaxPlayerObjectNumber][kSkillTypes];
	SkillUsage skill_usage[kMaxPlayerObjectNumber][kSkillTypes];
	MoveUsage movement[kMaxPlayerObjectNumber];
};

void PerformAct(const Action & act);

struct Information {
	const Map* MapNow;
	const Status* StatusNow;
};

Action Analysis(const Information & info);	//To analyse the given information and return the action to perform


void AIMain() {
	Information info;
	info.MapNow = GetMap();
	info.StatusNow = GetStatus();
	PerformAct(Analysis(info));
}

void PerformAct(const Action & act) {
	//Upgrade Skills
	for (size_t i = 0; i < act.playerObjNum; i++) {
		for (size_t j = 0; j < kSkillTypes; j++) {
			if (act.skill_upgrade[i][j].toUpgradeSkill) {
				UpgradeSkill(act.skill_upgrade[i][j].UserID, (SkillType)i);
			}
		}
	}
	//Use Skills
	for (size_t i = 0; i < act.playerObjNum; i++) {
		for (size_t j = 0; j < kSkillTypes; j++) {
			if (act.skill_usage[i][j].toUseSkill) {
				switch ((SkillType)i) {
				case LONG_ATTACK:
					LongAttack(act.skill_usage[i][j].UserID, act.skill_usage[i][j].TargetID);
					break;
				case SHORT_ATTACK:
					ShortAttack(act.skill_usage[i][j].UserID);
					break;
				case SHIELD:
					Shield(act.skill_usage[i][j].UserID);
					break;
				case DASH:
					Dash(act.skill_usage[i][j].UserID);
					break;
				case HEALTH_UP:
					HealthUp(act.skill_usage[i][j].UserID);
					break;
				default:
					break;
				}
			}
		}
	}
	//Move
	for (size_t i = 0; i < act.playerObjNum; i++) {
		Move(act.movement[i].UserID, act.movement[i].speed);
	}
}

Action Analysis(const Information & info)
{
	Action ret;
	ret.playerObjNum = 1; //info.StatusNow->objects_number;
	for (int i = 0; i < ret.playerObjNum; i++)
		for (int j = 0; j < kSkillTypes; j++)
			ret.skill_upgrade[i][j].toUpgradeSkill = false;
	for (int i = 0; i < ret.playerObjNum; i++)
		for (int j = 0; j < kSkillTypes; j++)
			ret.skill_usage[i][j].toUseSkill = false;
	double shortest_dist = Distance(info.StatusNow->objects[0].pos, info.MapNow->objects[0].pos);;
	int shortest_index = 0;
	for (int i = 0; i < info.MapNow->objects_number; i++)
	{
		double dist_now = Distance(info.StatusNow->objects[0].pos, info.MapNow->objects[i].pos);
		if((info.MapNow->objects[i].type != BOSS) && dist_now < shortest_dist) {
			shortest_dist = dist_now;
			shortest_index = i;
		}
	}
	ret.movement[0].speed = Displacement(info.StatusNow->objects[0].pos, info.MapNow->objects[shortest_index].pos);
	ret.movement[0].UserID = info.StatusNow->objects[0].id;
	return Action();
}
