#include "teamstyle17.h"
#include "our_type.h"
#include <cstdlib>
#include <cmath>

void Evolution(Action & ret)
{
	int skillNodes = info->StatusNow->objects[0].ability;
	int dashLevel = info->StatusNow->objects[0].skill_level[DASH];
	int shortAttackLevel = info->StatusNow->objects[0].skill_level[SHORT_ATTACK];
	int myID = info->StatusNow->objects[0].id;
	if (skillNodes > pow(2, dashLevel) && dashLevel <= 3)
	{
		ret.skill_upgrade[0][DASH].toUpgradeSkill = true;
		ret.skill_upgrade[0][DASH].UserID = myID;
	}
	if (skillNodes > pow(2, shortAttackLevel))
	{
		ret.skill_upgrade[0][SHORT_ATTACK].toUpgradeSkill = true;
		ret.skill_upgrade[0][SHORT_ATTACK].UserID = myID;
	}
}
Position JudgeDirection(const Position & pos)
{
	
}
void Attack(Action & ret)
{

}