#ifndef Dungeon_h
#define Dungeon_h

#include "Actors.h"
#include "Objects.h"
#include "Inventory.h"
#include <vector>
#include <string>
using namespace std;

const int MAXROWS = 18;
const int MAXCOLS = 70;

class Player;
class Monster;
class Objects;

class Dungeon
{
public:
    Dungeon(int level, Player* player, int goblinSmellDistance);
    //Accessors
    void print() const;
    //char getCellStatus(int r, int c) const;
    
    //Mutators
    Objects* makeRandObject();
    // Creates a random object.
    
    void putPlayer();
    // Randomly place the player on the dungeon.
    
    void addObject();
    // Randomly place an object on the dungeon.
    
    string getObject(int r, int c);
    // Retrieve the object at the specified position.
    
    string movePlayer(char dir);
    // Move player to the specified direction or attack the monster in the direction.
    
    void addMonsters();
    // Add M monsters that will appear on the specific dungeon level.
    
    string takeMonstersTurn(); // Let the monsters take their turn to move or attack the player.
    
    int getLevel() const;
    bool isStair() const;
    
private:
    int m_level;
    char m_grid[MAXROWS][MAXCOLS];
    char m_objPos[MAXROWS][MAXCOLS];
    vector<Objects*> m_objects;
    vector<Monster*> m_monsters;
    Player* m_player;
    int m_GSmellDistance;
};

#endif /* Dungeon_h */
