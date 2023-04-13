#include <iostream>
#include <iomanip>
#include <cmath>
#include "USER_ACCOUNT.h"
#include "BANK_ACCOUNT.h"

using namespace std;

class Node{
    private:
        User* user;
        Node* next;
        Node* prec;
        Bank* bank;
    public:
        Node(User* us, Bank* b) : user(us), bank(b){}

        Node* getNext();
        Node* getPrec();

        User* getUser();
        Bank* getBank();

        void setNext();
        void setNext(Node*);
        void setPrec();
        void setPrec(Node*);

        double Money();
        void Identify();
};

Bank* Node::getBank(){
    return this->bank;
}

User* Node::getUser(){
    return this->user;
}

double Node::Money(){
    //cout << this->bank->getMoney() << endl;
    return this->bank->getMoney();
}

void Node::Identify(){
    cout << this->user->getIdentity() << endl;
}

Node* Node::getNext(){
    return next;
}

Node* Node::getPrec(){
    return prec;
}

void Node::setPrec(Node* n){
    this->prec = n;
}

void Node::setPrec(){
    this->prec = nullptr;
}

void Node::setNext(){
    this->next = nullptr;
}

void Node::setNext(Node* n){
    this->next = n;
}

class List{
    private:
        Node* root;
    
    public:
        List() : root(nullptr){}

        Node* getRoot();

        void insertNode(User*, Bank*);
        Node* researchNode(string);
        void removeNode(string);

    friend ostream& operator<<(ostream& out, const List& ls);
};

Node* List::getRoot(){
    return root;
}

void List::insertNode(User* u, Bank* b){
    Node* newNode = new Node(u, b);
    Node* iter = this->root;

    if(this->root == nullptr){
        newNode->setPrec();
        newNode->setNext();
        this->root = newNode;
    }
    else if(this->root->Money() >= b->getMoney()){
        newNode->setNext(this->root);
        this->root = newNode;
    }else{
        while(  (iter->getNext()!=nullptr)  && (b->getMoney() > iter->getNext()->Money()))
            iter = iter->getNext();
            newNode->setNext(iter->getNext());
            iter->setNext(newNode);
        }

}


Node* List::researchNode(string C){
    Node* iter = this->root;
        while(iter != nullptr){
            if(iter->getUser()->getName() == C){
                //cout << "Research Complete: " << iter->getUser()->getName() << ", Money: " << iter->getBank()->getMoney() << endl;
                return iter;
            }
            iter = iter->getNext();
        }
    cout << "User: " << C << " Doesn't exist" << endl;
    return nullptr;
}

ostream& operator<<(ostream& out, const List& ls){
    Node* iter = ls.root;
// for(Nodo* iter=ls.testa;iter!=nullptr;iter=iter->succ)
    while(iter!=nullptr){
        out << iter->getUser()->getName() << " --> ";
            if(iter->getNext() != nullptr)
                iter = iter->getNext();
            else{
                cout << "NULL" << endl;
                break;
            }
    }
    return out;
}
