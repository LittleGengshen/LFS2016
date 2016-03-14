#include "teamstyle17.h"
#include<stdlib.h>


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
	UpgradeUsage skill_upgrade[kSkillTypes];
	SkillUsage skill_usage[kSkillTypes];
	MoveUsage movement;
};

void PerformAct(const Action& act);

struct Information {
	const Map* MapNow;
	const Status* StatusNow;
};

Action Analysis(const Information& info);	//To analyse the given information and return the action to perform


void AIMain() {
	Information info;
	info.MapNow = GetMap();
	info.StatusNow = GetStatus();
	PerformAct(Analysis(info));
}

void PerformAct(const Action& act) {

	//Upgrade Skills
	for (size_t i = 0; i < kSkillTypes; i++) {
		if (act.skill_upgrade[i].toUpgradeSkill) {
			UpgradeSkill(act.skill_upgrade[i].UserID, (SkillType)i);
		}
	}
	
	//Use skills
	for (size_t i = 0; i < kSkillTypes; i++) {
		if (act.skill_usage[i].toUseSkill) {
			switch ((SkillType)i) {
			case LONG_ATTACK:
				LongAttack(act.skill_usage[i].UserID, act.skill_usage[i].TargetID);
				break;
			case SHORT_ATTACK:
				ShortAttack(act.skill_usage[i].UserID);
				break;
			case SHIELD:
				Shield(act.skill_usage[i].UserID);
				break;
			case DASH:
				Dash(act.skill_usage[i].UserID);
				break;
			case HEALTH_UP:
				HealthUp(act.skill_usage[i].UserID);
				break;
			default:
				break;
			}
		}
	}

	//Move
	Move(act.movement.UserID, act.movement.speed);
}
