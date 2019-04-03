#include "cpu.h"
#include <iostream>
#include<string>
using namespace std;

/*
Constructor Method:
Sets accumulator to 0 and initializes the stack object
*/
CPU::CPU(){
    acc = 0;
    myStack;
}

/*
Deconstructor Method:
Calls clear method to remove method from std::list
*/
CPU::~CPU(){
    myStack.clear();
}
/*
Load Program:
given a string which is assumed is a file name
open the file given the filename
if stack is not empty reset stack by calling clear
*/
void CPU::LoadProgram(string filename){
    myFile.open(filename);
    if(!myStack.empty()){
        cout<<"Stack is not empty, clearing stack..."<<endl;
        myStack.clear();
    }
    acc = 0;
}

/*
Run:
No parameters
while there are still lines in the file read each one
if they contain any of the given keywords call their respective methods
close file once done and return accumulator
*/
int CPU::Run(){
    string input;
    while(getline(myFile, input, '\n')){
        if(input.find("PSH") != string::npos){
            int temp;
            temp = stoi(input.substr(3, 5));
            push(temp);
        }else if(input.find("POP") != string::npos){
            pop();
        }else if(input.find("ADD") != string::npos){
            add();
        }else if(input.find("SUB") != string::npos){
            sub();
        }else if(input.find("CMP") != string::npos){
            cmp();
        }
    }
    myFile.close();
    return acc;
}

/*
Next:
no parameters
designed to read file one line per call
if no line to read the return -1
if line contains given keyword call the respective methods and 'eat' next empty return
*/
int CPU::Next(){
    string input;
    if(!getline(myFile, input, '\n')){
        return -1;
        myFile.close();
    }
    if(input.find("PSH") != string::npos){
        int temp;
        temp = stoi(input.substr(3, 5));
        push(temp);
        getline(myFile, input, '\n');
    }else if(input.find("POP") != string::npos){
        pop();
        getline(myFile, input, '\n');
    }else if(input.find("ADD") != string::npos){
        add();
        getline(myFile, input, '\n');
    }else if(input.find("SUB") != string::npos){
        sub();
        getline(myFile, input, '\n');
    }else if(input.find("CMP") != string::npos){
        cmp();
        getline(myFile, input, '\n');
    }
    return 0;
}

/*
Print:
no parameters
prints out all current elements that are in the stack by looping through
the stack list
*/
void CPU::Print(){
    cout<<"Current Stack: "<<endl;
    for(list<int>::iterator i = myStack.begin(); i!=myStack.end(); i++){
        cout<<*i<<endl;
    }
}

/*
push:
parameter is given value to push onto the stack/list
pushes onto front of the list/stack
*/
void CPU::push(int val){
    myStack.push_front(val);
}

/*
pop:
no parameters
sets accumulator to the top of the stack/list then pops off the front
*/
void CPU::pop(){
    acc = myStack.front();
    myStack.pop_front();
}

/*
add:
no parameters
reads and adds the front element on the stack/list to the accumulator
pops off front of stack/list
*/
void CPU::add(){
    int temp = myStack.front();
    acc = acc + temp;
    myStack.pop_front();
}

/*
sub:
no parameters
reads and subtracts the front element on the stack/list from the accumulator
pops off the front of stack/list
*/
void CPU::sub(){
    acc -= myStack.front();
    myStack.pop_front();
}

/*
cmp:
no parameters
reads value, temp, off the front of the stack/list and pops off the front
compares temp against accumulator
if less than push to front of stack/list a -1
if greater than push to front of stack/list a 1
if equal push to front of stack/list a 0
*/
void CPU::cmp(){
    int temp = myStack.front();
    myStack.pop_front();
    if(temp>acc)
        myStack.push_front(1);
    else if(temp<acc)
        myStack.push_front(-1);
    else
        myStack.push_front(0);
}

