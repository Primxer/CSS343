#ifndef LEDGER_H
#define LEDGER_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct ledgerList{
    int id, money;
    string fromname, toname;
    ledgerList *next;
    ledgerList *prev;
};

class Ledger
{
    public:
        //Constructor/Destructor
        Ledger();
        ~Ledger();
        //Modify ledger
        void Clear();
        void AddExternalMoney(string, int);
        int AddPayment(string, string, int);
        int RefundPayment(int);
        void RefundPayment(string, string, int);
        //Printing ledger
        void Print();
        void Print(string);
        void Settle();
        void InTheBlack();
        void InTheRed();
    private:
        ledgerList *header;
        int cou;
        vector<string> names;
        vector<int> totalBalance;
};

#endif // LEDGER_H
