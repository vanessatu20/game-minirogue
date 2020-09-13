// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Inventory.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    m_dungeon = nullptr;
    m_player = new Player(this);
    m_GSmellDistance = goblinSmellDistance;
    
    // Create 5 dungeons of the game
    for(int i = 0; i < 5; i++)
    {
        m_levels.push_back(new Dungeon(i, m_player, m_GSmellDistance));
    }
    // Set the current dungeon to the first level.
    m_dungeon = m_levels[0];
}



void Game::play()
{
    string player_message = "";
    string monsters_message = "";
    // Add player to the current dungeon and displaye the dungeon.
    m_dungeon->putPlayer();
    m_dungeon->print();
    
    // Repeatedly, the let player take their turn, let monsters take their turn, and display the dungeon along with their messages.
    do{
        player_message = takePlayerTurn();
        monsters_message = m_dungeon->takeMonstersTurn();
        m_dungeon->print();
        cout << player_message << endl << monsters_message << endl;
        
    } while(!m_player->ifWins() && !m_player->isDead()); // Continue until the game ends

    cout << "Press q to exit game." << endl;
    while (getCharacter() != 'q')
        ;
}

string Game::takePlayerTurn()
{
    // 1/10 of the time the player will regain one hit point when taking their turn.
    m_player->regainOneHit();
    char command;
    string message = "";
    // Prompt the user for a command.
    command = getCharacter();
    
    // Decrease the sleepTime by 1 if there is still sleeptime remaining
    if(m_player->sleepTime() > 0)
    {
        m_player->changeSleepTime(-1);
        return "Player is asleep now.";
    }
    // Move the player in the commanded direction or attack the monster in that direction
    if(command == ARROW_LEFT || command == ARROW_RIGHT || command == ARROW_UP || command == ARROW_DOWN)
    {
        message = m_dungeon->movePlayer(command); // returns a character
    }
    // Get the object on the position the player is on if it is present.
    else if(command == 'g')
    {
        message = m_dungeon->getObject(m_player->row(), m_player->col());
    }
    // Display the player's inventory.
    else if(command == 'i')
    {
        m_player->getInventory()->print();
        getCharacter();
    }
    // Attempt to wield a weapon.
    else if(command == 'w')
    {
        m_player->getInventory()->print();
        // Prompt the user to select an item and check if the item is a weapon in the inventory.
        char ch = getCharacter();
        if(ch >= 'a' && ch <= 'a' + m_player->getInventory()->getInvSize() - 1 && m_player->getInventory()->getObjectType(ch - 'a') == "weapon")
        {
            // Set the player's current weapon to the selected weapon and return a message accordingly.
            m_player->setCurWeapon(m_player->getInventory()->getWeapon(ch - 'a'));
            message = "You are wielding a " + m_player->getInventory()->getObjectName(ch - 'a') + "!";
        }
    }
    // Attempt to read a scroll.
    else if(command == 'r')
    {
        m_player->getInventory()->print();
        // Prompt the user to select an item and check if the item is a scroll in the inventory.
        char ch = getCharacter();
        if(ch >= 'a' && ch <= 'a' + m_player->getInventory()->getInvSize() - 1 && m_player->getInventory()->getObjectType(ch - 'a') == "scroll")
        {
            // Use the scroll make it self destruct when used.
            Scroll* scroll = m_player->getInventory()->getScroll(ch - 'a');
            scroll->readScroll(m_player, m_dungeon);
            m_player->getInventory()->removeObject(ch - 'a');
            // Return a message accordingly.
            message = "You read the scroll called " + m_player->getInventory()->getObjectName(ch - 'a') + "!";
        }
    }
    // If the position is stairs, change the dungeon to the next level and place the player in the new dungeon.
    else if(command == '>' && m_dungeon->isStair())
    {
        int curLevel = m_dungeon->getLevel();
        m_dungeon = m_levels[curLevel+1];
        m_dungeon->putPlayer();
        m_dungeon->print();
    }
    
    // Returns either a messahe or an empty string according to the action taken.
    return message;
}


// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
