//Created by: Matthew Rutan
//Date: 11/27/2016
//Thing Header
#ifndef THING_H_INCLUDED
#define THING_H_INCLUDED
#include <string>
#include "room.h"

class Thing{
private:
    string name;
    string description;

protected:
    Room* location;

public:
    Thing(string name, string description);
    string getName();
    string getDescription();
    Room* getLocation();
    void updateLocation(Room *r);
};

#endif // THING_H_INCLUDED
