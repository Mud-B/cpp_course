#ifndef MONSTER_H
#define MONSTER_H
#include "common.h"

class Monster : public Role
{
public:
	Monster(int& index, int hp, int attack)
		: Role("Monster", hp, attack)
		, mIndex(index)
	{
		std::cout << "Meet Monster" << index << " ("
				  << hp << "/" << hp << "), dmage: " << attack << "\n";
	}
	
	int getIndex(){
		return mIndex;
	}


private:
	int mIndex;
};

class Boss : public Role
{
public:
	Boss()
		: Role("Boss", 40, 15)
	{
		std::cout << "Meet Boss" << " ("
				  << 40 << "/" << 40 << "), dmage: " << 15 << "\n";
	}
	void attackUp(){
		setAttack(1);
	}
	void reborn(){
		if(!mReborn){
			setHp(20);
			std::cout << "Boss heal 20hp, current hp(" 
				  << getHp() << "/40)" << std::endl;
			mReborn = true;
		}
	}

private:
	bool mReborn = false;
};

#endif