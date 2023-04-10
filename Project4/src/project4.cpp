#include "advanturer.h"
#include "room.h"
#include <memory>
#include<unistd.h>

ROOMNAME selectRoom() {
    srand(time(0));
    double prob = rand()%100 + 1;
    if(prob <= 10) return ROOMNAME::CAMP;
	else if(prob <= 65) return ROOMNAME::GENERALROOM;
	else if(prob <= 80) return ROOMNAME::TRAPROOM;
	else if(prob <= 90) return ROOMNAME::BOSSROOM;
	else if(prob <= 100) return ROOMNAME::WEAPONROOM;
}

int main() {
	Advanturer adv;	
	while(!adv.isDead()){
		switch(selectRoom()){
			case ROOMNAME::CAMP:{
				Camp c; 
				c.enterEvent(&adv); 
				break;
			} 
			case ROOMNAME::GENERALROOM:{
				GeneralRoom g;
				g.enterEvent(&adv);
				if(adv.isDead())break;
				g.fightEvent(&adv);
				if(adv.isDead())break;
				g.reward(&adv);
				break;
			}
			case ROOMNAME::TRAPROOM:{
				TrapRoom t;
				t.enterEvent(&adv);
				if(adv.isDead())break;
				t.fightEvent(&adv);
				if(adv.isDead())break;
				t.reward(&adv);
				break;
			}
		}
		sleep(1);
	}
	std::cout << "Advanturer is dead\n";
}