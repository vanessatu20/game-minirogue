// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Dungeon.h"
#include "Actors.h"
// You may add data members and other member functions to this class.
class Dungeon;
class Player;

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
private:
    Dungeon* m_dungeon;
    Player* m_player;
    int m_level;
    int m_GSmellDistance;
    vector<Dungeon*> m_levels;
    string takePlayerTurn();
};




#endif // GAME_INCLUDED
