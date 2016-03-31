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
	int dashLevel = info->StatusNow->objects[0].skill_level[DASH];
	int shortAttackLevel = info->StatusNow->objects[0].skill_level[SHORT_ATTACK];
	int myID = info->StatusNow->objects[0].id;
	int objnum = info->MapNow->objects_number;
	int my01ID = info->StatusNow->team_id;
	double myradius = info->StatusNow->objects[0].radius;
	Position mypos = info->StatusNow->objects[0].pos;
	for (int i = 0; i < objnum; i++)
	{
		if (info->MapNow->objects[i].team_id == my01ID^1)
		{
			int otherRealID = info->MapNow->objects[i].id;
			Position otherpos = info->MapNow->objects[i].pos;
			double otherradius = info->MapNow->objects[i].radius;
			if (Distance(mypos, otherpos) - myradius - otherradius < kShortAttackRange[shortAttackLevel])
			{
				ret.skill_usage[0][SHORT_ATTACK].TargetID = otherRealID;
				ret.skill_usage[0][SHORT_ATTACK].UserID = myID;
				ret.skill_usage[0][SHORT_ATTACK].toUseSkill = true;
			}
		}
	}

}