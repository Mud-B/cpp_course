#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>

class Role
{
public:
    Role(std::string name, int hp, int attack)
        : mName(name)
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

class Room
{
public:
    Room(std::string name)
        : mName(name){}
    ~Room();
    virtual void enterEvent() = 0;
    virtual void fightEvent() = 0;
    virtual void reward() = 0;

private:
    std::string mName;
};

class History{
public:
    History() = default;
    ~History();

private:
    int mRoomNum;
    std::vector<std::string> mRecord;
};

#endif