#include "teamstyle17.h"
#include "our_type.h"
#include "actlib.h"
//#include <iostream>


void AIMain() {
	Information info;
	info.MapNow = GetMap();
	info.StatusNow = GetStatus();
	PerformAction(Analysis(info));
}

void PerformAction(const Action & act) {
	//Upgrade Skills
	for (int i = 0; i < act.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
			if (act.skill_upgrade[i][j].toUpgradeSkill) {
				UpgradeSkill(act.skill_upgrade[i][j].UserID, (SkillType)i);
			}
		}
	}
	//Use Skills
	for (int i = 0; i < act.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
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
	for (int i = 0; i < act.playerObjNum; i++) {
		Move(act.movement[i].UserID, act.movement[i].speed);
	}
}

Action Analysis(const Information & info)
{
	Action ret;
	ret.playerObjNum = 1;//info.StatusNow->objects_number;
	//Initialize
	for (int i = 0; i < ret.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
			ret.skill_upgrade[i][j].toUpgradeSkill = false;
			ret.skill_usage[i][j].toUseSkill = false;
		}
	}
	MoveToClosest(
		info.StatusNow->objects[0],
		info.MapNow->objects,
		info.MapNow->objects_number,
		ret.movement[0]
		);
	return ret;
}