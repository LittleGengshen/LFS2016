#include "teamstyle17.h"
#include "our_type.h"
#include "actlib.h"
#include <cstdlib>
#include <ctime>
// Debug code begin
//#include <fstream>
//std::ofstream fileout;
// Debug code end

Information GlobalInfo;

Information* info = &GlobalInfo;
Position BossPos = { 10000,10000,10000 };
Position nowDest;

bool nowDestReached = true;
size_t notReachedTime = 0;


void AIMain() {
	srand((unsigned)time(NULL));
	info->MapNow = GetMap();
	info->StatusNow = GetStatus();

	PerformAction(Analysis());
}

void PerformAction(const Action & act) {
	// Upgrade Skills
	for (int i = 0; i < act.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
			if (act.skill_upgrade[i][j].toUpgradeSkill) {
				UpgradeSkill(act.skill_upgrade[i][j].UserID, (SkillType)j);
			}
		}
	}
	// Use Skills
	for (int i = 0; i < act.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
			if (act.skill_usage[i][j].toUseSkill) {
				switch ((SkillType)j) {
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
	// Move
	for (int i = 0; i < act.playerObjNum; i++) {
		Move(act.movement[i].UserID, act.movement[i].speed);
	}
}

Action Analysis(void)
{
	Action ret;
	ret.playerObjNum = 1;	//info->StatusNow->objects_number
	// Initialize
	for (int i = 0; i < ret.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
			ret.skill_upgrade[i][j].toUpgradeSkill = false;
			ret.skill_usage[i][j].toUseSkill = false;
		}
	}
	Position nowMovingToPos;
	if (notReachedTime > 150) {
		do {
			nowDest = { double(rand() % kMapSize),double(rand() % kMapSize),double(rand() % kMapSize) };
		} while (Distance(nowDest, BossPos) < 2500);
		nowDestReached = false;
		notReachedTime = 0;
	}
	else if (nowDestReached) {
		nowDest =
			ClosestObj(
				info->StatusNow->objects[0],
				info->MapNow->time < 1750 ? EARLY : LATE
				);
		nowDestReached = false;
		notReachedTime = 0;
	}
	else {
		notReachedTime++;
	}

	if (Distance(info->StatusNow->objects[0].pos, nowDest) < kMaxMoveSpeed + info->StatusNow->objects[0].radius) {
		nowDestReached = true;
	}

	ret.movement[0].speed = Displacement(info->StatusNow->objects[0].pos, nowDest);
	nowMovingToPos = JudgeDirection(nowDest);

	double DashSpeedBonus[kMaxSkillLevel + 1] = {
		0,20,40,60,80,100
	};
	double max_speed = kMaxMoveSpeed;
	if (info->StatusNow->objects[0].dash_time > 0) {
		max_speed += DashSpeedBonus[info->StatusNow->objects[0].skill_level[DASH]];
	}
	ret.movement[0].UserID = info->StatusNow->objects[0].id;
	if (isInDanger) {
		ret.movement[0].speed = Displacement(info->StatusNow->objects[0].pos, nowMovingToPos);
	}
	else {
		Shake(ret.movement[0].speed, info->StatusNow->objects[0], max_speed);
		ByPass(ret.movement[0].speed, info->StatusNow->objects[0], max_speed);
	}
	ModifySpeedNorm(ret.movement[0].speed, max_speed);

	Evolution(ret);
	Attack(ret);

	return ret;
}