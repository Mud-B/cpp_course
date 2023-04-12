#ifndef ADVANTURER_H
#define ADVANTURER_H
#include "common.h"

enum Buff{
	HEAL = 0, 
	DMAGE = 1, 
	CLEAR = 2, 
	RECORD = 3
};

class Advanturer : public Role
{
public:
	Advanturer()
		: Role("Advanturer", 100, 10)
		, mExp(0)
		, mExpMax(10){}
	void heal() {
		int value = 100 - getHp();
		setHp(value);
	}
	void heal(int v) {
		int value = v + getHp();
		value >= 100 ? heal() : setHp(v);
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
	int getBuff(Buff b){
		return mBuffList[b];
	}
	std::string getBuff(){
		std::string s="";
		for(auto buff : mBuffList)
			s += std::to_string(buff)+" ";
		return s;
	}
	void setBuff(Buff b, int value){
		mBuffList[b] = value;
	}
	void dealBuff(){
		if(mBuffList[Buff::HEAL]){
			heal(5);
			mBuffList[Buff::HEAL]--;
			std::cout << "Buff-1: Advanturer heal 5hp, current hp(" 
					  << getHp() << "/100)" << std::endl;
		}
		if(mBuffList[Buff::DMAGE]){
			setHp(-2);
			mBuffList[Buff::DMAGE]--;
			std::cout << "Buff-2: Advanturer lost 2hp, current hp(" 
					  << getHp() << "/100)" << std::endl;
		}
		if(mBuffList[Buff::CLEAR]){
			mBuffList[Buff::DMAGE] = 0;
			mBuffList[Buff::CLEAR] = 0;
			std::cout << "Buff-3: Continuous damage effect removed\n";
		}
	}

private:
	int mExp;
	int mExpMax;
	std::vector<int> mBuffList = {0,0,0,0};
};

#endif