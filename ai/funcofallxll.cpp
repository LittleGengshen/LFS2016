#include "teamstyle17.h"
#include "our_type.h"
#include <cstdlib>
#include <cmath>
#define DANDER_HEALTH_RATIO 1.5 
#define ATTACK_HEALTH_RATIO 1.5
#define DANGER_DISTANCE 800



int skillNodes ;
int dashLevel ;
int shortAttackLevel ;
int myID ;
int objnum ;
int my01ID ;
double myradius ;
Position mypos ;
int myHealth ;
int otherRealID ;
Position otherpos ;
double otherradius;
bool found;
bool isInDanger = false;
	
	

Position Escape(const Position & pos)
{
	double enemyDistance = Distance(mypos, otherpos) - myradius - otherradius;
	if (enemyDistance < DANGER_DISTANCE)
	{
		isInDanger = true;
	}

	Position out;
	out = Displacement(otherpos, mypos);
	for (int i = 0; i < objnum; i++)
	{
		if (info->MapNow->objects[i].type == ADVANCED_ENERGY)
		{
			Position energypos = info->MapNow->objects[i].pos;
			if (DotProduct(energypos, out) > 0)
			{
				return energypos;
			}

		}
	}

	return out;
}



void Evolution(Action & ret)
{
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

	skillNodes = info->StatusNow->objects[0].ability;
	dashLevel = info->StatusNow->objects[0].skill_level[DASH];
	shortAttackLevel = info->StatusNow->objects[0].skill_level[SHORT_ATTACK];
	myID = info->StatusNow->objects[0].id;
	objnum = info->MapNow->objects_number;
	my01ID = info->StatusNow->team_id;
	myradius = info->StatusNow->objects[0].radius;
	mypos = info->StatusNow->objects[0].pos;
	myHealth = info->StatusNow->objects[0].health;
	found = false;

	for (int i = 0; i < objnum; i++)
	{
		if (info->MapNow->objects[i].team_id == (my01ID^1))
		{
			otherRealID = info->MapNow->objects[i].id;
			otherpos = info->MapNow->objects[i].pos;
			otherradius = info->MapNow->objects[i].radius;
			isInDanger = false;
			found = true;
		}
	}

	if (found)
	{
		double otherhealth = pow(otherradius / 100., 3);
		if (otherhealth > myHealth * DANDER_HEALTH_RATIO)
		{
			return Escape(pos);
		}	

		if (otherhealth * ATTACK_HEALTH_RATIO < myHealth)
		{
			return otherpos;
		}		

	}
	
	return pos;
}



void Attack(Action & ret)
{
	if (found)
	{
		if (Distance(mypos, otherpos) - myradius - otherradius < kShortAttackRange[shortAttackLevel]
			)	//&& pow(otherradius/100, 3) * ATTACK_HEALTH_RATIO < myHealth) 
		{
				ret.skill_usage[0][SHORT_ATTACK].TargetID = otherRealID;
				ret.skill_usage[0][SHORT_ATTACK].UserID = myID;
				ret.skill_usage[0][SHORT_ATTACK].toUseSkill = true;
		}
	
	}

}