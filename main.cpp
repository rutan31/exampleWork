//Created by: Matthew Rutan
//Date: 10/4/2016
//Synopsis: Evaluates an expression entered by the user using a tree structure.

#include <iostream>
#include <string>
#include <cmath>
#include "math_tree.h"
#include "calc_parser.h"

using namespace std;

//checks if 'op' is a function like cos, sin etc.
//returns true if that is the case, otherwise false
bool isMathFunc(string op){
    string a[7]={"sin", "cos", "exp", "log", "tan", "abs", "log10"};
    int i=0;

    while (i < 7){
        if (op == a[i]){
            return true;
        }

        i++;
    }

    return false;
}

//evaluates math functions such cos, tan, log etc.
//returns math function value of 'val'
double evalOp(string op, double val)
{
    if (op == "cos"){
        return cos(val);
    }else if(op == "sin"){
        return sin(val);
    }else if(op == "exp"){
        return exp(val);
    }else if(op == "log"){
        return log(val);
    }else if(op == "tan"){
        return tan(val);
    }else if(op == "log10"){
        return log10(val);
    }else{
        return abs(val);
    }
}

//returns value of 'val1' 'op' 'val2'
double evalOp(string op, double val1, double val2)
{
    if(op == "+"){
        return val1+val2;
    }else if(op == "-"){
        return val1-val2;
    }else if(op == "*"){
        return val1*val2;
    }else if(op == "/"){
        return val1/val2;
    }else{
        return pow(val1,val2);
    }
}

//evaluates an expression 'Tree' and returns the numerical value
double eval(Tree *root)
{
    double result=0; //local variable for result of expression value

    if (!root->op.empty()){
        if (isMathFunc(root->op)){
            result+=evalOp(root->op, eval(root->left));
        }else{
            result+=evalOp(root->op, eval(root->left), eval(root->right));
        }
    }else{
        result+=root->val;
    }

    return result;
}

// this is a global variable used by the parser
Tree* math_tree;

int main()
{
    //hand-code a tree for this expression:
    //sin(3.14159/4.0)+cos(8.0*2.0)
    Tree r;
    r.op="+";

    Tree v1;
    v1.op="sin";
    v1.right=NULL;

    Tree v2;
    v2.op="/";

    Tree v3;
    v3.val=3.14159;
    v3.left=NULL;
    v3.right=NULL;

    Tree v4;
    v4.val=4.0;
    v4.right=NULL;
    v4.left=NULL;

    Tree v5;
    v5.op="cos";
    v5.right=NULL;

    Tree v6;
    v6.op="*";

    Tree v7;
    v7.val=8.0;
    v7.left=NULL;
    v7.right=NULL;

    Tree v8;
    v8.val=2.0;
    v8.left=NULL;
    v8.right=NULL;

    r.left=&v1;
    r.right=&v5;
    v1.left=&v2;
    v2.left=&v3;
    v2.right=&v4;
    v5.left=&v6;
    v6.left=&v7;
    v6.right=&v8;

    print_ascii_tree(&r);

    cout << "Expression: sin(3.14159/4.0) + cos(8.0*2.0)" << endl;
    cout << "Result: " << eval(&r) << endl << endl << endl;

    // this is the user-input loop; there is no need to change it
    while(true)
    {
        Parser parser;
        cout << "Enter expression: ";

        // this function gets the input and does the parsing
        parser.yyparse();

        // the yyparse() function sets the global variable math_tree
        // to a new tree; if that tree is NULL (no tree), just quit
        if(math_tree == NULL)
            break;

        // otherwise, print the tree
        print_ascii_tree(math_tree);

        // and evaluate it
        cout << "Result: " << eval(math_tree) << endl << endl;

        // reset the tree back to NULL before looping
        math_tree = NULL;
    }

    return 0;
}
