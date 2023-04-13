#include <iostream>
#include <iomanip>
#include <cmath>
#include "LIST.h"

using namespace std;


void List::insertNode(User* u, Bank* b){
    Node* newNode = new Node(u, b);
    Node* iter = this->root;

    // caso 1: lista vuota
    if(this->root == nullptr){
        newNode->next = nullptr;
        this->root = newNode;
    }

}


Node* List::researchNode(string C){
    Node* iter = this->root;
        while(iter != nullptr){
                //if(iter->user.getCF() == C)
                    return iter;
            iter = iter->next;
        }
    return nullptr;
}