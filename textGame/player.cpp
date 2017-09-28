//Created by: Matthew Rutan
//Date: 11/27/2016
//Player Implementation
#include "player.h"
#include <iostream>
#include <cstdlib>

bool validateInput(string input){
    string a[]={"East", "North", "South", "West" ,"Search", "Exit"};

    for (int i=0; i < 6; i++){
        if (a[i] == input){
            return true;
        }
    }

    return false;
}

//moves player in the desired direction
void movePlayer(Player *p, string direction){
    p->getLocation()->removeAgent(p);
    p->getLocation()->getLink(direction)->addAgent(p);
    p->updateLocation(p->getLocation()->getLink(direction));
}

void spotAgents(Player *p){
    if (p->getLocation()->getNumAgents() > 1){
        cout << "You spot:\n";
        p->getLocation()->printAgents("enemy","");
        p->getLocation()->printAgents("player",p->getName());
    }
}

//searches from for items of interest or enemies
int searchRoom(Room* r){
    set <Thing*> t=r->getThings();
    int found=1;
    Thing *key;

    if(t.size()==0){
        cout << "You search the area and find no items of interest" << endl;
    }else{
        set <Thing*>::iterator it;
        cout << endl << "You search the area to find: " << endl;

        for (it=t.begin(); it != t.end(); ++it){
            Thing* x=*it;
            cout << x->getDescription() << endl;
            if (x->getName()=="Key"){
                found=-1;
                key=*it;
            }
        }
    }

    if (found == -1){
        r->removeThing(key);
    }

    return found;
}

//allows the player to move with user input returns true if a player has escaped false otherwise
bool Player::act(){
    string input="";
    bool valid=false;
    bool val=false;

    while(!valid){
        cout << this->getName() << " Enter a Direction you would like to go, Search to inspect the area or Exit to quit: ";
        getline(cin,input);

        if (input.length() > 0){
            input[0]=toupper(input[0]);

            if (validateInput(input)){
                if(input=="Search"){
                    int result=searchRoom(this->getLocation());

                    if(result < 0){
                        this->updateKey(true);
                    }

                    spotAgents(this);

                    return false;
                }else if(input=="Exit"){
                    cout << endl << "Game Exit" << endl;
                    exit(0);
                }else if (validateInput(input) && this->getLocation()->containsLink(input)){
                    valid=true;
                }
            }
        }
    }

    movePlayer(this,input);
    cout << this->getDescription() << " moves to the " << this->getLocation()->getName() << endl;

    spotAgents(this);

    if (this->getLocation()->getName() == "Gate" && this->getKeyStatus()){
        val=true;
        this->getLocation()->removeAgent(this);
        this->updateState(false);
    }

    return val;
}

void Player::updateKey(bool update){
    hasKey=update;
}

bool Player::getKeyStatus(){
    return hasKey;
}

string Player::getType(){
    return agentType;
}

void Player::updateState(bool state){
    stillPlaying=state;
}

bool Player::getState(){
    return stillPlaying;
}
