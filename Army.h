#pragma once

#define DAMAGE_OF_POWDER 70
#define BLOOD_OF_POWDER 70
#define ARMOR_OF_POWDER 20
#define MUNITION_OF_POWDER 0 // Useless

#define DAMAGE_OF_HOP 40
#define BLOOD_OF_HOP 80
#define ARMOR_OF_HOP 80

#define DAMAGE_OF_SWORD 25
#define BLOOD_OF_SWORD 100
#define ARMOR_OF_SWORD 100

#define DAMAGE_OF_SPEAR 55
#define BLOOD_OF_SPEAR 80
#define ARMOR_OF_SPEAR 60

#define VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS 80

enum ArmyType { powder, hop, sword, spear, unknown };

class Army
{
protected:
	int damage;
	int blood;
	int armor;

	ArmyType type;

public:
	Army();
	Army(const int&, const int&, const int&, const ArmyType&);

	int getDamage();
	int getBlood();
	int getArmor();

	void armorIcreasing(const int&);
	void armorReducing(int&);
	void bloodReducing(int&);
	void beAttacked(int&); // Every soldier gets attacked by reducing their armor first, then blood will be reduced

	ArmyType getType();
};