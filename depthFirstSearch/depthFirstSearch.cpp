//Created by: Matthew Rutan
//Date: March 7, 2017
//Lab1: Depth First Search
//Email: rutan.31@osu.edu

/*----------------------------------------------README------------------------------------------------------
This code should be compiled from the console using command: 'g++ lab1.cpp' in the correct directory.
This will create a file called 'a.out' in the current directory. To run the code with your data file, type: 'a.out < your file name'

Note: the data file must be formatted to contain no spaces or text after the desired number of vertices only a newline.
This may cause incorrect results or the program to crash.

Example:
4--No spaces or text--
0 1 0 0
1 0 0 0
1 0 0 0
1 0 0 1
------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//Prototype
void dfSearch(int **tree, int *mList, int i, int n);

int main(){
    string numVertices;
    getline(cin,numVertices);
    int n=atoi(numVertices.c_str()); //get number of vertices

    int **vertices= new int*[n];
    for(int k=0; k < n; k++){
        vertices[k]=new int[n];
    }//allocate memory for matrix

    char input; //input from data file
    int *mList= new int[n]; //marked list
    int row=0;
    int col=0;
    int i=0;
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

            if (i < n){
                mList[i]=0;
                i++;
            }//initialize marking list
	    }
    }

    int numComponents=0;
    for (int i=0; i < n; i++){
        if (mList[i]==0){
            numComponents++;
            cout << "Component Traversal: ";
            dfSearch(vertices, mList, i, n);
            cout << endl;
        }//run Depth First Search
    }

    cout << "Total number of Components: " << numComponents << endl;

    for (int i=0; i < n; i++){
        delete [] vertices[i];
    }// free memory

    delete [] vertices;
    delete [] mList; //free memory

    return 0;
}

//Performs depth first search
//tree: The graph, mList: the marked list, i: the current vertex,
//n: total number of vertices
void dfSearch(int **tree, int *mList, int i, int n){
    mList[i]=1;
    cout << i+1 << " ";

    for (int j=0; j < n; j++){
        if (mList[j]==0 && tree[i][j]==1){
            dfSearch(tree,mList,j,n);
        }
    }
}
