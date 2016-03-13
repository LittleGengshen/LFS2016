#include "teamstyle17.h"
#include<stdlib.h>

enum SkillOperation {
	Upgrade, nop
};

struct SkillMgr {
	SkillOperation op;
	SkillType SkillToManage;
};

struct Action {
	SkillMgr SkillChange;
	SkillType SkillToUse;
	Speed SpeedToUse;
};

struct Information {
	const Map* MapNow;
	const Status* StatusNow;
};

void PerformAct(const int user_id, const Action act);

void AIMain() {
	Action Analysis(const Information);
	const Map* map = GetMap();
	const Status* status = GetStatus();
	const Information info = { map,status };
	PerformAct(status->objects[0].id, Analysis(info));
}

void PerformAct(const int user_id, const Action act) {
	//To be completed...
	switch (act.SkillChange.op) {
	case Upgrade:
		UpgradeSkill(user_id, act.SkillChange.SkillToManage);
		break;
	case nop:
	default:
		break;
	}
}
