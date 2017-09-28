//Created By: Matthew Rutan
//Data: 09/02/2016
//Synopsis: Simulates Conway's game of life.

#include<iostream>
#include<vector>
//#include<unistd.h> // linux / Mac OS X
#include<windows.h> // Windows
#include<cstdlib>
using namespace std;

// You can change the size of your world matrix in your entire code
// just by changing the values of ROWS and COLS here.
#define ROWS 21
#define COLS 80

// You can change the characters used to represent DEAD and ALIVE cells here
#define DEAD  ' '
#define ALIVE '*'

//Prototypes
int getNeighborCount(vector< vector<char> > world_copy, int row, int col, int isAlive);
void gliders(vector< vector<char> > &world);
void rPentomino(vector< vector<char> > &world);
void blinker(vector< vector<char> > &world);

void generation(vector< vector<char> > &world,
                vector< vector<char> > &world_copy)
{
    // copy the contents of world into world_copy
    for (int i=0; i < ROWS; i++){
        for (int k=0; k < COLS; k++){
            world_copy[i][k]=world[i][k];
        }
    }
    int neighborCount=0;

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if (world_copy[i][j] == ALIVE){
                neighborCount=getNeighborCount(world_copy, i, j, 1);

                if (neighborCount > 3 || neighborCount == 1 || neighborCount == 0){
                    world[i][j]=DEAD;
                }
            }else{
                neighborCount=getNeighborCount(world_copy, i, j, 0);

                if (neighborCount == 3){
                    world[i][j]=ALIVE;
                }
            }
        }
    }
}

void display(vector< vector<char> > &world)
{
    // display the 2D matrix
    // You can add more code to 'beautify' the display of the matrix
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            cout << world[i][j];
        }
        cout << endl;
    }
}

int main()
{
    vector< vector<char> > world(ROWS, vector<char>(COLS, DEAD));
    vector< vector<char> > copy(ROWS, vector<char>(COLS, DEAD));

    int user=0;

    cout << "Choose an initial state: " << endl;
    cout << "1: Blinker" << endl;
    cout << "2: rPentomino" << endl;
    cout << "3: Gliders" << endl;"Entry: ";

    while (user < 1 || user > 3){
        cout << "Entry: ";
        cin >> user;
        if (user==1){
            blinker(world);
        }else if(user==2){
            rPentomino(world);
        }else if(user==3){
            gliders(world);
        }else{
            cout << "Invalid Entry" << endl;;
        }
    }

    while(1)
    {
        // clear the screen and display the world
        system("cls");
        display(world);

        // wait for some time
        Sleep(50);

        // update the world
        generation(world, copy);
    }

    return 0;
}

//initializes world to Blinker state
void blinker(vector< vector<char> > &world){
    world[2][1]=world[2][2]=world[2][3]=ALIVE;
}

//initializes world to R-Pentomino state
void rPentomino(vector< vector<char> > &world){
    world[1][2]=world[1][3]=world[2][1]=world[2][2]=world[3][2]=ALIVE;
}
//initializes world to gliders state.
void gliders(vector< vector<char> > &world){
    world[5][1]=world[6][1]=world[6][2]=world[5][2]=world[5][11]=world[6][11]=world[7][11]=ALIVE;
    world[8][12]=world[9][13]=world[9][14]=world[4][12]=world[3][13]=world[3][14]=ALIVE;
    world[4][16]=world[5][17]=world[6][17]=world[6][18]=world[7][17]=world[8][16]=ALIVE;
    world[3][21]=world[3][22]=world[4][21]=world[4][22]=world[5][21]=world[5][22]=ALIVE;
    world[2][23]=world[6][23]=world[6][25]=world[7][25]=world[2][25]=world[1][25]=ALIVE;
    world[3][35]=world[3][36]=world[4][35]=world[4][36]=world[6][15]=ALIVE;
}

/* This function takes in the current world and a location and counts the number of alive neighbors around
that location.

The function simply goes through all possible combinations of valid locations around
and including the point. One could have simply used if statements for each scenario but, this makes
the code very long and less readable. Though, the trade off is that the point being passed is rechecked
so this is less efficient code. The isAlive parameter is used to subtract from the final count because
the final count will be 1 more than it should be due to the location being counted in the neighbor count
in the for loop. isAlive should either be 1 or 0, 1 for alive, 0 for dead.*/
int getNeighborCount(vector< vector<char> > world_copy, int row, int col, int isAlive){
    int nCount=0;

    if (col == 0){
        if (row == 0){ //Scenario: top left corner of screen
            for (int i=0; i < 2; i++){
                for (int k=0; k < 2; k++){
                    if (world_copy[row+i][col+k] == ALIVE){
                        nCount++;
                    }
                }
            }
        }else if(row == ROWS-1){ //Scenario: bottom left corner of screen
            for (int i=-1; i < 1; i++){
                for (int k=0; k < 2; k++){
                    if (world_copy[row+i][col+k] == ALIVE){
                        nCount++;
                    }
                }
            }
        }else{ //Scenario: left border of screen
            for (int i=-1; i < 2; i++){
                for (int k=0; k < 2; k++){
                    if (world_copy[row+i][col+k] == ALIVE){
                        nCount++;
                    }
                }
            }
        }
    }else if(col == COLS-1){
        if (row == 0){ //Scenario: top right corner of screen
            for (int i=0; i < 2; i++){
                for (int k=-1; k < 1; k++){
                    if (world_copy[row+i][col+k] == ALIVE){
                        nCount++;
                    }
                }
            }

        }else if(row == ROWS-1){ //Scenario: lower right corner of screen
            for (int i=-1; i < 1; i++){
                for (int k=-1; k < 1; k++){
                    if (world_copy[row+i][col+k] == ALIVE){
                        nCount++;
                    }
                }
            }

        }else{ //Scenario: right border of screen
            for (int i=-1; i < 2; i++){
                for (int k=-1; k < 1; k++){
                    if (world_copy[row+i][col+k] == ALIVE){
                        nCount++;
                    }
                }
            }
        }
    }else if (row == 0){  //Scenario: top border of screen
        for (int i=0; i < 2; i++){
            for (int k=-1; k < 2; k++){
                if (world_copy[row+i][col+k] == ALIVE){
                    nCount++;
                }
            }
        }
    }else if (row == ROWS-1){ //Scenario: bottom border of screen
        for (int i=-1; i < 1; i++){
            for (int k=-1; k < 2; k++){
                if (world_copy[row+i][col+k] == ALIVE){
                    nCount++;
                }
            }
        }

    }else{ //Scenario: anywhere else
        for (int i=-1; i < 2; i++){
            for (int k=-1; k < 2; k++){
                if (world_copy[row+i][col+k] == ALIVE){
                    nCount++;
                }
            }
        }
    }

    return nCount-isAlive; //subtracts the passed location point from the count
}
