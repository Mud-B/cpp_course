#include <iostream>
#include <climits>
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
		std::cout << "=======================================\n"
				  << "Get into camp" << std::endl;
	}
	void enterEvent(Advanturer* adv) {
		std::cout << "Trigger Event: Heal the advanturer, current hp(100/100)"
				  << std::endl;
		adv->heal();
		adv->dealBuff();
		std::cout << "current hp(" << adv->getHp() << "/100)\n" 
				  << "current buff: " << adv->getBuff() << "\n";
	}
};

class GeneralRoom : public RoomBase
{
public:
	GeneralRoom()
		: RoomBase(ROOMNAME::GENERALROOM) {
		std::cout << "=======================================\n"
				  << "Get into general room" << std::endl;
	}
	void enterEvent(Advanturer* adv) {
		adv->dealBuff();
		if (probality(10)){
			adv->heal(10);
			adv->setBuff(Buff::HEAL, adv->getBuff(Buff::HEAL)+2);
			std::cout << "Trigger Event: Heal the advanturer, current hp(" 
					  << adv->getHp() << "/100)" << std::endl;
		}
		std::cout << "current hp(" << adv->getHp() << "/100)\n" 
				  << "current buff: " << adv->getBuff() << "\n";
	}
	void fightEvent(Advanturer* adv){
		// Construct monster
		srand(time(0));
		int mTotalMonster = rand()%3 + 1;
		std::vector<Monster> monsters;
		for(int i=1; i<=mTotalMonster; i++){
			int hp = rand()%9 + 6;		//hp: 6~14
			int attack = rand()%5 + 3;	//attack: 3~7
			Monster monster(i, hp, attack);
			monsters.emplace_back(monster);
		}
		// Fighting
		std::cout << "Start fighting:\n";
		while(!adv->isDead() && mTotalMonster!=mDeadMonster){
			// select monster with highest attack
			int maxAttack = INT_MIN;
			int index = -1;
			for(auto monster : monsters){
				if(monster.isDead())continue;
				if(monster.getAttack() > maxAttack){
					maxAttack = monster.getAttack();
					index = monster.getIndex();
				}
			}
			if(index == -1)		// can't find monster
				break;
			auto& attackedMonster = monsters[index-1];
			// advanturer attack first
			attackedMonster.getHp() - adv->getAttack() > 0 ? 
					attackedMonster.setHp(-adv->getAttack()) :
					attackedMonster.setHp(-attackedMonster.getHp());
			std::cout << "Advanturer attack Monster" << attackedMonster.getIndex() << ", hit 10 dmage, "
					  << "Monster" << attackedMonster.getIndex() << "(" << attackedMonster.getHp() << "/"
					  << attackedMonster.getHpMax() << ")\n";
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
				std::cout << "Monster" << monster.getIndex() << " attack Advanturer, hit " 
						  << monster.getAttack() << " dmage, "
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

class TrapRoom : public RoomBase
{
public:
	TrapRoom()
		: RoomBase(ROOMNAME::TRAPROOM){
		std::cout << "======================================\n"
				  << "Get into trap room" << std::endl;
	}
	void enterEvent(Advanturer* adv) {
		adv->dealBuff();
		int lost = 0.1*adv->getHp();
		adv->heal(-lost);
		adv->setBuff(Buff::DMAGE, adv->getBuff(Buff::DMAGE)+5);
		std::cout << "Trigger Event: Advanturer lost " << lost << "hp, current hp(" 
				  << adv->getHp() << "/100)" << std::endl
				  << "current buff: " << adv->getBuff() << "\n";
	}
	void fightEvent(Advanturer* adv){
		// Construct monster
		srand(time(0));
		int mTotalMonster = 1;
		std::vector<Monster> monsters;
		for(int i=1; i<=mTotalMonster; i++){
			int hp = rand()%9 + 6;		//hp: 6~14
			int attack = rand()%5 + 3;	//attack: 3-7
			Monster monster(i, hp*2, attack*2);
			monsters.emplace_back(monster);
		}
		// Fighting
		std::cout << "Start fighting:\n";
		while(!adv->isDead() && mTotalMonster!=mDeadMonster){
			// select monster with highest attack
			int maxAttack = INT_MIN;
			int index = -1;
			for(auto monster : monsters){
				if(monster.isDead())continue;
				if(monster.getAttack() > maxAttack){
					maxAttack = monster.getAttack();
					index = monster.getIndex();
				}
			}
			if(index == -1)		// can't find monster
				break;
			auto& attackedMonster = monsters[index-1];
			// advanturer attack first
			attackedMonster.getHp() - adv->getAttack() > 0 ? 
					attackedMonster.setHp(-adv->getAttack()) :
					attackedMonster.setHp(-attackedMonster.getHp());
			std::cout << "Advanturer attack Monster" << attackedMonster.getIndex() << ", hit 10 dmage, "
					  << "Monster" << attackedMonster.getIndex() << "(" << attackedMonster.getHp() << "/"
					  << attackedMonster.getHpMax() << ")\n";
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
				std::cout << "Monster" << monster.getIndex() << " attack Advanturer, hit " 
						  << monster.getAttack() << " dmage, "
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
