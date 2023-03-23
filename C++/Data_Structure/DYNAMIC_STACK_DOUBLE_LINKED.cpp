#include <iostream>
#include <iomanip>
#include <cmath>
#include <typeinfo>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Node{
    public:
        int val;
        Node *succ, *pred;
        Node(){}     
}; 

class DynamicStack{
    public:
        Node* head;
        
        DynamicStack(){this->head = nullptr;}
        
        void insertNode(int);
        void HeadExtract();

        int HeadChecker();

        void PredPrint();

        friend ostream& operator<<(ostream&, DynamicStack&);

    private:
        void insertHead(Node*);
        void insertOtherNode(Node*);
};


void DynamicStack::insertNode(int v){
    Node* nuovo = new Node;
        nuovo->val = v;
    if(this->head == nullptr){
        insertHead(nuovo);
    }else{
        insertOtherNode(nuovo);
    }
}

void DynamicStack::insertHead(Node* nuovo){
    nuovo->succ = this->head;
    this->head = nuovo;
    cout << "HeadChecker: " << HeadChecker() << endl;
}

void DynamicStack::HeadExtract(){
    
}

void DynamicStack::insertOtherNode(Node* nuovo){
    nuovo->pred = this->head;
    this->head = nuovo;
    cout << "HeadChecker: " << HeadChecker() << endl;
}

int DynamicStack::HeadChecker(){
    return this->head->val;
}

void DynamicStack::PredPrint(){
    Node* iter = this->head;
    while(iter->pred != nullptr){
        cout << iter->val << ">>" << iter->pred->val << endl;
        iter = iter->pred;
    }
}

ostream& operator<<(ostream& os, DynamicStack& obj){
    os << "DynamicStack: [ ";
        Node* iter = obj.head;
        while(iter != nullptr){
            os << iter->val << " ";
            iter = iter->pred;
        }
    os << "]" << endl;
    return os;
}

int main(){
    DynamicStack s;
        s.insertNode(4);
        s.insertNode(6);
        s.insertNode(3);
        s.insertNode(2);
        s.insertNode(8);

    cout << s << endl;
    
    cout << "PredecessorPrinter: " << endl;
        s.PredPrint();
}