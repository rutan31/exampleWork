//Created by: Matthew Rutan
//Date: 11/27/2016
//Room Implementation
#include "room.h"
#include "thing.h"
#include "player.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//Function for link rooms
string inverseDirection(string direction){
    if (direction == "North"){
        return "South";
    }else if (direction == "South"){
        return "North";
    }else if (direction == "East"){
        return "West";
    }else{
        return "East";
    }
}

string Room::getName(){
    return roomName;
}

string Room::getDescription(){
    return roomDescription;
}

int Room::getSize(){
    return (int) links.size();
}

int Room::getNumAgents(){
    return (int) agents.size();
}

set<Thing*> Room::getThings(){
    return things;
}

set<Agent*> Room::getAgents(){
    return agents;
}

//returns a string with details of enemies around a room
string Room::footSteps(){
    map <string, Room*>::iterator it;
    string steps="";

    for(it=links.begin(); it != links.end(); ++it){
        if(it->second->hasEnemy()){
            steps=steps+"You hear footsteps to the " + it->first + ".\n";
        }
    }

    return steps;
}

//returns if a room has an enemy
bool Room::hasEnemy(){
    set <Agent*>::iterator it;
    bool enemy=false;
    Agent *t;

    for(it=this->agents.begin(); it!=this->agents.end(); ++it){
        t=*it;
        if(t->getType()=="enemy"){
            enemy=true;
            break;
        }
    }

    return enemy;
}

Room::Room(string name, string description){
    roomName=name;
    roomDescription=description;
}

//prints agents of type 'type' and without name 'name'
void Room::printAgents(string type, string name){
    set <Agent*>::iterator it;

    for(it=this->agents.begin(); it != this->agents.end(); ++it){
        Agent* a=*it;
        if (a->getType()==type && a->getName() != name){
            cout << a->getDescription() << endl;
        }
    }
}

//returns a random direction based on agent type
string Room::getRandomLink(){
    srand(time(NULL));

    int r=rand() % links.size();

    if (r < 0){
        r=r*-1;
    }

    map <string, Room*>::iterator it;
    int i=0;
    string direction="";

    for(it=this->links.begin(); it != this->links.end(); ++it){
        if(i==r){
            direction=it->first;
            break;
        }

        i++;
    }

    return direction;
}

void Room::addThing(Thing* t){
    things.insert(t);
}

void Room::addAgent(Agent *a){
    this->agents.insert(a);
}

void Room::removeAgent(Agent *a){
    agents.erase(a);
}

void Room::removeThing(Thing *t){
    things.erase(t);
}

Room* Room::getLink(string direction){
    return this->links[direction];
}

void Room::link(string direction, Room *r){
    this->links[direction]=r;
    r->links[inverseDirection(direction)]=this;
}

//print all connected rooms to a room
void Room::printRooms(){
    map <string, Room*>::iterator it;

    for(it=this->links.begin(); it != this->links.end(); ++it){
        cout << "To the " << it->first << " you see a " << it->second->getName() << endl;
    }

    cout << endl;
}

//returns if a room has a link in a desired direction
bool Room::containsLink(string direction){
    map <string, Room*>::iterator it;

    for(it=this->links.begin(); it != this->links.end(); ++it){
        if (it->first == direction){
            return true;
        }
    }

    return false;
}
