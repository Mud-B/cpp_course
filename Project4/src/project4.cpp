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
	int n=10;
	while(n--){
		switch(selectRoom()){
			case ROOMNAME::GENERALROOM:GeneralRoom g;g.enterEvent(&adv);g.fightEvent(&adv);g.reward(&adv);break;
		}
		sleep(1);
	}
	
//	while(!adv.isDead()){
//		switch(selectRoom()){
//			case ROOMNAME::GENERALROOM:GeneralRoom g;g.enterEvent(&adv);g.fightEvent(&adv);g.reward(&adv);break;
//		}
//	}
	std::cout << "Advanturer is dead\n";
}