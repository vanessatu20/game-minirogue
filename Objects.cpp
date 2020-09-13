#include "Objects.h"

///////////////////////////////////////////////////////
//  Implement Objects                                //
///////////////////////////////////////////////////////
Objects::Objects()
{
    m_row = 0;
    m_col = 0;
}

Objects::~Objects(){}

int Objects::row() const
{
    return m_row;
}

int Objects::col() const
{
    return m_col;
}

void Objects::setPos(int r, int c)
{
    m_row = r;
    m_col = c;
}


///////////////////////////////////////////////////////
//  Implement Weapon                                //
///////////////////////////////////////////////////////
Weapon::Weapon(int dex, int dam): dexBonus(dex), damAmount(dam){}
Weapon::~Weapon(){}

int Weapon::getDexBonus() const
{
    return dexBonus;
}
int Weapon::getDamAmount() const
{
    return damAmount;
}

char Weapon::symbol() const
{
    return ')';
}

string Weapon::getType() const
{
    return "weapon";
}

Mace::Mace(): Weapon(0, 2){}
Mace::~Mace(){}

string Mace::getName() const
{
    return "mace";
}

string Mace::actString() const
{
    return "swings";
}

ShortSword::ShortSword(): Weapon(0, 2){}
ShortSword::~ShortSword(){}

string ShortSword::getName() const
{
    return "short sword";
}

string ShortSword::actString() const
{
    return "slashes";
}

LongSword::LongSword(): Weapon(2, 4){}
LongSword::~LongSword(){}

string LongSword::getName() const
{
    return "long sword";
}

string LongSword::actString() const
{
    return "swings";
}

MagicAxe::MagicAxe(): Weapon(5, 5){}
MagicAxe::~MagicAxe(){}

string MagicAxe::getName() const
{
    return "magic axe";
}

string MagicAxe::actString() const
{
    return "chops";
}

MagicFangs::MagicFangs(): Weapon(3, 2){}
MagicFangs::~MagicFangs(){}

string MagicFangs::getName() const
{
    return "magic fangs of sleep";
}

string MagicFangs::actString() const
{
    return "stikes";
}



///////////////////////////////////////////////////////
//  Implement Scroll                                //
///////////////////////////////////////////////////////

Scroll::Scroll(){}
Scroll::~Scroll(){}

string Scroll::getType() const
{
    return "scroll";
}

char Scroll::symbol() const
{
    return '?';
}


// Implementation of Teleportation scroll
Teleportation::Teleportation(){}
Teleportation::~Teleportation(){}

void Teleportation::readScroll(Player* player, Dungeon* dungeon)
{
    dungeon->putPlayer();
}

string Teleportation::getName() const
{
    return "scroll of teleportation";
}


// Implementation of Imrpove Armor scroll
ImproveArmor::ImproveArmor(){}
ImproveArmor::~ImproveArmor(){}

void ImproveArmor::readScroll(Player* player, Dungeon* dungeon)
{
    player->changeArmor(randInt(1, 3));
}
string ImproveArmor::getName() const
{
    return "scroll of improve armor";
}


// Implementation of Raise Strength scroll
RaiseStrength::RaiseStrength(){}
RaiseStrength::~RaiseStrength(){}

void RaiseStrength::readScroll(Player* player, Dungeon* dungeon)
{
    player->changeStrength(randInt(1, 3));
}
string RaiseStrength::getName() const
{
    return "scroll of raise strength";
}


// Implementation of Enhance Health scroll
EnhanceHealth::EnhanceHealth(){}
EnhanceHealth::~EnhanceHealth(){}


void EnhanceHealth::readScroll(Player* player, Dungeon* dungeon)
{
    player->incMaxHit(randInt(3, 8));
}
string EnhanceHealth::getName() const
{
    return "scroll of enhance health";
}


// Implementation of Enhance Dexterity scroll
EnhanceDexterity::EnhanceDexterity(){}
EnhanceDexterity::~EnhanceDexterity(){}

void EnhanceDexterity::readScroll(Player* player, Dungeon* dungeon)
{
    player->changeDexterity(1);
}
string EnhanceDexterity::getName() const
{
    return "scroll of enhance dexterity";
}
