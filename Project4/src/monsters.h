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

#endif