#include "Dungeon.h"
#include "utilities.h"
#include "Objects.h"
#include <iostream>
using namespace std;

Dungeon::Dungeon(int level, Player* player, int goblinSmellDistance)
{
    m_player = player;
    m_level = level;
    m_GSmellDistance = goblinSmellDistance;
    
    // Set the rooms and corridors.
    for(int i = 0; i < MAXROWS; i++)
    {
        for(int j = 0; j < MAXCOLS; j++)
        {
            m_grid[i][j] = '#';
        }
    }
    
    for(int i = 3; i < 13; i++)
    {
        for(int j = 4; j < 19; j++)
        {
            m_grid[i][j] = ' ';
        }
    }
    
    for(int i = 10; i < 15; i++)
    {
        for(int j = 25; j < 42; j++)
        {
            m_grid[i][j] = ' ';
        }
    }
    
    for(int i = 7; i < 14; i++)
    {
        for(int j = 46; j < 65; j++)
        {
            m_grid[i][j] = ' ';
        }
    }
    
    for(int i = 4; i < 64; i++)
    {
        m_grid[12][i] = ' ';
    }
    
    // Set objects grid only indicating walls and objects.
    for(int i = 0; i < MAXROWS; i++)
    {
        for(int j = 0; j < MAXCOLS; j++)
        {
            m_objPos[i][j] = m_grid[i][j];
        }
    }
    // Add 2 or 3 objects on the dungeon.
    int objNum = randInt(2, 3);
    for(int i = 0; i < objNum; i++)
    {
        addObject();
    }
    // add stairway or golden idol
    bool success = false;
    char objChar = '>';
    if(m_level == 4) { objChar = '&'; }
    while(success == false)
    {
        int randR = randInt(MAXROWS);
        int randC = randInt(MAXCOLS);
        
        if(m_grid[randR][randC] != ' ') { continue; }
        m_grid[randR][randC] = objChar;
        m_objPos[randR][randC] = objChar;
        success = true;
    }

    // Add monsters to the dungeon.
    addMonsters();

}

void Dungeon::print() const
{
    clearScreen();
    // display the m_grid to show the dungeon.
    for(int i = 0; i < MAXROWS; i++)
    {
        for(int j = 0; j < MAXCOLS; j++)
        {
            cout << m_grid[i][j];
        }
        cout << endl;
    }
    // print lable line displaying the status of the player and game.
    cout << "Dungeon Level: " << m_level << ", Hit Points: " << m_player->hit() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dexterity() << endl << endl;
}

Objects* Dungeon::makeRandObject()
{
    // Return of the the 7 types of objects.
    int objType = randInt(7);
    Objects* newObj = nullptr;
    
    if(objType == 0)
    {
        newObj = new Mace;
    }
    else if(objType == 1)
    {
        newObj = new ShortSword;
    }
    else if(objType == 2)
    {
        newObj = new LongSword;
    }
    else if(objType == 3)
    {
        newObj = new ImproveArmor;
    }
    else if(objType == 4)
    {
        newObj = new RaiseStrength;
    }
    else if(objType == 5)
    {
        newObj = new EnhanceHealth;
    }
    else if(objType == 6)
    {
        newObj = new EnhanceDexterity;
    }
    
    // Add to the vector of objects on the dungeon.
    m_objects.push_back(newObj);
    return newObj;
}


void Dungeon::putPlayer()
{
    // If player already exists, remove the '@' on the original position of the player.
    if(m_player->row() != 0)
    {
        m_grid[m_player->row()][m_player->col()] = m_objPos[m_player->row()][m_player->col()];
    }
    // Select a random position to place the player until the selected position is not occupied by a wall or a monster.
    bool success = false;
    while(success == false)
    {
        int r = randInt(MAXROWS);
        int c = randInt(MAXCOLS);
        
        if (m_grid[r][c] != '#' && m_grid[r][c] != 'B' && m_grid[r][c] != 'S' && m_grid[r][c] != 'D' && m_grid[r][c] != 'G')
        {
            m_player->setPos(r, c);
            m_grid[r][c] = '@';
            success = true;
        }
    }
}

void Dungeon::addObject()
{
    Objects* newObj = makeRandObject();
    char objChar = newObj->symbol();
    int randR, randC;
    bool success = false;
    // Select a random position to place each objects until the selected position is not occupied by a wall or another object.
    while(success == false)
    {
        randR = randInt(1, MAXROWS-2);
        randC = randInt(1, MAXCOLS-2);
        if(m_objPos[randR][randC] == ' ')
        {
            newObj->setPos(randR, randC);
            success = true;
            m_grid[randR][randC] = objChar;
            m_objPos[randR][randC] = objChar;
        }
    }
}

string Dungeon::getObject(int r, int c)
{
    // If the player picks up the golden idol, the player wins the game.
    if(m_objPos[r][c] == '&')
    {
        m_player->wins();
        return "Congratulations, you won!";
    }
    // Else, check which objects on the dungeon is the objects being picked up.
    // Erase it from the list of objects on the dungeon and add it to the player's inventory.
    for(int i = 0; i < m_objects.size() && m_player->getInventory()->getInvSize() < 26; i++)
    {
        if(m_objects[i]->row() == r && m_objects[i]->col() == c)
        {
            m_player->addToInventory(m_objects[i]);
            m_objects.erase(m_objects.begin() + i);
            m_objPos[r][c] = ' ';
            return "You picked up a " + m_objects[i]->getName() + ".";
        }
    }
    return "";
}

string Dungeon::movePlayer(char dir)
{
    int r = 0;
    int c = 0;
    // Set r and c to the coordinate next of the current position in the corresponding direction.
    if(dir == ARROW_LEFT)
    {
        r = m_player->row();
        c = m_player->col()-1;
    }
    else if(dir == ARROW_RIGHT)
    {
        r = m_player->row();
        c = m_player->col()+1;
    }
    else if(dir == ARROW_UP)
    {
        r = m_player->row()-1;
        c = m_player->col();
    }
    else if(dir == ARROW_DOWN)
    {
        r = m_player->row()+1;
        c = m_player->col();
    }
    // Don't move if there is a wall.
    if(m_grid[r][c] == '#')
    {
        return "";
    }
    // If there is a monster in that direction
    bool ifHit = false;
    if(m_grid[r][c] == 'B' || m_grid[r][c] == 'S' || m_grid[r][c] == 'D' || m_grid[r][c] == 'G')
    {
        Monster* defMonster = nullptr;
        int monIndex = 0;
        // Check which monster on the dungeon the player wants to attack by matching the location of each monster in the vector.
        for(int i = 0; i < m_monsters.size(); i++)
        {
            if(r == m_monsters[i]->row() && c == m_monsters[i]->col())
            {
                defMonster = m_monsters[i];
                monIndex = i;
            }
        }
        if(defMonster == nullptr){ exit(1); }
        // Attack the monster on that position.
        ifHit = m_player->attack(defMonster);
        // Create Message to return.
        string message = "Player " + m_player->getCurWeapon()->actString() + " " + m_player->getCurWeapon()->getName() + " at " + defMonster->getName();
        if(ifHit)
        {
            // If the player kills the monster.
            if(defMonster->hit() <= 0)
            {
                // Remove the monster from the dungeon and check if the monsters leaves an object.
                m_monsters.erase(m_monsters.begin() + monIndex);
                Objects* leaveObj= defMonster->maybeLeaveWeapon();
                // If the monster leaves an object
                if(leaveObj != nullptr)
                {
                    // Delete the object if the position is already occpied by another object.
                    if(m_objPos[r][c] != ' ')
                    {
                        delete leaveObj;
                    }
                    // Else, add the new object to the vector of objects on the dungeon.
                    else
                    {
                        m_objects.push_back(leaveObj);
                        leaveObj->setPos(r, c);
                        m_grid[r][c] = leaveObj->symbol();
                        m_objPos[r][c] = leaveObj->symbol();
                    }
                }
                else
                {
                    m_grid[r][c] = ' ';
                }
                return message + " dealing a final blow.";
            }
            // If the attacker's weapon is the magic fangs of sleep, check if it puts the defender to sleep.
            if(m_player->getCurWeapon()->getName() == "magic fangs of sleep" && trueWithProbability(0.2))
            {
                int r = randInt(2, 6);
                if(defMonster->sleepTime() < r)
                {
                    defMonster->changeSleepTime(r);
                }
                return message + " and hits, putting " + defMonster->getName() + " to sleep.";
            }
            return message + " and hits.";
        }
        return message + " and misses.";
    }
    // Set the grid to display accordingly
    m_grid[m_player->row()][m_player->col()] = m_objPos[m_player->row()][m_player->col()];
    m_grid[r][c] = '@';
    m_player->setPos(r, c);
    
    return "";
}


void Dungeon::addMonsters()
{
    int nMonster = randInt(2, 5*(m_level+1)+1);
    int type = 0;
    int randR = 0;
    int randC = 0;
    bool success = false;
    Monster* newMon = nullptr;
    for(int i = 0; i < nMonster; i++)
    {
        // Two of the monsters can appear on level 0 and 1
        if(m_level == 0 || m_level == 1)
        {
            type = randInt(2);
            if(type == 0)
            {
                newMon = new Goblin;
            }
            else if(type == 1)
            {
                newMon = new Snakewoman;
            }
        }
        // Three of the monsters can appear on level 2
        else if(m_level == 2)
        {
            type = randInt(3);
            if(type == 0)
            {
                newMon = new Bogeyman;
            }
            else if(type == 1)
            {
                newMon = new Snakewoman;
            }
            else if(type == 2)
            {
                newMon = new Goblin;
            }
        }
        // All four monsters can appear on level 3 and 4
        else if(m_level == 3 || m_level == 4)
        {
            type = randInt(4);
            if(type == 0)
            {
                newMon = new Bogeyman;
            }
            else if(type == 1)
            {
                newMon = new Snakewoman;
            }
            else if(type == 2)
            {
                newMon = new Dragon;
            }
            else if(type == 3)
            {
                newMon = new Goblin;
            }
        }
        
        success = false;
        // Add the monster to a space not occupied by a wall or other actors, and set the grid accordingly.
        while(success == false)
        {
            randR = randInt(1, MAXROWS-2);
            randC = randInt(1, MAXCOLS-2);
            if(m_grid[randR][randC] == '#') { continue; }
            
            
            newMon->setPos(randR, randC);
            m_grid[randR][randC] = newMon->symbol();
            m_monsters.push_back(newMon);
            success = true;
        }
    }
}

string Dungeon::takeMonstersTurn()
{
    string message = "";
    for(int i = 0; i < m_monsters.size(); i++)
    {
        // If there is sleep time remaining for the monster, decrement its sleep tims and skip its turn to move.
        if(m_monsters[i]->sleepTime() > 0)
        {
            m_monsters[i]->changeSleepTime(-1);
            continue;
        }
        // Call each monster's function to determine where they want to move.
        char dir = m_monsters[i]->chooseMove(m_player, m_GSmellDistance, m_grid);
        int r = 0;
        int c = 0;
        if(dir == 'L')
        {
            r = m_monsters[i]->row();
            c = m_monsters[i]->col()-1;
        }
        else if(dir == 'R')
        {
            r = m_monsters[i]->row();
            c = m_monsters[i]->col()+1;
        }
        else if(dir == 'U')
        {
            r = m_monsters[i]->row()-1;
            c = m_monsters[i]->col();
        }
        else if(dir == 'D')
        {
            r = m_monsters[i]->row()+1;
            c = m_monsters[i]->col();
        }
        // Skip this turn if the monster decides not to move.
        else if(dir == 'N') { continue; }
        // Move to the specified position if it's not occupied by a wall or another monster or player.
        if(m_grid[r][c] == ' ' || m_grid[r][c] == '?' || m_grid[r][c] == ')' || m_grid[r][c] == '>' || m_grid[r][c] == '&')
        {
            m_grid[m_monsters[i]->row()][m_monsters[i]->col()] = m_objPos[m_monsters[i]->row()][m_monsters[i]->col()];
            m_grid[r][c] = m_monsters[i]->symbol();
            m_monsters[i]->setPos(r, c);
        }
        // Attck the player if the player is in the specified position.
        else if(m_grid[r][c] == '@')
        {
            bool ifHit = m_monsters[i]->attack(m_player);
            message +=  m_monsters[i]->getName() + " " + m_monsters[i]->getCurWeapon()->actString() + " " + m_monsters[i]->getCurWeapon()->getName() + " at Player";
            if(ifHit)
            {
                if(m_player->hit() <= 0)
                {
                    message += " dealing a final blow.\n";
                }
                // If the monster is wielding a magic fangs of sleep, check if it puts the player to sleep.
                else if(m_monsters[i]->getCurWeapon()->getName() == "magic fangs of sleep" && trueWithProbability(0.2))
                {
                    int r = randInt(2, 6);
                    if(m_player->sleepTime() < r)
                    {
                        m_player->changeSleepTime(r);
                    }
                    message += " and hits, putting Player to sleep.";
                }
                else
                {
                    message += " and hits.\n";
                }
            }
            else
            {
                message += " and misses.\n";
            }
        }
    }
    // Return a message according to each situation.
    return message;
}


int Dungeon::getLevel() const
{
    return m_level;
}

bool Dungeon::isStair() const
{
    return (m_objPos[m_player->row()][m_player->col()] == '>');
}
