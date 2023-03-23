#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

class Node{
    public:
        int val;
        Node* parent, *right, *left;
};

class BST{
    private:
        Node* root;
        int cardinality = 0;
        Node* searchNode(Node*, int) const;
        int distanceNode(Node*, Node*);
        //int distanceFromRoot(Node*);
        int foundDistanceSameDirection(Node*, Node*);
        Node* foundAncient(Node*, Node*);
        int directionNode(Node*); //0 right 1 left

        void inOrder(Node*) const;
    public:
        BST() : root(nullptr){}
        void insertNode(int);
 
        Node* searchNode(int) const; 
        int distanceFromRoot(int);
        int directionNode(int); //connection with private
        int distanceNode(int, int);

        int height(Node*)const;
        void inOrder() const; 
        friend ostream& operator<<(ostream&, BST&);
};

void BST::insertNode(int v){    
    Node* nw = new Node;
    Node* x = root, *y = nullptr;

    nw->val = v;
    nw->left = nw->right = nullptr;

    while(x != nullptr){
        y = x;
        if(v < x->val)
            x = x->left;
        else
            x = x->right;
    }

    nw->parent = y;

    if(y==nullptr)
        root=nw;
    else if(v < y->val)
        y->left = nw;
    else 
        y->right = nw;
    
    cardinality++;
}   

Node* BST::searchNode(int v) const{
    /*if(searchNode(root, v) != nullptr)
        cout << "BST ELEMENT with value " << v << " found" << endl;
    else
        cout << "BST ELEMENT with value " << v << " not found" << endl;
    */
    return searchNode(root, v);
}

Node* BST::searchNode(Node* n, int v) const{
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

int BST::distanceFromRoot(int v){
    int d = 0;
    Node* iter = root;
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


int BST::directionNode(int v){
    Node* n = searchNode(v);
    return directionNode(n);
}
int BST::directionNode(Node* n){
    if(n->val < root->val)
        return 1;
    else
        return 0;
}

Node* BST::foundAncient(Node* n1, Node* n2){
    int d1 = distanceFromRoot(n1->val), d2 = distanceFromRoot(n2->val);
    Node* iter = n1, *iter2 = n2;
    
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

int BST::foundDistanceSameDirection(Node* n1, Node* n2){
    int d1 = distanceFromRoot(n1->val), d2 = distanceFromRoot(n2->val);
    int d = 0;

    if(d1 == d2 ){
        d = (d1 + d2) - (2 * distanceFromRoot(n1->parent->val)); 

    }else if(d1 > d2 && ((d2 != 0) || (d2 == 0))){
        Node* ancient = foundAncient(n1, n2);

        int da = distanceFromRoot(ancient->val);
        
        d = ((d1 + d2) - ((2 * da)));

    }else if(d2 > d1 && (d1 != 0)){
        Node* ancient = foundAncient(n1, n2);

        int da = distanceFromRoot(ancient->val);
        d = (d1 + d2) - (2 * da);

    }else if((d1 == 0) && d2 != 0){
        d = d2;
    }
    return d;
}

int BST::distanceNode(int v1, int v2){
    Node* n1 = searchNode(v1), *n2 = searchNode(v2);
    return distanceNode(n1, n2);
}

    //Dn1 + Dn2 - 2*DParentCommon
int BST::distanceNode(Node* n1, Node* n2){
    int d = 0;
    int dir1 = directionNode(n1), dir2 = directionNode(n2);

    if(dir1 != dir2){
        d = distanceFromRoot(n1->val) + distanceFromRoot(n2->val);
    } else if(dir1 == dir2){
        d = foundDistanceSameDirection(n1, n2);
    }
    return d;
}

//PRINTING IN ORDER

void BST::inOrder() const{
    return inOrder(root);
}

void BST::inOrder(Node* n) const{
    if(n!=nullptr){
        inOrder(n->left);
        cout << n->val << " ";        
        inOrder(n->right);
    }
}

//OVERLOADING OPERATOR << + HEIGHT + PRINTLEVEL

int BST::height(Node* p)const{
    if (p==nullptr) return 0;

    int lh = height(p->left);
    int rh = height(p->right);

    if(lh>rh)   return (lh+1);
    else        return (rh+1);
}

ostream& operator<<(ostream& os, BST& obj){
    cout << "BST height: " << obj.height(obj.root) << endl;
    cout << "BST element number: " << obj.cardinality << endl;
    cout << "BST element in order: ";
    obj.inOrder();

    return os;
}

//////////////////////////////////////////////////////////////

int main(){
    srand(8877);
    int r;

    BST bst;

    bst.insertNode(60);

    cout << "Putting element: ";
    for(unsigned short i=0; i<20; i++){
        r = rand()%101;
        bst.insertNode(r);
        cout << r << " ";
    } cout << endl;

    cout << bst << endl;

    cout << bst.distanceNode(24, 29) << endl;
    cout << bst.distanceNode(29, 24) << endl;

    return 0;
}