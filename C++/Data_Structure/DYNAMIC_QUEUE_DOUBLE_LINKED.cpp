#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define N 5

using namespace std;

class Node{
    public:
        Node *succ, *pred;
        int val;
        Node(){}
};

class DynamicQueue{
    private:
        Node* head, *queue;
    
    public:
        DynamicQueue(){ head = nullptr; queue = nullptr;}
        //~CodaDinamica();
        void insertNode(int);

        void deleteQueue();
        void restoreQueue();
        
        friend ostream& operator<<(ostream&, DynamicQueue&);
        void PredPrint();
        void SuccPrint();

        int HeadChecker();
        int QueueChecker();
        
    private:
        void insertHead(Node*);
        void insertQueue(Node*);
};

void DynamicQueue::insertNode(int v){
    Node* nuovo = new Node;
    nuovo->val = v;
    nuovo->succ = nullptr;

    if(this->head == nullptr)
        insertHead(nuovo);
    else{
        insertQueue(nuovo);
    }
}  

void DynamicQueue::insertHead(Node* nuovo){
        nuovo->succ = this->head;
        this->head = nuovo;

        cout << "HeadChecker: " << HeadChecker() << endl;
}

void DynamicQueue::insertQueue(Node* nuovo){
    Node* iter = this->head;
        while(iter->succ!=nullptr)
            iter = iter->succ;
    iter->succ = nuovo;
    nuovo->pred = iter;
    this->queue = nuovo;

    cout << "QueueChecker: " << QueueChecker() << endl;
}

void DynamicQueue::deleteQueue(){
    Node* tmp = this->head;
    this->head = this->head->succ;
    tmp->succ = this->head;
    this->head->pred = tmp;
}

void DynamicQueue::restoreQueue(){
    if(this->head->pred !=nullptr){
        Node* tmp = this->head;
        this->head = this->head->pred;
        this->head->succ = tmp;
    }
}

ostream& operator<<(ostream& os, DynamicQueue& obj){
    os << "Coda Dinamica: [ ";
        Node* iter = obj.head;
        while(iter!=nullptr){
            cout << iter->val << " ";
            iter = iter->succ;
        }
    os << "]" << endl;
    return os;
}

int DynamicQueue::HeadChecker(){
    return this->head->val;
}

int DynamicQueue::QueueChecker(){
    return this->queue->val;
}

void DynamicQueue::PredPrint(){
    Node* iter = new Node;
        iter = this->head;
            if(iter->pred == nullptr){
            cout << "NULL" << "<<" << iter->val << endl;
            }

        iter = this->head->succ;
        while(iter != nullptr){
            cout << iter->pred->val << ">>" << iter->val << endl;
            iter = iter->succ;
        }
}

void DynamicQueue::SuccPrint(){
    Node* iter = new Node;
        iter = this->head; 
        while(iter->succ != nullptr){
            cout << iter->val << "<<" << iter->succ->val << endl;
            iter = iter->succ;
        }
}

int main(){

    DynamicQueue c;

    c.insertNode(1);
    c.insertNode(3);
    c.insertNode(8);
    c.insertNode(9);       

    cout << endl << c;

    cout << endl << "SuccessorPrinter: " << endl;
    c.SuccPrint();
    
    cout << endl;

    cout << "PredecessorPrinter: " << endl;
    c.PredPrint();

    c.deleteQueue();

    cout << c << endl;

    cout << "SuccessorPrinter: " << endl;
    c.SuccPrint();
    cout << endl;

    cout << "PredecessorPrinter: " << endl;
    c.PredPrint();

    cout << "HeadChecker: " << c.HeadChecker() << endl;

    c.restoreQueue();

    cout << c << endl << "HeadChecker: " << c.HeadChecker() << endl;

    cout << "SuccessorPrinter: " << endl;
    c.SuccPrint();
    
    cout << endl;

    cout << "PredecessorPrinter: " << endl;    
    c.PredPrint();
}