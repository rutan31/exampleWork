//Created by: Matthew Rutan
//Date: 11/27/2016
//Room Header
#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
#include <string>
#include <map>
#include <set>

using namespace std;

class Thing;
class Agent;

class Room{
private:
    string roomName;
    string roomDescription;
    set <Thing*> things;
    set <Agent*> agents;
    map <string, Room*> links;

public:
    Room(string name, string description);
    string getName();
    string getDescription();
    set <Thing*> getThings();
    set <Agent*> getAgents();
    int getSize();
    int getNumAgents();
    string footSteps();
    bool hasEnemy();
    void removeAgent(Agent *a);
    void removeThing(Thing *t);
    void addThing(Thing* t);
    void addAgent(Agent* a);
    bool containsLink(string direction);
    string getRandomLink();
    void link(string direction, Room *r);
    Room *getLink(string direction);
    void printRooms();
    void printAgents(string type, string name);
};

#endif // ROOM_H_INCLUDED
