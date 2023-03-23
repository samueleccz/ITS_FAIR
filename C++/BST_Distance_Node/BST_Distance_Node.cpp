#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>            
#include <ctime>
#include <fstream>
#include <typeinfo>
#include <chrono>

using namespace std;

template <class H>
class Node{
    public:
        H val;
        Node<H>* right, *left, *parent; 
};

template <class H>
class BST{
    private:
        Node<H>* root;
        int nEnt;
        void postOrder(Node<H>* p) const;
        int distanceNode(Node<H>*, Node<H>*);
        
        int foundDistanceSameDirection(Node<H>*, Node<H>*);
        Node<H>* searchNode(Node<H>*, H) const;
        int directionNode(Node<H>*); //0 right 1 left
        Node<H>* foundAncient(Node<H>*, Node<H>*);
        

    public:
        BST(): root(nullptr){}
        void insertNode(H);

        Node<H>* searchNode(H) const; 
        int distanceFromRoot(H);
        int directionNode(H); //connection with private
        int distanceNode(H, H);

        template <typename U> 
        friend ostream& operator<<(ostream&, BST<U>&);
    
        void postOrder() const;
};


template <class H>
int BST<H>::directionNode(H v){
    Node<H>* n = searchNode(v);

    return directionNode(n);
}

template <class H>
int BST<H>::directionNode(Node<H>* n){
    if(n->val < root->val)
        return 1;
    else
        return 0;
}

template <class H>
Node<H>* BST<H>::searchNode(H v) const{
    return searchNode(root, v);
}

template <class H>
Node<H>* BST<H>::searchNode(Node<H>* n, H v) const{
    while((n != nullptr) && (n->val != v)){
        if(v < n->val)
            n = n->left;
        else 
            n = n->right;
    }

    if(n == nullptr)
        n = nullptr;

    return n;
}



template <class H>
int BST<H>::distanceFromRoot(H v){
    int d = 0;
    Node<H>* iter = root;
    if(searchNode(v) != nullptr){
        while((iter != nullptr) && (iter->val != v)){
            if(v < iter->val){
                iter = iter->left;
                d++;
            }
            else{
                iter = iter->right;
                d++;
            }     
        }
    } else return INT_MIN;

    return d;
}

template <class H>
Node<H>* BST<H>::foundAncient(Node<H>* n1, Node<H>* n2){
    int d1 = distanceFromRoot(n1->val), d2 = distanceFromRoot(n2->val);
    Node<H>* iter = n1, *iter2 = n2;
    
    if(d1 > d2){
    int counter = d1;
        while(counter != d2){
            iter = iter->parent;
            counter--;
        }
        while(iter->val != iter2->val){            
            iter = iter->parent;
            iter2 = iter2->parent;
        }
    }else{
    int counter = d2;
    while(counter != d1){
        iter2 = iter2->parent;
        counter--;
    }
    while(iter2->val != iter->val){            
        iter = iter->parent;
        iter2 = iter2->parent;
    }     
    }    

    return iter;
}


template <class H>
void BST<H>::insertNode(H value){
    Node<H>* nuovo = new Node<H>;
    Node<H>* x = root, *y = nullptr;

    nuovo->val = value;
    nuovo->left = nuovo->right = nullptr;

    while(x != nullptr){
        y=x;
            if(value < x->val){
                x = x->left;
            }else{
                x = x->right;
            }
    }

    nuovo->parent = y;

    if(y == nullptr){
        this->root = nuovo;
    }else if(nuovo->val < y->val){
        y->left = nuovo;
    }else{
        y->right = nuovo;
    }
    this->nEnt++;
}

template <class H>
int BST<H>::foundDistanceSameDirection(Node<H>* n1, Node<H>* n2){
    int d1 = distanceFromRoot(n1->val), d2 = distanceFromRoot(n2->val);
    int d = 0;

    if(d1 == d2){ //CASO 1
        d = (d1 + d2) - (2 * distanceFromRoot(n1->parent->val)); 

    }else if(d1 > d2 && ((d2 != 0) || (d2 == 0))){ //2
        Node<H>* ancient = foundAncient(n1, n2);

        int da = distanceFromRoot(ancient->val);
        
        d = ((d1 + d2) - ((2 * da)));

    }else if(d2 > d1 && (d1 != 0)){ //3
        Node<H>* ancient = foundAncient(n1, n2);

        int da = distanceFromRoot(ancient->val);
        d = (d1 + d2) - (2 * da);

    }else if((d1 == 0) && d2 != 0){ //4
        d = d2;
    }
    return d;
}

///////////////////////////////////// DISTANCE NODE
//DISTANCE NODE PUBLIC
template <class H>
int BST<H>::distanceNode(H v1, H v2){
    Node<H>* n1 = searchNode(v1), *n2 = searchNode(v2);
    return distanceNode(n1, n2);
}
/////////////
//DISTANCE NODE PRIVATE
template <class H>
int BST<H>::distanceNode(Node<H>* n1, Node<H>* n2){
    int d = 0;
    int dir1 = directionNode(n1), dir2 = directionNode(n2);

    if(dir1 != dir2){
        d = distanceFromRoot(n1->val) + distanceFromRoot(n2->val);
    } else if(dir1 == dir2){
        d = foundDistanceSameDirection(n1, n2);
    }
    return d;
}
//////////////
//////////////////////////////////////////////////////

template <class H>
void BST<H>::postOrder() const {postOrder(root);}

template <class H>
void BST<H>::postOrder(Node<H>* p) const{
    if(p){
        postOrder(p->left);
        postOrder(p->right);
        cout << p->val << " ";
    }
}

template <class H>
ostream& operator<<(ostream& out, BST<H>& t){
    t.postOrder();
    return out;
}

int main(){
    ifstream in;
    in.open("input.txt", ios::in);

    string tipo = "", line;
    int n, elint, cambio=0, val1, val2;
    char elchar, char1, char2;
    BST<int> primo;
    BST<int> secondo;
    BST<int> terzo;
    BST<char> quarto;
    BST<char> quinto;
    BST<char> sesto;

    if(in.is_open()){
                getline(in, line, ' ');
                tipo = line;
                getline(in, line, ' ');
                n = stoi(line);
                    for(unsigned short i=0; i<n; i++){
                        getline(in, line, ':');
                            if(line == "ins" && tipo == "int"){
                                getline(in, line, ' ');
                                elint = stoi(line);
                                primo.insertNode(elint);
                            }
                    }
                        getline(in, line, ' ');
                        val1 = stoi(line);
                        getline(in, line);
                        val2 = stoi(line);
                        cout << primo << endl;
                        cout << primo.distanceNode(val1, val2) << endl;

                getline(in, line, ' ');
                tipo = line;
                getline(in, line, ' ');
                n = stoi(line);
                    for(unsigned short i=0; i<n; i++){
                        getline(in, line, ':');
                            if(line == "ins" && tipo == "int"){
                                getline(in, line, ' ');
                                elint = stoi(line);
                                secondo.insertNode(elint);
                            }
                    }
                        getline(in, line, ' ');
                        val1 = stoi(line);
                        getline(in, line);
                        val2 = stoi(line);
                        cout << secondo << endl;
                        cout << secondo.distanceNode(val1, val2) << endl;


                getline(in, line, ' ');
                tipo = line;
                getline(in, line, ' ');
                n = stoi(line);
                    for(unsigned short i=0; i<n; i++){
                        getline(in, line, ':');
                            if(line == "ins"){
                                getline(in, line, ' ');
                                elint = stoi(line);
                                terzo.insertNode(elint);
                            }
                    }
                        getline(in, line, ' ');
                        val1 = stoi(line);
                        getline(in, line);
                        val2 = stoi(line);
                        cout << terzo << endl;
                        cout << terzo.distanceNode(val1, val2) << endl;

                getline(in, line, ' ');
                tipo = line;
                getline(in, line, ' ');
                n = stoi(line);
                    for(unsigned short i=0; i<n; i++){
                        getline(in, line, ':');
                            if(line == "ins"){
                                getline(in, line, ' ');
                                elchar = line[0];
                                quarto.insertNode(elchar);
                            }
                    }
                        getline(in, line, ' ');
                        char1 = line[0];
                        getline(in, line);
                        char2 = line[0];
                        cout << quarto << endl;
                        cout << quarto.distanceNode(char1, char2) << endl;

                getline(in, line, ' ');
                tipo = line;
                getline(in, line, ' ');
                n = stoi(line);
                    for(unsigned short i=0; i<n; i++){
                        getline(in, line, ':');
                            if(line == "ins"){
                                getline(in, line, ' ');
                                elchar = line[0];
                                quinto.insertNode(elchar);
                            }
                    }
                        getline(in, line, ' ');
                        char1 = line[0];
                        getline(in, line);
                        char2 = line[0];
                        cout << quinto << endl;
                        cout << quinto.distanceNode(char1, char2) << endl;

                getline(in, line, ' ');
                tipo = line;
                getline(in, line, ' ');
                n = stoi(line);
                    for(unsigned short i=0; i<n; i++){
                        getline(in, line, ':');
                            if(line == "ins"){
                                getline(in, line, ' ');
                                elchar = line[0];
                                sesto.insertNode(elchar);
                            }    
                    }
                        getline(in, line, ' ');
                        char1 = line[0];
                        getline(in, line);
                        char2 = line[0];
                        cout << sesto << endl;
                        cout << sesto.distanceNode(char1, char2) << endl;    
    }
}