#ifndef Objects_h
#define Objects_h

#include <string>
#include "Actors.h"
using namespace std;

///////////////////////////////////////////////////////
//  Declare Objects                                  //
///////////////////////////////////////////////////////
class Objects
{
public:
    Objects();
    virtual ~Objects();
    virtual string getName() const = 0;
    int row() const;
    int col() const;
    virtual string getType() const = 0;
    virtual char symbol() const = 0;
    
    void setPos(int r, int c);
    
private:
    int m_row;
    int m_col;
};


///////////////////////////////////////////////////////
//  Declare Weapon                                  //
///////////////////////////////////////////////////////
class Weapon: public Objects
{
public:
    Weapon(int dex, int dam);
    virtual ~Weapon();
    
    virtual string getName() const = 0 ;
    int getDexBonus() const;
    int getDamAmount() const;
    virtual string getType() const;
    virtual char symbol() const;
    virtual string actString() const = 0;
private:
    int dexBonus;
    int damAmount;
};

class Mace: public Weapon
{
public:
    Mace();
    ~Mace();
    virtual string getName() const;
    virtual string actString() const;
};

class ShortSword: public Weapon
{
public:
    ShortSword();
    ~ShortSword();
    virtual string getName() const;
    virtual string actString() const;
};

class LongSword: public Weapon
{
public:
    LongSword();
    ~LongSword();
    virtual string getName() const;
    virtual string actString() const;
};

class MagicAxe: public Weapon
{
public:
    MagicAxe();
    ~MagicAxe();
    virtual string getName() const;
    virtual string actString() const;
};

class MagicFangs: public Weapon
{
public:
    MagicFangs();
    ~MagicFangs();
    virtual string getName() const;
    virtual string actString() const;
    // Have 1/5 chance of putting the defender to sleep
    // Have 1/5 chance of putting the defender to sleep
    // Have 1/5 chance of putting the defender to sleep
    // Have 1/5 chance of putting the defender to sleep
};




///////////////////////////////////////////////////////
//  Declare Scroll                                  //
///////////////////////////////////////////////////////
class Player;
class Dungeon;
class Scroll: public Objects
{
public:
    Scroll();
    virtual ~Scroll();
    virtual void readScroll(Player* player, Dungeon* dungeon) = 0;
    virtual string getName() const = 0;
    virtual string getType() const;
    virtual char symbol() const;
};

class Teleportation: public Scroll
{
public:
    Teleportation();
    ~Teleportation();
    virtual void readScroll(Player* player, Dungeon* dungeon);
    virtual string getName() const;
};

class ImproveArmor: public Scroll
{
public:
    ImproveArmor();
    ~ImproveArmor();
    virtual void readScroll(Player* player, Dungeon* dungeon);
    virtual string getName() const;
    
};

class RaiseStrength: public Scroll
{
public:
    RaiseStrength();
    ~RaiseStrength();
    virtual void readScroll(Player* player, Dungeon* dungeon);
    virtual string getName() const;
};

class EnhanceHealth: public Scroll
{
public:
    EnhanceHealth();
    ~EnhanceHealth();
    virtual void readScroll(Player* player, Dungeon* dungeon);
    virtual string getName() const;
};

class EnhanceDexterity: public Scroll
{
public:
    EnhanceDexterity();
    ~EnhanceDexterity();
    virtual void readScroll(Player* player, Dungeon* dungeon);
    virtual string getName() const;
};

#endif /* Objects_h */
