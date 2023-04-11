#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>

class Role
{
public:
    Role() = delete;
    Role(std::string name, int hp, int attack)
        : mName(name)
        , mHp(hp)
        , mHpMax(hp)
        , mAttack(attack){}
//    ~Role();
    int getHp(){
        return mHp;
    }
    void setHp(int hp){
        mHp += hp;
    }
	int getHpMax(){
        return mHpMax;
    }
    bool isDead(){
        return mHp <= 0;
    }
    int getAttack(){
        return mAttack;
    }
    void setAttack(int a){
        mAttack += a;
    }

private:
    std::string mName;
    int mHp, mHpMax;
    int mAttack;
};

enum ROOMNAME{
    CAMP,
    GENERALROOM,
    TRAPROOM,
    BOSSROOM,
    WEAPONROOM
};

class RoomBase
{
public:
    RoomBase();
    RoomBase(ROOMNAME name)
        : mName(name){}
//     ~RoomBase();
    void enterEvent();
    void fightEvent();
    void reward();

private:
    ROOMNAME mName;
};

class History{
public:
    History() = default;
//    virtual ~History();
    void add(ROOMNAME room){
        mRecord[room]++;
    }
    void printRecord(){
		std::cout << std::setfill('-') << std::setw(60) <<"\n"
				  << "Advanturer is dead, Pass Total " << getTotal() << " rooms, ";
        for(auto& r : mRecord){
			switch(r.first){
				case ROOMNAME::CAMP: 
					std::cout << "CAMP: " << r.second << ", ";break;
				case ROOMNAME::GENERALROOM: 
					std::cout << "GENERALROOM: " << r.second << ", ";break;
				case ROOMNAME::TRAPROOM: 
					std::cout << "TRAPROOM: " << r.second << ", ";break;
				case ROOMNAME::BOSSROOM: 
					std::cout << "BOSSROOM: " << r.second << ", ";break;
				case ROOMNAME::WEAPONROOM: 
					std::cout << "WEAPONROOM: " << r.second << std::endl;break;
			}
		}
    }

private:
    std::unordered_map<ROOMNAME, int> mRecord = {
		{ROOMNAME::WEAPONROOM, 0},
		{ROOMNAME::BOSSROOM, 0},
		{ROOMNAME::TRAPROOM, 0},
		{ROOMNAME::GENERALROOM, 0},
		{ROOMNAME::CAMP, 0}
	};
	int getTotal(){
		int total = 0;
		for(auto& r : mRecord){
			total += r.second;
		}
        return total;
    }
};

#endif