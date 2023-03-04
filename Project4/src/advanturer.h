#ifndef ADVANTURER_H
#define ADVANTURER_H
#include "common.h"

class Advanturer : public Role
{
public:
	Advanturer()
		: Role("advanturer", 100, 10)
		, mExp(0)
		, mExpMax(10){}
	Advanturer(std::string name="advanturer", int hp=100, int attack=10)
		: Role(name, hp, attack)
		, mExp(0)
		, mExpMax(10){}
	Advanturer(std::string name="advanturer", int hp=100, int attack=10, int max=10)
		: Role(name, hp, attack)
		, mExp(0)
		, mExpMax(max){}
	void heal() {
		int value = 100 - getHp();
		setHp(value);
	}
	void gainExp(int exp) {
		mExp += exp;
		if (mExp > mExpMax) {
			heal();
			mExp -= mExpMax;
		}
	}

private:
	int mExp;
	int mExpMax;
};

#endif