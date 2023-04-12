#include "advanturer.h"
#include "room.h"
#include <unistd.h>		//sleep() needed

ROOMNAME selectRoom() {
    srand(time(0));
    double prob = rand()%100 + 1;	//0~100
    if(prob <= 10) return ROOMNAME::CAMP;
	else if(prob <= 65) return ROOMNAME::GENERALROOM;
	else if(prob <= 80) return ROOMNAME::TRAPROOM;
	else if(prob <= 90) return ROOMNAME::BOSSROOM;
	else return ROOMNAME::WEAPONROOM;
}

int main() {
	Advanturer adv;
	History hi;
	while(!adv.isDead()){
		switch(selectRoom()){
			case ROOMNAME::CAMP:{
				hi.add(ROOMNAME::CAMP);
				Camp c; 
				c.enterEvent(&adv); 
				break;
			} 
			case ROOMNAME::GENERALROOM:{
				hi.add(ROOMNAME::GENERALROOM);
				GeneralRoom g;
				g.enterEvent(&adv);
				if(adv.isDead())break;
				g.fightEvent(&adv);
				if(adv.isDead())break;
				g.reward(&adv);
				break;
			}
			case ROOMNAME::TRAPROOM:{
				hi.add(ROOMNAME::TRAPROOM);
				TrapRoom t;
				t.enterEvent(&adv);
				if(adv.isDead())break;
				t.fightEvent(&adv);
				if(adv.isDead())break;
				t.reward(&adv);
				break;
			}
			case ROOMNAME::BOSSROOM:{
				hi.add(ROOMNAME::BOSSROOM);
				BossRoom b;
				b.enterEvent(&adv);
				if(adv.isDead())break;
				b.fightEvent(&adv);
				if(adv.isDead())break;
				b.reward(&adv);
				break;
			}
			case ROOMNAME::WEAPONROOM:{
				hi.add(ROOMNAME::WEAPONROOM);
				break;
			}
		}
		sleep(1);
	}
	hi.printRecord();
}