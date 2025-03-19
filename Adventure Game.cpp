/*
Name: Daniel Joy
Email: drjoy@cn.edu
ID: 0587254
Major: Computer Science & Mathematics
*/

#include <iostream>
#include <cstdlib>
#include <random>
#include <time.h> //for time control
#include <unistd.h> //for sleep
#include <algorithm> //for finding
#include <string> //for string/int concatination
using namespace std;

void gameOver();
void visitTheShop();
void backToTown();

class Player
{
private:
    int health;
    int damage;
    int defense;
    int luck;
    int dungeonsCleared;
    int gold;
public:
    string name = "";
    Player()
    {
        health = 100;
        damage = 5;
        defense = 2;
        luck = 1;
        dungeonsCleared = 0;
    }
    int getGold()
    {
        return gold;
    }
    void addGold(int gold1)
    {
        gold += gold1;
    }
    void subtractGold(int gold1)
    {
        gold -= gold1;
    }
    int getHealth()
    {
        return health;
    }
    int getDefense()
    {
        return defense;
    }
    int getDamage()
    {
        return damage;
    }
    int getLuck()
    {
        return luck;
    }
    int getDungeonsCleared()
    {
        return dungeonsCleared;
    }
    void addDungeonCleared()
    {
        dungeonsCleared += 1;
    }
    void takeDamage(int damage)
    {
        health -= damage;
        if(health <= 0)
        {
            gameOver();
        }
    }
    void addHealth(int hlth)
    {
        health += hlth;
    }
    void addDamage(int dmge)
    {
        damage += dmge;
    }
    void addDefense(int dfnse)
    {
        defense += dfnse;
    }
    void addLuck(int lck)
    {
        luck += lck;
    }
};
class Monster
{
private:
    int health;
    int damage;
    int defense;
public:
    int getHealth()
    {
        return health;
    }
    int getDamage()
    {
        return damage;
    }
    int getDefense()
    {
        return defense;
    }
    void takeDamage(int damage)
    {
        health -= damage;
    }
    Monster(int health1, int damage1, int defense1)
    {
        health = health1;
        damage = damage1;
        defense = defense1;
    }
    Monster()
    {
        health = 10;
        damage = 3;
        defense = 2;
    }
};

string questName = "";
string quests[] = {"Venture into the dungeon located northwest of town and slay its inhabitants",
                    "Locate the tower south-west of the village and kill the evil king",
                    "Rescue the lost kitten somewhere in the village",
                    "Figure out how to unpoison the local well",
                    "Collect 5 flowers for the royal wedding"};
Player player;

void slowPrint(string toPrint)
{
    for(int x = 0; x < toPrint.length(); x++)
    {
        cout << toPrint.at(x);
        usleep(40000);
    }
    cout << "\n";
}

void gameOver()
{
    cout << "Game over.";
    cout << "You cleared " << player.getDungeonsCleared() << " dungeons.";
}

void displayRoom(string entity)
{
    cout << "#################################" << endl;
    for (int x = 0; x < 5; x++)
    {
        cout << "#                                #" << endl;
    }
    cout << "#              " << entity.at(0) << "                #" << endl;
    for (int x = 0; x < 5; x++)
    {
        cout << "#                                #" << endl;
    }
    cout << "#################################" << endl;
}
void quest1()
{
    string questItems[] = {"Monster", "Treasure", "Berries"};
    string treasures[] = {"Sword of Death", "Shield of Bravery", "Head of Lettuce"};
    string monsters[] = {"Slime", "Zombie", "Skeleton Archer", "Skeleton Warrior"};
    slowPrint("You've decided to venture into the dungeon!\n");
    slowPrint("You walk into the first room...");
    for(int x = 0; x < 5; x++)
    {
        int tempNum = rand() % 100;
        string currentRoom = "";
        if(tempNum >= 30)
            currentRoom = "Monster";
        else if(tempNum >= 10)
            currentRoom = "Treasure";
        else
            currentRoom = "Berries";
        displayRoom(currentRoom);
        if(currentRoom == "Berries")
        {
            slowPrint("This room contains berries! They will replenish +10 health");
            if(player.getHealth() >= 90)
            {
                player.addHealth(100-player.getHealth());
            }
            else
            {
                player.addHealth(10);
            }
        }
        else if(currentRoom == "Treasure")
        {
            slowPrint("This room contains treasure!");
            slowPrint("You walk up to find...");
            string randomTreasure = treasures[rand() % 3];
            cout << "a " << randomTreasure << "!";
            if(randomTreasure == "Sword of Death")
            {
                slowPrint("You gain 5 damage!");
                player.addDamage(5);
            }
            else if(randomTreasure == "Shield of Bravery")
            {
                slowPrint("You gain 2 defense!");
                player.addDefense(2);
            }
            else if(randomTreasure == "Head of Lettuce")
            {
                slowPrint("Lettuce grants luck!");
                player.addLuck(1);
            }
        }
        else if(currentRoom == "Monster")
        {
            slowPrint("You found a monster! Preparing for combat...");
            usleep(30000);
            string currentMonster = monsters[rand() % 4];
            int stats[] = {};
            if(currentMonster == "Slime")
            {
                stats[0] = 10, stats[1] = 2, stats[2] = 2;
                slowPrint("You found a slime!");
            }
            else if(currentMonster == "Zombie")
            {
                slowPrint("You found a zombie!");
                stats[0] = 8, stats[1] = 3, stats[2] = 2;
            }
            else if(currentMonster == "Skeleton Archer")
            {
                slowPrint("You found a Skeleton Archer!");
                stats[0] = 5, stats[1] = 5, stats[2] = 2;
            }
            else if(currentMonster == "Skeleton Warrior")
            {
                slowPrint("You found a Skeleton Warrior!");
                stats[0] = 10, stats[1] = 7, stats[2] = 4;
            }
            Monster monster(stats[0], stats[1], stats[2]);
            while(monster.getHealth() > 0 && player.getHealth() > 0)
            {
                slowPrint("Attacking the monster...");
                int damageToTake = player.getDamage() - monster.getDefense();
                if(rand() % 20 <= player.getLuck())
                {
                    slowPrint("You got lucky and landed a critical hit! x2 damage!");
                    damageToTake *= 2;
                }
                monster.takeDamage(damageToTake);
                slowPrint("The monster took " + to_string(damageToTake) + " damage. It now has " + to_string(monster.getHealth()) + " HP remaining.");
                usleep(300000);
                slowPrint("Now the monster will attack you...");
                damageToTake = monster.getDamage() - player.getDefense();
                if(damageToTake > 0)
                {
                    player.takeDamage(damageToTake);
                    slowPrint("You took " + to_string(damageToTake) + " damage, you have " + to_string(player.getHealth()) + " HP remaining.");
                }
                else
                {
                    slowPrint("The monster did no damage to you.");
                }
                usleep(300000);
            }
            if(player.getHealth() <= 0)
            {
                gameOver();
            }
            else
            {
                int goldToGain = rand() % 5 + 1;
                slowPrint("You defeated the monster! You gain " + to_string(goldToGain) + " gold pieces!");
                player.addGold(goldToGain);
                slowPrint("Additionally, you gain 1 skill point all around!");
                player.addDamage(1);
                player.addDefense(1);
                player.addHealth(1);
                player.addLuck(1);
            }
        }
        slowPrint("Moving on to the next room...");
    }
    slowPrint("After 5 rooms of the dungeon, you creep into the final room... inside... is a hideous, 50 ft tall monster.");
    Monster monster(50, 10, 5);
    while(monster.getHealth() > 0 && player.getHealth() > 0)
    {
        slowPrint("Attacking the boss...");
        int damageToTake = player.getDamage() - monster.getDefense();
        if(rand() % 50 <= player.getLuck())
        {
            slowPrint("You got lucky and landed a critical hit! x2 damage!");
            damageToTake *= 2;
        }
        monster.takeDamage(damageToTake);
        slowPrint("The boss took " + to_string(damageToTake) + " damage. It now has " + to_string(monster.getHealth()) + " HP remaining.");
        usleep(300000);
        slowPrint("Now the boss will attack you...");
        damageToTake = monster.getDamage() - player.getDefense();
        if(damageToTake > 0)
        {
            player.takeDamage(damageToTake);
            slowPrint("You took " + to_string(damageToTake) + " damage, you have " + to_string(player.getHealth()) + " HP remaining.");
        }
        else
        {
            slowPrint("The boss did no damage to you.");
        }
        usleep(300000);
    }
    if(player.getHealth() <= 0)
    {
        gameOver();
    }
    else
    {
        int goldToGain = rand() % 10 + 10;
        slowPrint("You defeated the boss! You gain " + to_string(goldToGain) + " gold pieces!");
        player.addGold(goldToGain);
        slowPrint("Additionally, you gain 2 skill points all around!");
        player.addDamage(2);
        player.addDefense(2);
        player.addHealth(2);
        player.addLuck(2);
        player.addDungeonCleared();
    }
}

void quest2()
{
    slowPrint("You decide to head southwest and search for the tower...");
    slowPrint("After many days of searching, you come across the old ruins. It appears to be abandoned, but then you notice a small trapdoor");
    slowPrint("You slowly climb down the ladder, emerging in a deep labyrinth...");
    int x = 0;
    int y = 0;
    string orientation = "north";
    string direction;
    while(x != 2 && y != 2)
    {
        if(x == 0 && y == 0)
        {
            slowPrint("The first room appears to be completely barren, except for a sign pointing towards the right passage.");
            slowPrint("There are 3 passages: one leading to the left, one straight ahead, and one to the right.");
        }
        else if((x == -1 && y == 0) || (x == 0 && y == 1) || (x == -2 && y == 1) || (x == -2 && y == 2) || (x == -1 && y == 3) || (x == 1 && y == 2) || (x == 2 && y == 1) || (x == 1 && y == 0))
        {
            slowPrint("There is only one passage leading out of the room: straight ahead");
        }
        else if(x == 2 && y == 0)
        {
            if(orientation == "east")
                slowPrint("The room curves heavily, leaving only one option: going left");
            if(orientation == "south")
                slowPrint("The room curves heavily, giving you the only option of right");
        }
        else if(x == -2 && y == 0)
        {
            if(orientation == "west")
                slowPrint("The room appears to be completely barren, except for one wooden door on the right");
            if(orientation == "south")
                slowPrint("The room appears to be completely barren, except for one wooden door on the left.");
        }
        else if(x == -2 && y == 3)
        {
            if(orientation == "north")
                slowPrint("You have reached the far corner of the dungeon! There is only one door - heading right");
            if(orientation == "west")
                slowPrint("You have reached the far corner of the dungeon! There is only one door - leading left");
        }
        else if(x == 0 && y == 3)
        {
            if(orientation == "north")
                slowPrint("The cold room curves towards the left... it seems that you only have one option.");
            if(orientation == "east")
                slowPrint("The cold, bricked-up room curves towards the right, leaving you only one option.");
        }
        else if(x == 0 && y == 2)
        {
            if(orientation == "north")
                slowPrint("This room splits into many different passages, one leading straight ahead, while the other curves right.");
            if(orientation == "west")
                slowPrint("This room splits in two, with two different doors opposite of each other. Left, or right?");
            if(orientation == "south")
                slowPrint("This room gives you many decisions! Straight or left?");
        }
        slowPrint("Which way do you decide to go? ('straight', 'left', 'right')");
        cin >> direction;
        cout << "orientation: " + orientation + " direction: " + direction << endl;
        if(orientation == "north")
        {
            if(direction == "left")
            {
                x -= 1;
                orientation = "west";
            }
            else if(direction == "straight")
            {
                y += 1;
            }
            else if(direction == "right")
            {
                x += 1;
                orientation = "east";
            }
        }
        else if(orientation == "east")
        {
            if(direction == "left")
            {
                y += 1;
                orientation == "north";
            }
            else if(direction == "straight")
            {
                x += 1;
            }
            else if(direction == "right")
            {
                y -= 1;
                orientation == "south";
            }
        }
        else if(orientation == "south")
        {
            if(direction == "left")
            {
                x += 1;
                orientation = "east";
            }
            else if(direction == "straight")
            {
                y -= 1;
            }
            else if(direction == "right")
            {
                x -= 1;
                orientation == "west";
            }
        }
        else if(orientation == "west")
        {
            if(direction == "left")
            {
                y -= 1;
                orientation = "south";
            }
            else if(direction == "straight")
            {
                x -= 1;
            }
            else if(direction == "right")
            {
                y += 1;
                orientation = "north";
            }
        }
    }
    slowPrint("You have finally discovered the king! He appears ancient, and very weak.");
    slowPrint("He says that he is sorry for tormenting the villagers and taxing them beyond reasonable measure for all their life.");
    slowPrint("He doesn't want to waste away any longer...");
    slowPrint("Do you put him out of his misery ('kill'), or leave him to wither away on his own ('leave')");
    string decision = "";
    cin >> decision;
    while (!(decision == "kill" || decision == "Kill" || decision == "leave" || decision == "Leave"))
    {
        slowPrint("That wasn't one of the decisions! please input either 'kill' or 'leave'");
        cin >> decision;
    }
    if(decision == "kill" || decision == "Kill")
    {
        slowPrint("You have decided to kill the old king... what kind of monster would do that?");
        slowPrint("As punishment, you must sit here for a full 100 seconds before continuing.");
        usleep(10000000);
    }
    else if(decision == "leave" || decision == "Leave")
    {
        slowPrint("You've decided to leave the old king to die on his own.");
        slowPrint("As you turn to leave, the king cries out for you to wait.");
        slowPrint("You turn back, and he reaches beneath his crumbling form. 'Take this...' he croaks, revealing his battered crown.");
        slowPrint("+10 to all stats!");
        player.addDamage(10);
        player.addDefense(10);
        player.addHealth(10);
        player.addLuck(10);
        slowPrint("You retrace your steps and make your way back to town.");
    }
}
void quest3()
{
    slowPrint("You've decided to rescue the lost kitten.");
    slowPrint("Talk to the villagers to determine where the kitten is.");
    usleep(300000);
    cout << endl;
    slowPrint("Villagers to interrogate:");
    slowPrint("1. Herman");
    slowPrint("2. Jack");
    slowPrint("3. Daniel");
    slowPrint("4. Brianna");

    string villager;
    cout << endl;
    slowPrint("Input a name to choose one of the villagers, or 'Guess' to guess where the kitten is:");
    cin >> villager;
    while(villager != "guess" && villager != "Guess")
    {
        if(villager == "herman" || villager == "Herman" || villager == "1")
        {
            slowPrint("You decided to interrogate Herman.");
            usleep(300000);
            slowPrint("Herman: 'I have never seen that lost kitten before! I've just been here making bread from flour and water. Though some of my bread keeps disappearing...'");
        }
        else if(villager == "jack" || villager == "Jack" || villager == "2")
        {
            slowPrint("You decided to interrogate the villager Jack.");
            usleep(300000);
            slowPrint("Jack: 'Aye, I heard about the lost kitty. I last saw it over by Dan's house, last Wednesday. I hear strange noises from that house at night, might be the cat.'");
        }
        else if(villager == "daniel" || villager == "Daniel" || villager == "3")
        {
            slowPrint("You decided to interrogate the villager Daniel.");
            usleep(300000);
            slowPrint("Daniel: 'Whaaaaattt... I haven't heard anything about a cat! And you can't search my house, it's against the law! I have my rights!'");
        }
        else if(villager == "brianna" || villager == "Brianna" || villager == "4")
        {
            slowPrint("You decided to interrogate the villager Brianna.");
            usleep(300000);
            slowPrint("Brianna: 'Oh, I haven't seen the lost cat, though I would like to have one someday...");
        }
        else
        {
            slowPrint("That wasn't a villager's name!");
        }
        cout << endl;
        slowPrint("Choose another villager to talk to, or say 'Guess' to guess where the lost cat has gone.");
        cin >> villager;
    }
    slowPrint("Which villager do you think took the kitty?");
    cin >> villager;
    while(villager != "daniel" && villager != "Daniel")
    {
        slowPrint("Nope, that villager is innocent!");
        slowPrint("Pick another villager: ");
        cin >> villager;
    }
    slowPrint("You got it right! Daniel kidnapped the cat and hid it in his basement");
    slowPrint("For your investigative work, the villagers collectively award you 5 gold pieces");
    player.addGold(5);
}
void quest4() //figure out how to unpoison the local well
{
    slowPrint("You've chosen to unpoison the local well! All the locals cheer in excitement!");
    slowPrint("As you approach the well, you almost vomit from the stench alone.");
    string colors[] = {"violet", "orange", "mildew green", "hazel brown"};
    string color = colors[rand() % 4];
    slowPrint("It appears to have a " + color + " color to it.");
    slowPrint("The local Apothecary comes up to you and tells you that he can help. He recites all the potions that he knows:");
    cout << "1. Cobra venom - turns water orange and produces a foul oder. The cure is tossing in fresh dandelions" << endl;
    cout << "2. Nightshade berries added to anything will turn the substance a deep purple. The cure is adding blueberries." << endl;
    cout << "3. The vomit of a drunken man will poison any water, turning it a light green. The solution is to dilute the water." << endl;
    cout << "4. Too many acorns in the well will cause it to turn a murky brown. The solution is to drain and refill it." << endl;

    slowPrint("Which substance will you add to the well?");
    slowPrint("Choices: 'dandelions', 'blueberries', 'water', 'drain'");
    string decision;
    cin >> decision;
    bool success = false;
    if((color == "orange" && decision == "dandelions") || (color == "violet" && decision == "blueberries") || (color == "mildew green" && decision == "water") || (color == "hazel brown" && decision == "drain"))
        success = true;
    if(success)
    {
        slowPrint("You successfully cleared the well! +5 gold pieces and +2 stats all around");
        player.addDamage(2);
        player.addDefense(2);
        player.addGold(5);
        player.addHealth(2);
        player.addLuck(2);
    }
    else
    {
        slowPrint("You put in the wrong ingredient! All the villagers get angry and beat you with sticks. -10 health");
        player.takeDamage(10);
        if(player.getHealth() <= 0)
            gameOver();
    }
}
void quest5() //collect 5 flowers for the local wedding
{
    string flower;
    int totalFlowers = 0;
    string flowers[] = {"rose", "roses", "poppies", "poppy", "cornflower", "cornflowers", "tulips", "tulip", "lilly", "lillies", "azalea", "azaleas", "daffodil", "daffodils", "chrysanthemum", "chrysanthemums", "carnation", "carnations", "daisy", "daisies", "iris", "lavender", "orchid", "orchids", "petunia", "petunias", "sunflower", "sunflowers", "violet", "violets"};
    string alreadyUsedArray[] = {"", "", "", "", ""};
    slowPrint("The new king and queen are getting married! For the ceremony, they require 5 different kinds of flowers.");
    while(totalFlowers < 5)
    {
        slowPrint("Please input a kind of flower:");
        bool inList = false;
        bool alreadyUsed = false;
        cin >> flower;
        for(int x = 0; x < (sizeof(flowers) / sizeof(flowers[0])); x++)
        {
            if(flower == flowers[x])
            {
                for(int y = 0; y < 5; y++)
                {
                    if(flower == alreadyUsedArray[y])
                    {
                        alreadyUsed = true;
                    }
                }
                if(!alreadyUsed)
                {
                    alreadyUsedArray[totalFlowers] = flower;
                    totalFlowers += 1;
                    inList = true;
                    cout << "The king thanks you for your service! Now find " << (5 - totalFlowers) << " more." << endl;
                }
                else
                {
                    slowPrint("You've already used that kind of flower!");
                    slowPrint("The king is very displeased and hits you on the head with a stick. -3 health");
                    player.takeDamage(3);
                }
            }
        }
        if(!inList)
        {
            slowPrint("That is not a correct name of a flower!");
            slowPrint("The king is displeased with your trickery! He hits you on the head with a stick and you lose 3 health as a punishment");
            player.takeDamage(3);
        }
    }
    slowPrint("You have successfully collected 5 different kinds of flowers for the royal couple!");
    cout << "They are very happy with your ";
    for(int x = 0; x < 4; x++)
    {
        cout << alreadyUsedArray[x] + ", ";
    }
    cout << "and " + alreadyUsedArray[4] + ".";
    slowPrint("You gain 25 gold for your troubles.");
    player.addGold(25);

}
void visitTheTavern()
{
    slowPrint("You decide to visit the local tavern.");
    slowPrint("Upon heading inside, you notice the town bulletin board. Here people have pinned quests for brave adventurers such as yourself to undertake!\n");
    slowPrint("This week's quests are the following:");
    int alreadyUsed[3] = {-1, -1, -1};
    int counter = 0;
    for (int x = 0; x < 3; x++)
    {
        srand(time(NULL));
        int temp = rand() % 5;
        bool exists = !(alreadyUsed[0] == temp || alreadyUsed[1] == temp || alreadyUsed[2] == temp);
        if(exists == 1)
        {
            alreadyUsed[counter] = temp;
            cout << to_string(counter+1) + ". ";
            slowPrint(quests[temp]);
            counter += 1;
        }
        else
        {
            x -= 1;
        }
    }
    cout << "Which quest would you like to undertake? Select the number: ";
    int questNumber;
    cin >> questNumber;
    questName = quests[alreadyUsed[questNumber-1]];
    if(questName == quests[0])
        quest1();
    else if(questName == quests[1])
        quest2();
    else if(questName == quests[2])
        quest3();
    else if(questName == quests[3])
        quest4();
    else if(questName == quests[4])
        quest5();
    slowPrint("Congrats on completing your quest!");
    backToTown();
}
void displayIntro()
{
    slowPrint("Long ago, centuries before the invention of C++, one brave warrior set off to conquer all of the lands.\n");
    slowPrint("You, are that brave warrior! What is your name, hero?");
    string name = "";
    cin >> name;
    slowPrint("Welcome, " + name);
    visitTheTavern();
}
void backToTown()
{
    string decision;
    slowPrint("You may either visit the tavern ('tavern'), visit the village shop ('shop'), or save your progress & quit the game ('save').");
    slowPrint("Which option would you like to do?");
    cin >> decision;
    if(decision == "tavern" || decision == "Tavern")
    {
        visitTheTavern();
    }
    else if(decision == "shop" || decision == "Shop")
    {
        visitTheShop();
    }
    else if(decision == "save" || decision == "Save" || decision == "quit" || decision == "Quit");
    {
        slowPrint("Your save code is: ");
        string saveCode = "" + to_string(player.getDamage()) + "." + to_string(player.getDefense()) + "." + to_string(player.getDungeonsCleared()) + "." + to_string(player.getGold()) + "." + to_string(player.getHealth()) + "." + to_string(player.getLuck());
        slowPrint(saveCode);
        exit(0);
    }
}
void visitTheShop()
{
    string items[] = {"A great sword, giving its wearer a mighty boost to damage. (10 gold)", "A gigantic wooden shield, carved from the eldest Oak Tree in the forest. (5 gold)", "A yellow amulet, shimmering in the candlelight. (12 gold)", "A green amulet that seems to be calling to you. (20 gold)", "A red elixar, perched on top of the wooden desk. (5 gold)"};
    slowPrint("You decide to visit the shop!");
    slowPrint("The elderly shopkeeper shuffles out from behind his counter as you enter, causing that little bell above the door to ring.");
    slowPrint("'An adventurer!' He proclaims. 'I haven't seen one of your kind in ages! I have all this neat stuff that I've been collecting, just waiting for the next great one to come along.'");
    usleep(20000);
    slowPrint("The shopkeeper has the following items for sale:");
    string alreadyUsed = items[rand() % 5];
    cout << "1. " + alreadyUsed << endl;
    string newItem = items[rand() % 5];
    while(newItem == alreadyUsed)
    {
        newItem = items[rand() % 5];
    }
    cout << "2. " + newItem;
    slowPrint("3. Exit the shop.");
    int decision;
    slowPrint("You have " + to_string(player.getGold()) + " gold.");
    slowPrint("Which option would you like? Please input a number: ");
    cin >> decision;
    if(decision == 1)
    {
        if(alreadyUsed == items[0])
        {
            slowPrint("You decide to purchase the sword!");
            if(player.getGold() >= 10)
            {
                player.subtractGold(10);
                player.addDamage(5);
                slowPrint("+5 damage");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(alreadyUsed == items[1])
        {
            slowPrint("You decide to purchase the shield!");
            if(player.getGold() >= 5)
            {
                player.subtractGold(5);
                player.addDefense(3);
                slowPrint("+3 defense");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(alreadyUsed == items[2])
        {
            slowPrint("You decide to purchase the yellow amulet!");
            if(player.getGold() >= 12)
            {
                player.subtractGold(12);
                player.addLuck(3);
                slowPrint("+3 luck");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(alreadyUsed == items[3])
        {
            slowPrint("You decide to purchase the green amulet! Wow you're rich!");
            if(player.getGold() >= 20)
            {
                player.subtractGold(20);
                player.addDamage(2);
                player.addDefense(2);
                player.addLuck(2);
                slowPrint("+2 damage, +2 defense, +2 luck");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(alreadyUsed == items[4])
        {
            slowPrint("You decide to purchase the green elixar.");
            if(player.getGold() >= 5)
            {
                player.subtractGold(5);
                player.addHealth(20);
                slowPrint("+20 Health");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        usleep(300000);
    }
    else if(decision == 2)
    {
        if(newItem == items[0])
        {
            slowPrint("You decide to purchase the sword!");
            if(player.getGold() >= 10)
            {
                player.subtractGold(10);
                player.addDamage(5);
                slowPrint("+5 damage");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(newItem == items[1])
        {
            slowPrint("You decide to purchase the shield!");
            if(player.getGold() >= 5)
            {
                player.subtractGold(5);
                player.addDefense(3);
                slowPrint("+3 defense");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(newItem == items[2])
        {
            slowPrint("You decide to purchase the yellow amulet!");
            if(player.getGold() >= 12)
            {
                player.subtractGold(12);
                player.addLuck(3);
                slowPrint("+3 luck");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(newItem == items[3])
        {
            slowPrint("You decide to purchase the green amulet! Wow you're rich!");
            if(player.getGold() >= 20)
            {
                player.subtractGold(20);
                player.addDamage(2);
                player.addDefense(2);
                player.addLuck(2);
                slowPrint("+2 damage, +2 defense, +2 luck");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        else if(newItem == items[4])
        {
            slowPrint("You decide to purchase the green elixar.");
            if(player.getGold() >= 5)
            {
                player.subtractGold(5);
                player.addHealth(20);
                slowPrint("+20 Health");
            }
            else
            {
                slowPrint("You don't have enough gold to purchase this!");
            }
        }
        usleep(300000);
    }
    backToTown();

}
int main()
{
    displayIntro();
    backToTown();
	return 0;
}
/*
Result:

*/
