#ifndef Inventory_h
#define Inventory_h

#include "Objects.h"
#include <vector>
using namespace std;

class Objects;
class Weapon;
class Scroll;

class Inventory
{
public:
    Inventory();
    void print() const;
    int getInvSize() const;
    string getObjectType(int index) const;
    string getObjectName(int index) const;
    Weapon* getWeapon(int index) const;
    Scroll* getScroll(int index) const;
    void addObject(Objects* obj);
    void removeObject(int index);
    
private:
    vector<Objects*> m_objects;
};

#endif /* Inventory_h */
