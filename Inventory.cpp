#include "Inventory.h"
#include "utilities.h"

#include <iostream>
using namespace std;

Inventory::Inventory(){}

void Inventory::print() const
{
    clearScreen();
    cout << "Inventory:" << endl;
    char x = ' ';
    for(int i = 0; i < m_objects.size(); i++)
    {
        x = 'a' + i;
        cout << x << ". " << m_objects[i]->getName() << endl;
    }
}

int Inventory::getInvSize() const
{
    return (int)m_objects.size();
}

void Inventory::addObject(Objects* obj)
{
    m_objects.push_back(obj);
}

string Inventory::getObjectType(int index) const
{
    return m_objects[index]->getType();
}

string Inventory::getObjectName(int index) const
{
    return m_objects[index]->getName();
}

Weapon* Inventory::getWeapon(int index) const
{
    Weapon* weapon = dynamic_cast<Weapon*>(m_objects[index]);
    return weapon;
}

Scroll* Inventory::getScroll(int index) const
{
    Scroll* scroll = dynamic_cast<Scroll*>(m_objects[index]);
    return scroll;
}

void Inventory::removeObject(int index)
{
    m_objects.erase(m_objects.begin() + index);
}
