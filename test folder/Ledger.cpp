#include "Ledger.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//constructor that allocates memory for the header
Ledger::Ledger()
{
    cou = 0;
    header = new ledgerList;
    header->next = NULL;
    header->toname = "";
    header->fromname = "";
    header->money=0;
    header->id = cou;
}

//deconstructor that removes memory from tail to tip of the list
Ledger::~Ledger()
{
    Clear();
    delete header;
}

//Removes all the transactions except for the header
void Ledger::Clear(){
    ledgerList *newpt = new ledgerList;
    for(ledgerList *p = header; p!=NULL; p=p->next){
        if(p->next == NULL){
            newpt = p;
        }
    }

    for(newpt; newpt != header; newpt=newpt->prev){
        ledgerList *temp = new ledgerList;
        temp = newpt;
        newpt->prev->next = newpt->next;
        delete temp;
    }
}

//Adds money to list with given amount, using ToName for toname and "The Bank" for fromname
void Ledger::AddExternalMoney(string ToName, int Amount){
    cou++;
    ledgerList *temp = new ledgerList;
    temp->toname=ToName;
    temp->fromname="The Bank";
    temp->money=Amount;
    temp->id=cou;
    temp->next = header->next;
    temp->prev = header;
    temp->prev->next = temp;
}

//adds money to the list using FromName and ToName for fromname and toname respectivley with money being Amount
int Ledger::AddPayment(string FromName, string ToName, int Amount){
    cou++;
    ledgerList *temp = new ledgerList;
    temp->toname=ToName;
    temp->fromname=FromName;
    temp->money=Amount;
    temp->id=cou;
    temp->next = header->next;
    temp->prev = header;
    temp->prev->next = temp;
    return cou;
}

//removes a element of the list given the ID by finding the correct id value from the list
int Ledger::RefundPayment(int Id){
    int re = -1;
    for(ledgerList *p = header; p != NULL; p=p->next){
        if(p->id == Id){
            re = Id;
            ledgerList *todelete = new ledgerList;
            todelete = p;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete todelete;
        }
    }
    return re;
}

//removes element from the list by finding the exact element that contains FromName, ToName, and Amount
void Ledger::RefundPayment(string FromName, string ToName, int Amount){
    for(ledgerList *p = header; p != NULL; p=p->next){
        if(p->fromname==FromName && p->toname==ToName && p->money==Amount){
            ledgerList *todelete = new ledgerList;
            todelete = p;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete todelete;
        }
    }
}

//Prints all elements of the list
void Ledger::Print(){
    for(ledgerList *p = header->next; p!=NULL; p=p->next){
        std::cout<<p->toname<<" "<<"received $"<<p->money<<" "<<"from "<<p->fromname<<endl;
    }

}

//Prints only the element that contains the given string for either toname or fromname
void Ledger::Print(string UserName){
    for(ledgerList *p = header->next; p!=NULL; p=p->next){
        if(p->fromname == UserName || p->toname == UserName)
            std::cout<<p->toname<<" "<<"received $"<<p->money<<" "<<"from "<<p->fromname<<endl;
    }
}

//Settles the accounts by adding money and all unique names to the names and totalBalance vectors. The vectors
//are the same size and each element (0, 1, 2, 3...etc) represents the name and the corresponding balance
void Ledger::Settle(){
    cout<<"Settled accounts:"<<endl;
    //Fill the names vector with all the unique names
    for(ledgerList *p = header->next; p!=NULL; p=p->next){
        if(std::find(names.begin(), names.end(), p->fromname) == names.end()){
                if(p->fromname != "The Bank")
                    names.push_back(p->fromname);
        }
        if(std::find(names.begin(), names.end(), p->toname) == names.end()){
                if(p->toname != "The Bank")
                    names.push_back(p->toname);
        }
    }

    //Initialize each element of the totalBalance vector. Creates the
    //amount of elements relative to names size
    for(string s: names){
        totalBalance.push_back(0);
    }

    /*
        Fills the elements in totalBalance by finding names in the list, finding the element in the names vector,
        then either adding or subtracting the money amount from each relative name depending if it is a from name or
        to name
    */
    for(ledgerList *p = header->next; p!=NULL; p=p->next){
        if(p->fromname != "The Bank"){
            string sub = p->fromname;
            string add = p->toname;
            for(int i = 0; i<names.size(); i++){
                if(names.at(i)==sub){
                    totalBalance.at(i) -= p->money;
                }
                if(names.at(i)==add){
                    totalBalance.at(i) += p->money;
                }
            }
        }else{
            string add = p->toname;
            for(int i = 0; i<names.size(); i++){
                if(names.at(i)==add){
                    totalBalance.at(i) += p->money;
                }
            }
        }
    }

    //Prints each element in the names and totalBalance vectors
    for(int i=0; i<names.size(); i++){
        cout<<names.at(i)<<" has $"<<totalBalance.at(i)<<endl;
    }
}

//Scans the totalBalance vector and outputs the people whom are positive in money
void Ledger::InTheBlack(){
    cout<<"People who are in the black:"<<endl;
    for(int i=0; i<names.size(); i++){
        if(totalBalance.at(i)>0){
            cout<<names.at(i)<<" with $"<<totalBalance.at(i)<<endl;
        }
    }
}

//scans the totalBalance vector and outputs the people whom are negative in money
void Ledger::InTheRed(){
    cout<<"People who are in the red:"<<endl;
    for(int i=0; i<names.size(); i++){
        if(totalBalance.at(i)<0){
            cout<<names.at(i)<<" with $"<<totalBalance.at(i)<<endl;
        }
    }
}
