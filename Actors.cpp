#include "Actors.h"


///////////////////////////////////////////////////////
//  Implement Actors                                 //
///////////////////////////////////////////////////////
//class Actors
//{
//public:
//    Actors(int hit, int armor, int strength, int dexterity, int sleep, Weapon* weapon);
//
//    int row() const;
//    int col() const;
//    int hit() const;
//    int armor() const;
//    int strength() const;
//    int dexterity() const;
//    int sleepTime() const;
//    Weapon* getCurWeapon() const;
//
//    void setCurWeapon(Weapon* weapon);
//    void setPos(int r, int c);
//    //getPos
//private:
//    int m_row;
//    int m_col;
//    int m_hit;
//    int m_armor;
//    int m_strength;
//    int m_dexterity;
//    int m_sleepTime;
//    Weapon* m_curWeapon;
//};

Actors::Actors(int hit, int armor, int strength, int dexterity, int sleep, Weapon* weapon)
{
    m_row = 0;
    m_col = 0;
    m_hit = hit;
    m_armor = armor;
    m_strength = strength;
    m_dexterity = dexterity;
    m_sleepTime = sleep;
    m_curWeapon = weapon;
    m_maxHit = 0;
}
Actors::~Actors(){}


int Actors::row() const
{
    return m_row;
}

int Actors::col() const
{
    return m_col;
}

int Actors::hit() const
{
    return m_hit;
}

int Actors::armor() const
{
    return m_armor;
}

int Actors::strength() const
{
    return m_strength;
}

int Actors::dexterity() const
{
    return m_dexterity;
}

int Actors::sleepTime() const
{
    return m_sleepTime;
}

Weapon* Actors::getCurWeapon() const
{
    return m_curWeapon;
}

void Actors::setCurWeapon(Weapon* weapon)
{
    m_curWeapon = weapon;
}

void Actors::setPos(int r, int c)
{
    m_row = r;
    m_col = c;
}

void Actors::changeHit(int x)
{
    // Increment/decrement hit point up to the actor's maximum hit point.
    m_hit += x;
    if(m_hit > m_maxHit) { m_hit = m_maxHit; }
}

void Actors::changeArmor(int x)
{
    // Increment/decrement armor point up to 99.
    m_armor += x;
    if(m_armor > 99) { m_armor = 99; }
}

void Actors::changeStrength(int x)
{
    // Increment/decrement strength point up to 99.
    m_strength += x;
    if(m_strength > 99) { m_strength = 99; }
}

void Actors::changeDexterity(int x)
{
    // Increment/decrement dexterity point up to 99.
    m_dexterity += x;
    if(m_dexterity > 99) { m_dexterity = 99; }
}

void Actors::changeSleepTime(int x)
{
    // Increment/decrement sleep time up to 9.
    m_sleepTime += x;
    if(m_sleepTime > 9) { m_sleepTime = 9; }
}

bool Actors::attack(Actors* defender)
{
    // Attack the defender according to the formula provided.
    int attPoints = dexterity() + getCurWeapon()->getDexBonus();
    int defPoints = defender->dexterity() + defender->armor();
    int damAmount = 0;
    bool success = false;
    if(randInt(1, attPoints) >= randInt(1, defPoints))
    {
        success = true;
        damAmount = randInt(0, strength() + getCurWeapon()->getDamAmount() - 1);
        defender->changeHit(damAmount * -1);
    }
    return success;
}


void Actors::regainOneHit()
{
    // There is a 1/10 chance that the actor will regain one hit point.
    if(trueWithProbability(0.1) && hit()+1 <= m_maxHit)
    {
        m_hit++;
    }
}

void Actors::incMaxHit(int x)
{
    // Increment maximum hit points
    m_maxHit += x;
}

///////////////////////////////////////////////////////
//  Implement Player                                 //
///////////////////////////////////////////////////////
Player::Player(Game* game): Actors(20, 2, 2, 2, 0, new ShortSword)
{
    m_game = game;
    m_inventory = new Inventory;
    m_inventory->addObject(getCurWeapon());
    // Have max hit point of 20 originally.
    incMaxHit(20);
    // Set the status of winning to false originally.
    m_win = false;
}
Player::~Player(){}

void Player::addToInventory(Objects* obj)
{
    m_inventory->addObject(obj);
}

Inventory* Player::getInventory() const
{
    return m_inventory;
}

bool Player::isDead() const
{
    return (hit() <= 0);
}

void Player::wins()
{
    m_win = true;
}

bool Player::ifWins() const
{
    return m_win;
}



///////////////////////////////////////////////////////
//  Implement Monster and its subclasses             //
///////////////////////////////////////////////////////


Monster::Monster(int hit, int armor, int strength, int dexterity, int sleep, Weapon* weapon): Actors(hit, armor, strength, dexterity, sleep, weapon){}
Monster::~Monster(){}

bool Monster::inNSteps(int n, int mRow, int mCol, int pRow, int pCol) const
{
    if(n < 0)
    {
        return false;
    }
    if(mRow == pRow && mCol == pCol)
    {
        return true;
    }
    // Search by move upward.
    if(inNSteps(n-1, mRow-1, mCol, pRow, pCol))
    {
        return true;
    }
    // Search by move downward.
    if(inNSteps(n-1, mRow+1, mCol, pRow, pCol))
    {
        return true;
    }
    // Search by move leftward.
    if(inNSteps(n-1, mRow, mCol-1, pRow, pCol))
    {
        return true;
    }
    // Search by move rightward.
    if(inNSteps(n-1, mRow, mCol+1, pRow, pCol))
    {
        return true;
    }
    return false;
}

char Monster::chaseDir(Player* player) const
{
    char dir = 'N';
    int order = randInt(2);
    if(order == 0)
    {
        if(row() > player->row())
        {
            dir = 'U';
        }
        if(row() < player->row())
        {
            dir = 'D';
        }
        if(col() > player->col())
        {
            dir = 'L';
        }
        if(col() < player->col())
        {
            dir = 'R';
        }
    }
    else
    {
        if(col() > player->col())
        {
            dir = 'L';
        }
        if(col() < player->col())
        {
            dir = 'R';
        }
        if(row() > player->row())
        {
            dir = 'U';
        }
        if(row() < player->row())
        {
            dir = 'D';
        }
    }
    return dir;
}

Bogeyman::Bogeyman(): Monster(randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), 0, new ShortSword){}
Bogeyman::~Bogeyman(){}

string Bogeyman::getName() const
{
    return "Bogeyman";
}

char Bogeyman::symbol() const
{
    return 'B';
}

char Bogeyman::chooseMove(Player* player, int goblinDist, char grid[][MAXCOLS])
{
    if(inNSteps(5, row(), col(), player->row(), player->col()))
    {
        return chaseDir(player);
    }
    return 'N';
}

Objects* Bogeyman::maybeLeaveWeapon() const
{
    if(trueWithProbability(0.1))
    {
        Objects* newObj = new MagicAxe;
        return newObj;
    }
    return nullptr;
}

Snakewoman::Snakewoman(): Monster(randInt(3, 6), 3, 2, 3, 0, new MagicFangs){}
Snakewoman::~Snakewoman(){}

string Snakewoman::getName() const
{
    return "Snakewoman";
}

char Snakewoman::symbol() const
{
    return 'S';
}

char Snakewoman::chooseMove(Player* player, int goblinDist, char grid[][MAXCOLS])
{
    if(inNSteps(3, row(), col(), player->row(), player->col()))
    {
        return chaseDir(player);
    }
    return 'N';
}

Objects* Snakewoman::maybeLeaveWeapon() const
{
    if(trueWithProbability(1.0/3.0))
    {
        Objects* newObj = new MagicFangs;
        return newObj;
    }
    return nullptr;
}

Dragon::Dragon(): Monster(randInt(20, 25), 4, 4, 4, 0, new LongSword)
{
    incMaxHit(hit());
}
Dragon::~Dragon(){}

string Dragon::getName() const
{
    return "Dragon";
}

char Dragon::symbol() const
{
    return 'D';
}

char Dragon::chooseMove(Player* player, int goblinDist, char grid[][MAXCOLS])
{
    regainOneHit();
    if(inNSteps(1, row(), col(), player->row(), player->col()))
    {
        return chaseDir(player);
    }
    return 'N';
}

Objects* Dragon::maybeLeaveWeapon() const
{
    int rand = randInt(5);
    Objects* newObj = nullptr;
    if(rand == 0)
    {
        newObj = new Teleportation;
    }
    else if(rand == 1)
    {
        newObj = new ImproveArmor;
    }
    else if(rand == 2)
    {
        newObj = new RaiseStrength;
    }
    else if(rand == 3)
    {
        newObj = new EnhanceHealth;
    }
    else if(rand == 4)
    {
        newObj = new EnhanceDexterity;
    }
    return newObj;
}

Goblin::Goblin(): Monster(randInt(15, 20), 1, 3, 1, 0, new ShortSword){}
Goblin::~Goblin(){}

string Goblin::getName() const
{
    return "Goblin";
}

char Goblin::symbol() const
{
    return 'G';
}

char Goblin::chooseMove(Player* player, int goblinDist, char grid[][MAXCOLS])
{
    if(inNSteps(5, row(), col(), player->row(), player->col()))
    {
        return chaseDir(player);
    }
    return 'N';
}

Objects* Goblin::maybeLeaveWeapon() const
{
    Objects* newObj = nullptr;
    if(trueWithProbability(1.0/3.0))
    {
        int rand = randInt(2);
        if(rand == 0)
        {
            newObj = new MagicAxe;
        }
        else
        {
            newObj = new MagicFangs;
        }
    }
    return newObj;
}
