//Created by: Matthew Rutan
//Date: 11/27/2016
//Enemy Header
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "agent.h"

class Enemy : public Agent{
private:
    int wait;
    bool state;

public:
    Enemy(string name, string description):Agent(name,description){agentType="enemy"; wait=0; state=true;};
    bool act();
    string getType();
    int getWait();
    void resetWait();
    void incrementWait();
    bool getState();
};

#endif // ENEMY_H_INCLUDED
