#ifndef ADVANTURER_H
#define ADVANTURER_H
#include "common.h"

class Advanturer : public Role
{
public:
	Advanturer()
		: Role("Advanturer", 100, 10)
		, mExp(0)
		, mExpMax(10){}
	void heal() {
		int value = 100 - getHp();
		std::cout << "heal " << value << "hp\n";
		setHp(value);
	}
	void heal(int v) {
		int value = v + getHp();
		value >= 100 ? heal() : setHp(value);
		std::cout << "heal " << value << "hp\n";
	}
	void gainExp(int exp) {
		mExp += exp;
		if (mExp > mExpMax) {
			heal();
			mExp -= mExpMax;
		}
		std::cout << "Gain " << exp << " point of Exp, current exp("
			<< mExp << "/" << mExpMax << ")\n";
	}

private:
	int mExp;
	int mExpMax;
	unsigned char mBuffList[4] = {0};
};

#endif