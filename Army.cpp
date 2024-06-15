#include "Army.h"

Army::Army() : damage(0), blood(0), armor(0), type(unknown)
{

}

Army::Army(const int& damage, const int& blood, const int& armor, const ArmyType& type) : damage(damage), blood(blood), armor(armor), type(type)
{

}

int Army::getDamage()
{
	return damage;
}

int Army::getBlood()
{
	return blood;
}

int Army::getArmor()
{
	return armor;
}

void Army::armorIcreasing(const int& armorIncreasing)
{
	armor += armorIncreasing;
}

void Army::armorReducing(int& damageTaken)
{
	if (armor >= damageTaken)
	{
		armor -= damageTaken;
		damageTaken = 0;
	}
	else
	{
		damageTaken -= armor;
		armor = 0;
	}
}

void Army::bloodReducing(int& damageTaken)
{
	if (blood >= damageTaken)
	{
		blood -= damageTaken;
		damageTaken = 0;
	}
	else
	{
		damageTaken -= blood;
		blood = 0;
	}
}

void Army::beAttacked(int& damageTaken)
{
	armorReducing(damageTaken);
	bloodReducing(damageTaken);
}

ArmyType Army::getType()
{
    return type;
}
