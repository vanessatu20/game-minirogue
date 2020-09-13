#ifndef Actors_h
#define Actors_h

#include "Objects.h"
#include "utilities.h"
#include "Inventory.h"
#include "Dungeon.h"
#include <string>
using namespace std;

///////////////////////////////////////////////////////
//  Declare Actors                                   //
///////////////////////////////////////////////////////
//class Weapon;
//class Objects;
//
class Inventory;
class Weapon;
class Game;
class Dungeon;
class Objects;
class Actors
{
public:
    Actors(int hit, int armor, int strength, int dexterity, int sleep, Weapon* weapon);
    virtual ~Actors();
    
    int row() const;
    int col() const;
    int hit() const;
    int armor() const;
    int strength() const;
    int dexterity() const;
    int sleepTime() const;
    Weapon* getCurWeapon() const;
    
    void setCurWeapon(Weapon* weapon);
    void setPos(int r, int c);
    void changeHit(int x);
    void changeArmor(int x);
    void changeStrength(int x);
    void changeDexterity(int x);
    void changeSleepTime(int x);
    bool attack(Actors* defender);
    void regainOneHit();
    void incMaxHit(int x);
    
private:
    int m_row;
    int m_col;
    int m_hit;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleepTime;
    Weapon* m_curWeapon;
    int m_maxHit;
};

///////////////////////////////////////////////////////
//  Declare Player                                   //
///////////////////////////////////////////////////////


class Player: public Actors
{
public:
    Player(Game* game);
    virtual ~Player();

    Inventory* getInventory() const;
    bool isDead() const;
    bool ifWins() const;
    void wins();
    void addToInventory(Objects* obj);
    
private:
    Game* m_game;
    Inventory* m_inventory;
    bool m_win;
};


///////////////////////////////////////////////////////
//  Declare Monsters                                 //
///////////////////////////////////////////////////////


class Monster: public Actors
{
public:
    Monster(int hit, int armor, int strength, int dexterity, int sleep, Weapon* weapon);
    virtual ~Monster();
    
    virtual string getName() const = 0;
    virtual char symbol() const = 0;
    virtual char chooseMove(Player* player, int goblinDist, char grid[][70]) = 0;
    
    virtual Objects* maybeLeaveWeapon() const = 0;
    bool inNSteps(int n, int mRow, int mCol, int pRow, int pCol) const;
    char chaseDir(Player* player) const;
};

class Bogeyman: public Monster
{
public:
    Bogeyman();
    ~Bogeyman();
    string getName() const;
    char symbol() const;
    char chooseMove(Player* player, int goblinDist, char grid[][70]);
    Objects* maybeLeaveWeapon() const;
};

class Snakewoman: public Monster
{
public:
    Snakewoman();
    ~Snakewoman();
    string getName() const;
    char symbol() const;
    char chooseMove(Player* player, int goblinDist, char grid[][70]);
    Objects* maybeLeaveWeapon() const;
};

class Dragon: public Monster
{
public:
    Dragon();
    ~Dragon();
    string getName() const;
    char symbol() const;
    char chooseMove(Player* player, int goblinDist, char grid[][70]);
    Objects* maybeLeaveWeapon() const;
};

class Goblin: public Monster
{
public:
    Goblin();
    ~Goblin();
    string getName() const;
    char symbol() const;
    char chooseMove(Player* player, int goblinDist, char grid[][70]);
    Objects* maybeLeaveWeapon() const;
};



#endif /* Actors_h */
