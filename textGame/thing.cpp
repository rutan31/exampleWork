//Created by: Matthew Rutan
//Date: 11/27/2016
//Thing Implementation
#include "room.h"
#include "thing.h"
#include <iostream>

Thing::Thing(string name, string description){
    this->name=name;
    this->description=description;
}

string Thing::getName(){
    return name;
}

string Thing::getDescription(){
    return description;
}

void Thing::updateLocation(Room *r){
    location=r;
}

Room* Thing::getLocation(){
    return location;
}
