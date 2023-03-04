#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

bool probality(double v) {
    srand(time(0));
    double prob = rand() % 100;
    return prob < v;
}

class Role
{
public:
    Role() = delete;
    Role(std::string name, int hp, int attack)
        : mName(name)
        , mHp(hp)
        , mHpMax(hp)
        , mAttack(attack){}
    ~Role();
    int getHp(){
        return mHp;
    }
    void setHp(int hp){
        mHp += hp;
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

enum class ROOMNAME{
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
     ~RoomBase();
    void enterEvent();
    void fightEvent();
    void reward();

private:
    ROOMNAME mName;
};

class History{
public:
    History() = default;
    ~History(){
        mRecord.clear();
        mRecord.shrink_to_fit();
    }
    void add(std::string room){
        mRecord.push_back(room);
        ++mTotalCount;
    }
    int getCount(){
        return mTotalCount;
    }
    std::string getRecord(int n){
        return mRecord[n];
    }

private:
    int mTotalCount;
    std::vector<std::string> mRecord;
};

#endif