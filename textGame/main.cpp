//Created by: Matthew Rutan
//Date: 11/27/2016
//Game Main
#include <iostream>
#include "room.h"
#include "player.h"
#include "enemy.h"
#include <vector>

using namespace std;

void initializeMap(Room *start);
bool playing(vector<Agent*> a, int numPlayers);

int main()
{
    Room *start= new Room("Entrance", "You see a large one story house in front of you.\n"
    "You look around and see that the area is surrounded by large iron gates.\n");
    initializeMap(start);

    int numPlayers=2;
    Enemy *enemy = new Enemy("Enemy 1","A Man with a Fancy Hat");
    Player *player = new Player("Player 1","Player 1");
    Player *player2 = new Player("Player 2","Player 2");

    vector<Agent*> users;
    users.push_back(enemy);
    users.push_back(player);
    users.push_back(player2);

    player->updateLocation(start);
    start->addAgent(player);

    player2->updateLocation(start);
    start->addAgent(player2);

    start->getLink("North")->addAgent(enemy);
    enemy->updateLocation(start->getLink("North"));

    cout << "Game Start: The Goal of the game is to find the Exit and Escape. Whoever escapes first wins." << endl << endl;

    string input="";

    while (playing(users,numPlayers)){
        for(int i=0; i < (int)users.size(); i++){
            if (users[i]->getType()=="player"){
                cout << endl << users[i]->getName() << " ";
                cout << users[i]->getLocation()->getDescription() << endl;
                users[i]->getLocation()->printRooms();
                if(!users[i]->getLocation()->footSteps().empty()){
                    cout << player->getLocation()->footSteps();
                }
            }

            if (users[i]->act()){
                break;
            }
        }
    }

    cout << endl << "You use the key to unlock the gate and make your escape" << endl;

    return 0;
}

//returns if a player has won
bool playing(vector<Agent*> a, int numPlayers){
    int playingCount=0;

    for (int i=0; i < (int)a.size(); i++){
        if (a[i]->getType()=="player"){
            if(a[i]->getState()){
                playingCount++;
            }
        }
    }

    return playingCount == numPlayers;
}
//creates the map and points the starting entrance to it
void initializeMap(Room *start){
    Room *foyer=new Room("Foyer", "You are in the Foyer. "
    "It is well lit by a glass chandelier in the center of the room.\n"
    "You see expensive wood furniture against a wall and the floor is made of ceramic tile.\n");
    foyer->addThing(new Thing("Clock","A ticking Wooden Grandfather Clock"));

    Room *diningRoom= new Room("Dining Room", "You are in the Dining Room. It is lit by two Candle Light bulbs attached to the a wall.\n"
    "There is also a small fireplace in a corner of the room.\n"
    "A large wooden table decorated with ornate china is in the center of the room.\n");

    Room *kitchen =new Room("Kitchen", "You are in the Kitchen. Wooden cabinets line the walls and there is a small island in the center of the room.\n"
    "You see counter tops topped with kitchen appliances and a large refrigerator.\n");

    Room *recreationRoom =new Room("Recreation Room", "You are in the Recreation Room. There is a large entertainment center against a wall\nand couch against the opposite wall.\n"
    "There is a small coffee table in the center of the room, decorated with a small decorative bowl.\n");

    Room *longHallway= new Room("Long Hallway", "You are in a Long Hallway with a small chandelier illuminating the way. A small cabinet is\nagainst one side of the wall"
    " and a small leather chair sits against the other.\n");
    longHallway->addThing(new Thing("Small Statue","A small statue in the form of a small child"));

    Room *study= new Room("Study", "You are in the Study. You see two large bookshelves lined with books against the wall. In the center of the room\n"
    "you see a large wood desk lit by a small lamp. There are many papers and folders sitting on the desk.\n");
    study->addThing(new Thing("Note", "A small note with writing. It says: Does anyone know where the key to the Front Gate is?\n"
    "I last remember having it in my pockets before the laundry was done."));

    Room *bathroom =new Room("Bathroom", "You are in a small bathroom. You see a large mirror on on the wall above a small sink. There is also\n"
    "a large white tub sitting against the wall at the other side of the room.\n");

    Room *masterBedroom= new Room("Master Bedroom", "You are in the Master Bedroom. There is a large bed against the wall decorated with fine cloth pillows\nand bedsheets."
    " There are also end tables on each side of the bed and a dresser against the opposite side of the wall.\n");

    Room *masterBathroom = new Room("Master Bathroom", "You are in the Master Bathroom. There is a large mirror lining much of the wall above a marble counter top sink.\n"
    "There is also a large marble tub on the other side of the room.\n");

    Room *washRoom= new Room("Washroom", "You are in the Washroom. There is a washer and dryer against the wall on one side of the room.\n"
    "It is a very cramped room and is lit by single light bulb hanging from the ceiling.\n");
    washRoom->addThing(new Thing("Key","An Old Key Iron Key. It is Covered with rust.\nYou Take The Key"));

    Room *sunRoom= new Room("Sun Room", "You are in the Sun Room. It has many windows and is well lit from the natural light coming from outside.\n"
    "There are also many chairs sitting to face the windows.\n");

    Room *garage = new Room("Garage", "You are in the garage. It is dark and damp and only lit by a small light ball hanging from the ceiling.\n"
    "You see evidence of cars being once parked in the garage.\n");

    Room *gateExit =new Room("Gate","You see a large black iron gate blocking a large driveway heading away from the house. It seems like an exit.\n"
    "You see the gate is locked with a large iron padlock.\n");

    start->link("North",foyer);
    start->link("South",gateExit);

    foyer->link("East",diningRoom);
    foyer->link("North",longHallway);
    foyer->link("West",study);

    study->link("North",masterBedroom);

    masterBedroom->link("West",masterBathroom);

    longHallway->link("North",recreationRoom);
    longHallway->link("West",bathroom);

    diningRoom->link("North",kitchen);

    kitchen->link("West",recreationRoom);
    kitchen->link("East",washRoom);

    recreationRoom->link("West",sunRoom);

    washRoom->link("North",garage);
}
