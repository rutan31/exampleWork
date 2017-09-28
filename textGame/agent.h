//Created by: Matthew Rutan
//Date: 11/27/2016
//Agent Header
#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include "thing.h"

class Agent : public Thing{
protected:
    string agentType;
    Agent(string name, string description):Thing(name,description){};

public:
    virtual bool act()=0;
    virtual string getType()=0;
    virtual bool getState()=0;
};

#endif // AGENT_H_INCLUDED
