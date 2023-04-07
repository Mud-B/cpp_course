#ifndef MONSTER_H
#define MONSTER_H
#include "common.h"

class Monster : public Role
{
public:
	Monster(int& index)
		: Role("Monster", 20, 5)
		, mIndex(index)
	{
		std::cout << "Meet Monster" << index << " (20/20)\n";
	}
	
	int getIndex(){
		return mIndex;
	}


private:
	int mIndex;
};

#endif