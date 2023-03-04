#include <iostream>
#include "common.h"
#include "advanturer.h"

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
	void enterEvent(Advanturer& vturer) {
		if (probality(10))
			vturer.setHp(10);
		vturer.setHp(5);
		std::cout << "Trigger Event: Heal the advanturer, current hp(" 
			<< vturer.getHp() << "/100)" << std::endl;
		Role monster("monster", 20, 5);
		std::cout << "Meet monster1, hp("
			<< monster.getHp() << "/20)" << std::endl;
	}
};