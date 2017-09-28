//Created by: Matthew Rutan
//Date: April 4, 2017
//Lab2: Breadth First Search
//Email: rutan.31@osu.edu

/*----------------------------------------------README------------------------------------------------------
This code should be compiled from the console using command: 'g++ lab2.cpp' in the correct directory.
This will create a file called 'a.out' in the current directory. To run the code with your data file, type: 'a.out < your file name'

Note: the data file must be formatted to contain no spaces or text after the desired number of vertices only a newline.
This may cause incorrect results or the program to crash.

Example:
4--No spaces or text--
0 1 0 0
1 0 0 0
1 0 0 0
1 0 0 1

Queue was only implemented with basic, needed functionality (enqueue and dequeue).
------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/* Queue Structure */
class Node {
public:
    int value;
    Node* pnext;
};

class Queue {
public:
    Node* first;
    Node* last;
    int count;
};

//Prototypes
void bfSearch(int **tree, int n);
void enqueue(Queue *q, int x);
int dequeue(Queue *q);

int main(){
    string numVertices;
    getline(cin,numVertices);
    int n=atoi(numVertices.c_str()); //get number of vertices

    int **vertices= new int*[n];
    for(int k=0; k < n; k++){
        vertices[k]=new int[n];
    }//allocate memory for matrix

    char input; //input from data file
    int row=0;
    int col=0;
    while(cin.get(input)){
        if(input == '0' || input == '1'){
            if((col+1) % n == 0 && row != n-1){
                vertices[row][col]=(int)input-'0';
                col=0;
                row++;
            }else{
                vertices[row][col]=(int)input-'0';
                col++;
            }//read input and create matrix
	    }
    }

    bfSearch(vertices, n);

    for (int i=0; i < n; i++){
        delete [] vertices[i];
    }// free memory

    delete [] vertices; //free memory

    return 0;
}

//Performs breadth first search
//tree: The graph, mList: the marked list, i: the current vertex,
//n: total number of vertices
void bfSearch(int **tree, int n){
    Queue *q = new Queue;
    q->count=0;

    int *mList= new int[n]; //marked list
    int *vDistance= new int[n]; //vertex distances
    int numComponents=0; //number of components in graph

    for (int i=0; i < n; i++){
        mList[i]=0;
        vDistance[i]=0; //initialize marked list and distances array
    }

    for (int k=0; k < n; k++){
        if (mList[k] == 0){
            mList[k]=1;
            vDistance[k]=0;
            enqueue(q,k);

            numComponents++;
            cout << endl << "Component " << numComponents << ":" << endl;
            cout << "Vertices & Distances:" << endl;

            while(q->count > 0){
                int i=dequeue(q);

                cout << i+1 << " " << vDistance[i] << endl; //print vertex with distance

                for (int j=0; j < n; j++){
                    if (tree[i][j] == 1 && mList[j] == 0){
                        enqueue(q,j);
                        mList[j]=1;
                        vDistance[j]=vDistance[i]+1;
                    }
                }
            }
        }
    }

    delete q;
    delete [] vDistance;
    delete [] mList; //free memory for dynamic structure
}

//Add x to back of Queue
void enqueue(Queue *q, int x){
    if(q->count == 0){
        Node *k=new Node;
        k->value=x;
        q->first=k;
        q->last=k;
        q->count++;
    }else{
        Node *k=new Node;
        k->value=x;
        q->last->pnext=k;
        q->last=k;
        q->count++;
    }
}

//Remove first item from Queue, return 0 if empty.
int dequeue(Queue *q){
    int val=0;

    if (q->count > 1){
        Node *x=q->first;
        val=q->first->value;
        q->first=q->first->pnext;
        q->count--;
        delete x;
    }else if(q->count == 1){
        val=q->first->value;
        delete q->first;
        q->first=q->last;
        q->last=q->first;
        q->count--;
    }

    return val;
}
