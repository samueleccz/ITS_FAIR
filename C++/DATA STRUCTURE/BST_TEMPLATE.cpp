#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

template <class T>
class Node{
    public:
        Node<T>* left, *right, *parent;
        T val;
};

template <class T>
class BinarySearchTree{ //COMPLEX O(h) ; h=height, nel caso migliore h = log(n)
    Node<T>* root;
    int nEnt = 0;
    void inOrder(Node<T>*) const;
    void preOrder(Node<T>*) const;
    void postOrder(Node<T>*) const;
    bool researchNode(Node<T>*, T) const;
    T successorNode(Node<T>*, T) const;
    Node<T>* successorNodeR(Node<T>*, T) const;
    Node<T>* minNodeR(Node<T>*) const;
    void deleteNode(Node<T>*);
    void transplantNode(Node<T>*, Node<T>*);

    public:
        BinarySearchTree(): root(nullptr){}
        void insertNode(T);
        
        bool deleteNode(T);
        bool researchNode(T) const;

        T successorNode(T) const;
        T maxNode(Node<T>*) const;
        T minNode(Node<T>*) const;

        void inOrder() const;
        void preOrder() const;
        void postOrder() const;
        //Node* getRoot() const {return root;}

        int const height(Node<T>*);

        template <typename U>      // all instantiations of this template are my friends
        friend ostream& operator<<(ostream&, BinarySearchTree<U>&);
        int getNEnt(){return nEnt;}
};



//FUNZIONI PUBBLICHE
template <class T>
void BinarySearchTree<T>::inOrder() const {inOrder(root);}

template <class T>
void BinarySearchTree<T>::preOrder() const {preOrder(root);}

template <class T>
void BinarySearchTree<T>::postOrder() const {postOrder(root);}

template <class T>
bool BinarySearchTree<T>::researchNode(T value) const {
    if(researchNode(root, value) == true){
        cout << "Element " << value << " found" << endl;
    }else{
        cout << "Element " << value << " not found" << endl;
    }
    return researchNode(root, value);
}

template <class T>
T BinarySearchTree<T>::successorNode(T value) const{
    Node<T>* r = root;
   while((r != nullptr) && (value != r->val)){
        if(value < r->val){
            r = r->left;
        }
        else{
            r = r->right;            
        }
    } 
    return successorNode(r, value);
}

template <class T>
bool BinarySearchTree<T>::deleteNode(T x){
    Node<T>* iter = root;
    while((iter != nullptr) && (x != iter->val)){
        if(x < iter->val){
            iter = iter->left;
        }else{
            iter = iter->right;
        }
    }
    if(iter == nullptr){
        return false;
    }
    deleteNode(iter);
    return true;
}

//FUNZIONI PRIVATE

template <class T>
void BinarySearchTree<T>::insertNode(T value){
    Node<T>* nuovo = new Node<T>;
    Node<T>* x = root, *y = nullptr;

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

template <class T>
bool BinarySearchTree<T>::researchNode(Node<T>* r, T value) const{
   while((r != nullptr) && (value != r->val)){
        if(value < r->val)
            r = r->left;
        else
            r = r->right;
    }
    if(r == nullptr)
        return false;

    return true;
}

template <class T>
T BinarySearchTree<T>::maxNode(Node<T>* p) const{
    Node<T>* iter = p;
    while(iter->right != nullptr){
        iter = iter->right;
    }
    return iter->val;
}

template <class T>
T BinarySearchTree<T>::minNode(Node<T>* p) const{
    Node<T>* iter = p;
    while(iter->left != nullptr){
        iter = iter->left;
    }
    return iter->val;    
}

template <class T>
Node<T>* BinarySearchTree<T>::minNodeR(Node<T>* p) const{
    while(p->left != nullptr){
        p = p->left;
    }
    return p;    
}

template <class T>
int const BinarySearchTree<T>::height(Node<T>* p){
    if(p == nullptr){
        return 0;
    }

    int lh = height(p->left);
    int rh = height(p->right);

    if(lh>rh) return (lh+1);
    else return (rh+1);
}

template <class T>
void BinarySearchTree<T>::inOrder(Node<T>* p) const{
    if(p){
        inOrder(p->left);
        cout << p->val << " ";
        inOrder(p->right);
    }
}

template <class T>
void BinarySearchTree<T>::preOrder(Node<T>* p) const{
    if(p){
        cout << p->val << " ";
        preOrder(p->left);
        preOrder(p->right);
    }
}

template <class T>
void BinarySearchTree<T>::postOrder(Node<T>* p) const{
    if(p){
        postOrder(p->left);
        postOrder(p->right);
        cout << p->val << " ";
    }
}

template <class T>
T BinarySearchTree<T>::successorNode(Node<T>* p, T value) const{
    Node<T>* iter = new Node<T>;
    if(researchNode(value)){
        if(p->right != nullptr){
            return minNode(p->right);
        }
        iter = p->parent;
        while(iter != nullptr && p->val == iter->right->val){
            p = iter;
            iter = iter->parent;
        }
    return iter->val;} else return INT_MAX;
}

template <class T>
Node<T>* BinarySearchTree<T>::successorNodeR(Node<T>* p, T value) const{
    Node<T>* iter = new Node<T>;
        if(p->right != nullptr){
            return minNodeR(p->right);
        }
        iter = p->parent;
        while(iter != nullptr && p->val == iter->right->val){
            p = iter;
            iter = iter->parent;
        }
    return iter;
}

template <class T>
void BinarySearchTree<T>::deleteNode(Node<T>* z){
    if(z->left == nullptr){
        transplantNode(z, z->right);
    }else if(z->right == nullptr){
        transplantNode(z, z->left);
    }else{
        Node<T>* iter = minNodeR(z->right);
        if(iter->parent != z){
            transplantNode(iter, iter->right);
            iter->right = z->right;
            iter->right->parent = iter;
        }
        transplantNode(z, iter);
        iter->left = z->left;
        iter->left->parent = iter;
    }

    delete z;
}

template <class T>
void BinarySearchTree<T>::transplantNode(Node<T>* u, Node<T>* v){
    if(u->parent == nullptr){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }

    if(v != nullptr){
        v->parent = u->parent;
    }
}

//FUNZIONI NON MEMBRO DI NESSUNA CLASSE
template <class T>
//NB: questa puo' essere sfruttata da operator<<
void printLevel(Node<T>* p, int level){ // stampa i nodi ad un dato livello
    // p punta ad una posizione vuota
    if(p == nullptr){
        if (level==0) cout << "_\t";
        return;
    }

    if(level == 0)
       cout << p->val << "\t";
    else if(level>0){
        printLevel(p->left,level-1);
        printLevel(p->right,level-1);
    }
}

//OPERATORE <<
template <class T>
ostream& operator<<(ostream& out, BinarySearchTree<T>& t){
    int h = t.height(t.root);
    cout << "Albero di altezza " << h << endl;
    for(int i=0;i<h;i++){
        printLevel(t.root, i);
        cout << endl;
    }
    return out;
}

int main(){

    BinarySearchTree<int> T;
        T.insertNode(8); //root
        T.insertNode(5); //root->left
        T.insertNode(2); //root->right
        T.insertNode(10); //root->left->left
        T.insertNode(6); //root->right->right
        T.insertNode(9); //root->left->right
        T.insertNode(11); //root->right->left
        //T.insertNode(15); //root->right->right->right
        //T.insertNode(11); //root->right->right->left

        cout << T;

        cout << endl << "preOrder: " << endl;
        T.preOrder();
        cout << endl << "inOrder: " << endl;
        T.inOrder();
        cout << endl << "postOrder: " << endl;
        T.postOrder();

        cout << endl;
        
        T.researchNode(10);

        //cout << T.successorNode(12) << endl;

        //cout << T.getNEnt() << endl;

        cout << "reasearch successor: " << endl << T.successorNode(10) << endl <<  T.successorNode(12) << endl << endl;

        T.deleteNode(8);

        cout << T << endl;
}