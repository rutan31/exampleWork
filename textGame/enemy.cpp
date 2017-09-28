//Created by: Matthew Rutan
//Date: 11/27/2016
//Enemy Implementation
#include "enemy.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

//allows enemy to move in random directions, always returns false
bool Enemy::act(){
    string direction=this->getLocation()->getRandomLink();

    if(!direction.empty() && this->getWait()!= 3){
        this->getLocation()->removeAgent(this);
        this->getLocation()->getLink(direction)->addAgent(this);
        this->updateLocation(this->getLocation()->getLink(direction));
        this->incrementWait();
    }else{
        this->resetWait(); //will wait in a room after 3 moves for 1 move
    }

    return false;
}

string Enemy::getType(){
    return agentType;
}

void Enemy::incrementWait(){
    wait++;
}

void Enemy::resetWait(){
    wait=0;
}

int Enemy::getWait(){
    return wait;
}

bool Enemy::getState(){
    return state;
}
