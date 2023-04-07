#include <iostream>
#include "common.h"
#include "advanturer.h"
#include "monsters.h"

auto probality = [](double v) -> bool{
	srand(time(0));
	int prob = rand()%100 + 1;
	return prob <= v;
};
	
class Camp : public RoomBase
{
public:
	Camp()
		: RoomBase(ROOMNAME::CAMP){
		std::cout << "Get into camp" << std::endl;
	}
	void enterEvent(Advanturer& advanturer) {
		std::cout << "Trigger Event: Heal the advanturer, current hp(100/100)"
				  << std::endl;
		advanturer.heal();
	}
};

class GeneralRoom : public RoomBase
{
public:
	GeneralRoom()
		: RoomBase(ROOMNAME::GENERALROOM) {
		std::cout << "Get into general room" << std::endl;
	}
	void enterEvent(Advanturer* adv) {
		if (probality(10)){
			adv->heal(10);
			std::cout << "Trigger Event: Heal the advanturer, current hp(" 
					  << adv->getHp() << "/100)" << std::endl;
		}
	}
	void fightEvent(Advanturer* adv){
		// Construct monster
		srand(time(0));
		int mTotalMonster = rand()%3 + 1;
		std::vector<Monster> monsters;
		for(int i=1; i<=mTotalMonster; i++){
			Monster monster(i);
			monsters.emplace_back(monster);
		}
		// Fighting
		std::cout << "Start fighting:\n";
		while(!adv->isDead() && mTotalMonster!=mDeadMonster){
			// advanturer attack first
			auto& attackedMonster = monsters[mDeadMonster];
			attackedMonster.getHp() - adv->getAttack() > 0 ? 
					attackedMonster.setHp(-adv->getAttack()) :
					attackedMonster.setHp(-attackedMonster.getHp());
			std::cout << "Advanturer attack Monster" << attackedMonster.getIndex() << ", hit 10 dmage, "
					  << "Monster" << attackedMonster.getIndex() << "(" << attackedMonster.getHp() << "/20)\n";
			if(attackedMonster.isDead()){
				std::cout << "Monster" << attackedMonster.getIndex() << " is dead\n";
				mDeadMonster++;
			}
			// monsters attack
			for(auto monster : monsters){
				if(monster.isDead())continue;
				adv->getHp() - monster.getAttack() > 0 ?
					adv->setHp(-monster.getAttack()) :
					adv->setHp(-adv->getHp());
				std::cout << "Monster" << monster.getIndex() << " attack Advanturer, hit 5 dmage, "
						  << "Advanturer(" << adv->getHp() << "/100)\n";
				if(adv->isDead()) break;
			}
		}
	}
	void reward(Advanturer* adv){
		adv->gainExp(mDeadMonster);
	}
private:
	unsigned char mTotalMonster = 0;
	unsigned char mDeadMonster = 0;
};
