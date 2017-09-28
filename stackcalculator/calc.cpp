//Created By: Matthew Rutan
//Created on: 09/17/2016
//Synopsis: Stack Calculator for Reverse Polish Notation.

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Node {
public:
    int value;
    Node* pnext;
};

class List {
public:
    Node* first;
    int count;
};

//Prototypes
void push(List *stack1, int n);
int pop(List *stack1);
bool isOperator(char a);
int doOperation(int a, int b, char op);
void validateSpacing(string &input);
void deleteStack(List *stack1);
bool validNumber(string num);

int main(){
    string input;
    string c="y";
    int result=0, valid=1;
    //valid is used to let the program know an error has occurred during calculation.
    int location=0;
    List *stack1=new List;
    stack1->count=0;

    while(c=="y" || c=="Y"){
        cout << "Enter your expression in postfix form: ";
        getline(cin,input);
        validateSpacing(input);

        for (int i=0; i < input.length(); i++){
            location=i; //location in current number being scanned in the input.

            while(location < input.length() && input[location] != ' '){
                location++;
            }//loop through a "number" until space is reached or end.

            if(!isOperator(input[location-1])){ //check if last character before space was an operator.
                if (!validNumber(input.substr(i,location-i))){
                    cout << "Invalid Input" << endl;
                    valid=0;
                    break;
                } //check for invalid characters in the number.

                int num=atoi(input.substr(i,location-i).c_str()); //convert string to number
                push(stack1, num);

                if (location == input.length()){ //number is last thing input -> invalid
                    cout << "Invalid Expression" << endl;
                    valid=0;
                    break;
                }
            }else if(stack1->count > 1){
                int op2=pop(stack1);
                int op1=pop(stack1);
                result=doOperation(op1,op2,input[i]);
                push(stack1,result);
            }else{
                cout << "Invalid Expression" << endl;
                valid=0;
                break;
            }

            i=location; //update i to current space
        }

        if (stack1->count == 0 && valid == 1){ //checks for validity in the input
            cout << "Invalid Expression" << endl;
        }else if(valid == 1){
            result=pop(stack1);
            if (stack1->count !=0){
                cout << "Invalid Expression" << endl;
            }else{
                cout << "Result: " << result << endl;
            }
        }

        deleteStack(stack1);
        valid=1;

        cout << endl << "Calculate another expression?(y or n): ";
        getline(cin,c);
    }

    return 0;
}

/*returns and removes the top element of the stack*/
int pop(List *stack1){
    int n=stack1->first->value;

    if (stack1->count > 1){
        Node *x=stack1->first;
        stack1->first=x->pnext;
        stack1->count--;
        delete x;
    }else{
        delete stack1->first;
        stack1->count--;
    }

    return n;
}

/*clears stack*/
void deleteStack(List *stack1){
    if (stack1->count > 0){
        Node *x;
        for (int i=0; i < stack1->count; i++){
            x=stack1->first;
            stack1->first=x->pnext;
            delete x;
        }

        stack1->first=NULL;
        stack1->count=0;
    }
}

/*adds the value, n, to stack*/
void push(List *stack1, int n){
    if (stack1->count == 0){
        Node *x= new Node;
        x->value=n;
        stack1->first=x;
        stack1->count++;
    }else{
        Node *x= new Node;
        x->value=n;
        x->pnext=stack1->first;
        stack1->first=x;
        stack1->count++;
    }
}

/*does the specified operation determined by 'op' on a and b*/
int doOperation(int a, int b, char op){
    int result=0;

    if (op == '+'){
        result=a+b;
    }else if(op == '-'){
        result=a-b;
    }else if(op == '*'){
        result=a*b;
    }else{
        result=a/b;
    }

    return result;
}

/*Adds spaces between operators if the input does not contain spaces
so the program will not crash. User input without proper spacing
will almost always result in invalid input.*/
void validateSpacing(string &input){
    if (input.length() > 1){
        for (int i=0; i < input.length(); i++){
            if (isOperator(input[i])){
                if (i==0){
                    if (input[i+1] != ' '){
                        input=input.substr(0,i+1)+" "+input.substr((i+1),input.length());
                    }
                }else if(i==(input.length()-1)){
                    if(input[i-1] != ' '){
                        input=input.substr(0,input.length()-1)+" "+input.substr(input.length()-1,input.length());
                    }
                }else if(input[i-1] != ' ' && input[i+1] != ' '){
                    input=input.substr(0,i)+" "+input[i]+" "+input.substr(i+1,input.length());
                }else if(input[i-1] != ' '){
                    input=input.substr(0,i)+" "+input.substr(i,input.length());
                }else if(input[i+1] != ' '){
                    input=input.substr(0,i+1)+" "+input.substr(i+1,input.length());
                }
            }
        }
    }
}

/* Checks supposed number for invalid characters. Returns
false if invalid*/
bool validNumber(string num){
    for (int i=0; i < num.length(); i++){
        if(num[i]-'0' > 9 || num[i]-'0' < 0){
            return false;
        }
    }

    return true;
}

/*return whether 'a' is an operator character*/
bool isOperator(char a){
    const char op[]={'+', '-', '*', '/'};

    for (int k=0; k < 4; k++){
        if (op[k] == a){
            return true;
        }
    }

    return false;
}
