#include "teamstyle17.h"
#include "our_type.h"
#include "actlib.h"
// Debug code begin
//#include <fstream>
//std::ofstream fileout;
// Debug code end

Information* info;

Position BossPos;
Position nowDest;
bool nowDestReached = true;

void AIMain() {
	info->MapNow = GetMap();
	info->StatusNow = GetStatus();

	PerformAction(Analysis());
}

void PerformAction(const Action & act) {
	// Upgrade Skills
	for (int i = 0; i < act.playerObjNum; i++) {
		for (int j = 0; j < kSkillTypes; j++) {
			if (act.skill_upgrade[i][j].toUpgradeSkill) {
				UpgradeSkill(act.skill_upgrade[i][j].UserID, (SkillType)i);
			}
		}
	}
	// Use Skills
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
	Position closest;
	if (nowDestReached) {
		closest =
			ClosestObj(
				info->StatusNow->objects[0],
				info->MapNow->time < 1000 ? EARLY : LATE
				);
	}
	else {
		closest = nowDest;
	}
	if (Distance(info->StatusNow->objects[0].pos, closest) < kMaxMoveSpeed + info->StatusNow->objects[0].radius) {
		nowDestReached = true;
	}
	ret.movement[0].UserID = info->StatusNow->objects[0].id;
	ret.movement[0].speed = Displacement(info->StatusNow->objects[0].pos, closest);
	ModifySpeedNorm(ret.movement[0].speed);
	Evolution(ret);
	Attack(ret);
	//ReflectUponBoundary(info->StatusNow->objects[0], ret.movement[0].speed);
	// Debug code begin
	//fileout.open("data.txt", std::ios::app);
	//fileout << "AI " << info->StatusNow->team_id << std::endl;
	//fileout << "X: " << ret.movement[0].speed.x << std::endl;
	//fileout << "Y: " << ret.movement[0].speed.y << std::endl;
	//fileout << "Z: " << ret.movement[0].speed.z << std::endl;
	//fileout.close();
	// Debug code end
	return ret;
}