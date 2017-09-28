//Created by: Matthew Rutan
//Date: 11/27/2016
//Player Header
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "agent.h"

class Player : public Agent{
private:
    bool hasKey;
    bool stillPlaying;

public:
    Player(string name, string description):Agent(name,description){hasKey=false; agentType="player"; stillPlaying=true;};
    bool act();
    void updateKey(bool update);
    bool getKeyStatus();
    void updateState(bool state);
    bool getState();
    string getType();
};

#endif // PLAYER_H_INCLUDED
