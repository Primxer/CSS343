#ifndef CPU_H
#define CPU_H
#include <list>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class CPU
{
    //public methods/constructors/de-constructors
    public:
        CPU();
        ~CPU();
        void LoadProgram(string);
        int Run();
        int Next();
        void Print();

    //private methods/data values
    private:
        void push(int);
        void pop();
        void add();
        void sub();
        void cmp();
        int acc;
        ifstream myFile;
        list<int> myStack;
};

#endif // CPU_H
