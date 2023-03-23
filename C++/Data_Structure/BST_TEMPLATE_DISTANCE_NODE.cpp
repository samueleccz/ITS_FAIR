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

        int foundDistanceSameDirection(Node<H>*, Node<H>*);
        Node<H>* searchNode(Node<H>*, H) const;
        int directionNode(Node<H>*); //0 right 1 left
        int distanceNode(Node<H>*, Node<H>*);
        Node<H>* foundAncient(Node<H>*, Node<H>*);

    public:
        BST(): root(nullptr){}
        void insertNode(H);

        Node<H>* searchNode(H) const; 
        int distanceFromRoot(H);
        int directionNode(H); //connection with private
        int distanceNode(H, H);

        int const height(Node<H>*);
        template <typename U> 
        friend ostream& operator<<(ostream&, BST<U>&);
        void postOrder() const;
};

template <class H>
Node<H>* BST<H>::searchNode(H v) const{
    /*if(searchNode(root, v) != nullptr)
        //cout << "BST ELEMENT with value " << v << " found" << endl;
    else
        //cout << "BST ELEMENT with value " << v << " not found" << endl;
*/
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
int BST<H>::foundDistanceSameDirection(Node<H>* n1, Node<H>* n2){
    int d1 = distanceFromRoot(n1->val), d2 = distanceFromRoot(n2->val);
    int d = 0;

    if(d1 == d2){
        d = (d1 + d2) - (2 * distanceFromRoot(n1->parent->val)); 

    }else if(d1 > d2 && ((d2 != 0) || (d2 == 0))){
        Node<H>* ancient = foundAncient(n1, n2);

        int da = distanceFromRoot(ancient->val);
        
        d = ((d1 + d2) - ((2 * da)));

    }else if(d2 > d1 && (d1 != 0)){
        Node<H>* ancient = foundAncient(n1, n2);

        int da = distanceFromRoot(ancient->val);
        d = (d1 + d2) - (2 * da);

    }else if((d1 == 0) && d2 != 0){
        d = d2;
    }
    return d;
}

template <class H>
int BST<H>::distanceNode(H v1, H v2){
    Node<H>* n1 = searchNode(v1), *n2 = searchNode(v2);
    return distanceNode(n1, n2);
}

    //Dn1 + Dn2 - 2*DParentCommon

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


/////////////////////////////////////////////////////////////////////////////////////

template <class H>
void BST<H>::postOrder() const {postOrder(root);}

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

/*
Parti dal primo nodo passato in input
e dopodiche' ti sposti a destra e sinistra per cercare l'altro
Se non lo trovi allora risali partendo sempre dal primo passato in input
E risalendo controlli a sinistra o destra in base al valore
Ogni volta che ti sposti incrementi un contatore 
*/


template <class H>
int const BST<H>::height(Node<H>* p){
    if(p == nullptr){
        return 0;
    }

    int lh = height(p->left);
    int rh = height(p->right);

    if(lh>rh) return (lh+1);
    else return (rh+1);
}

template <class H>
ostream& operator<<(ostream& out, BST<H>& t){
    int h = t.height(t.root);
    /*cout << "Albero di altezza " << h << endl;
    for(int i=0;i<h;i++){
        printLevel(t.root, i);
        cout << endl;
    }*/
    t.postOrder();
    return out;
}

template <class H>
void BST<H>::postOrder(Node<H>* p) const{
    if(p){
        postOrder(p->left);
        postOrder(p->right);
        cout << p->val << " ";
    }
}

int main(){
    srand(11223344);

    BST<int> bst;
    
    cout << "order of inseriment: ";
    for(unsigned short i=0; i<10; i++){
        int n = rand()%100;
        bst.insertNode(n);
        cout << n << " "; 
    }cout << endl;

    cout << "postorder: ";
    bst.postOrder();

    cout << endl << bst.distanceNode(31, 82) << endl;
    
}