/*
Definire una classe BST che implementi:
- inserimento
- visite (inorder, preorder e postorder)
*/

#include <iostream>
using namespace std;

class Nodo {
public:
    int val;
    Nodo* left;
    Nodo* right;
    Nodo* parent;
};

class BST{
public:
    BST(): root(nullptr){};
    void insert(int valore);
    void inOrder()const; // sx rad dx
    void preOrder()const;// rad sx dx
    void postOrder()const;// sx dx rad

    int altezza(Nodo* p)const;
    friend
    ostream& operator<<(ostream& out, const BST& t);

private:
    Nodo* root;
    int numElem =0;
    void inOrder(Nodo* p)const;
    void preOrder(Nodo* p)const;
    void postOrder(Nodo* p)const;

};


void BST::inOrder(Nodo* p) const{
    if(p!=nullptr){
        inOrder(p->left);
        cout << p->val << "\t";
        inOrder(p->right);
    }
}
//versione pubblica
void BST::inOrder() const {inOrder(root);}


void BST::preOrder(Nodo* p) const{
    if(p!=nullptr){
        cout << p->val << "\t";
        preOrder(p->left);
        preOrder(p->right);
    }
}
//versione pubblica
void BST::preOrder()const {preOrder(root);}



void BST::postOrder(Nodo* p) const{
    if(p!=nullptr){
        postOrder(p->left);
        postOrder(p->right);
        cout << p->val << "\t";
    }
}
//versione pubblica
void BST::postOrder()const {postOrder(root);}

void BST::insert(int valore){

    Nodo* nuovo = new Nodo;
    Nodo* x = root, *y = nullptr;

    nuovo->val = valore;
    nuovo->left = nuovo->right = nullptr;

    while(x!=nullptr){
        y=x;
        if(valore< x->val)
            x = x->left;
        else
            x = x->right;
    }

    nuovo->parent = y;
    if(y==nullptr)
        root = nuovo;
    else if(valore<y->val)
        y->left = nuovo;
    else
        y->right = nuovo;

    numElem++;
}

//NB: questa puo' essere sfruttata da operator<<
void stampaLivello(Nodo* p, int level){ // stampa i nodi ad un dato livello
    // p punta ad una posizione vuota
    if(p == nullptr){
        if (level==0) cout << "_\t";
        return;
    }

    if(level == 0)
       cout << p->val << "\t";
    else if(level>0){
        stampaLivello(p->left,level-1);
        stampaLivello(p->right,level-1);
    }

}

int BST::altezza(Nodo* p)const{
    if (p==nullptr) return 0;

    int lh = altezza(p->left);
    int rh = altezza(p->right);

    if(lh>rh)   return (lh+1);
    else        return (rh+1);
}


ostream& operator<<(ostream&out, const BST& t){
    int h = t.altezza(t.root);
    cout << "Albero di altezza " << h << endl;
    for(int i=0;i<h;i++){
        stampaLivello(t.root, i);
        cout << endl;
    }
    return out;
}



int main(){
    BST tree;
    tree.insert(20); 
    tree.insert(10);
    tree.insert(30);
    tree.insert(22);
    tree.insert(50);
    tree.insert(60);
    tree.insert(59);
    tree.insert(15);
    tree.insert(8);
    tree.insert(17);
    tree.insert(9);
    tree.insert(5);
    tree.insert(16);

    cout << tree << endl;

    cout << "Visita inorder:\t\t";
    tree.inOrder();
    cout << endl;
    cout << "Visita preorder:\t";
    tree.preOrder();
    cout << endl;
    cout << "Visita postorder:\t";
    tree.postOrder();

    return 0;
}
