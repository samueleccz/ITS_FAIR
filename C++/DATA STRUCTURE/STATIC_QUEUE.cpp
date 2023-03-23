#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define N 5

using namespace std;

class CodaArray{
    private:
        int testa = 0,coda = -1, dim, counter=0;
        int *arr;
    
    public:
        CodaArray(int);
        ~CodaArray();
        void enqueue(int);
        bool isFull();
        void dequeue();
        bool isEmpty();
        void front();
        int getDim();
        friend ostream& operator<<(ostream&, CodaArray&);
        int getVal(short);
};

CodaArray::CodaArray(int n) : dim(n){
    arr = new int[dim];
}

CodaArray::~CodaArray(){
    delete [] arr;
}

void CodaArray::enqueue(int val){
        if(!isFull()){
            coda++;
            arr[coda%dim] = val;
            counter++;
            cout << "VALUE ON QUEUE ADDED, " << val << endl;
        }else
            cout << "QUEUE FULL, ENQUEUE CANCELED" << endl;
}

bool CodaArray::isFull(){
    if(counter >= dim){
        return true;
    }
    return false;
}

void CodaArray::dequeue(){
    if(!isEmpty()){
        testa++;
        counter--;
    }else
        cout << "EMPTY QUEUE, DEQUEUE CANCELED" << endl;
}

bool CodaArray::isEmpty(){
    if(counter != 0){
        return false;
    }
    return true;
}

void CodaArray::front(){
    if(!isEmpty()){
        cout << "HEAD POINTER: " << arr[testa%dim] << endl;
    }else
        cout << "EMPTY QUEUE" << endl;
}

int CodaArray::getDim(){
    return dim;
}

ostream& operator<<(ostream& os, CodaArray& obj){
    if(!obj.isEmpty()){
        os << "arr: [ ";
            for(unsigned short i=obj.testa%obj.dim; i<=obj.coda%obj.dim; i++){
                os << obj.arr[i] << " "; 
            }
        os << "]" << endl;
    }else
        os << "EMPTY QUEUE" << endl;
        return os;
}

int CodaArray::getVal(short i){
    return arr[i];
}

int main(){
    CodaArray c(N);

    /*for(unsigned short i=0; i<5; i++){
        c.enqueue(i);
    }*/

    c.enqueue(1);
    c.enqueue(2);
    c.enqueue(3);
    c.enqueue(4);
    c.enqueue(5);
    c.enqueue(6);

    cout << c << endl;
    
    cout << "full= " << c.isFull() << endl;
    cout << "dim= " << c.getDim() << endl;

    c.front();
    c.dequeue();
    c.front();
    c.dequeue();
    c.front();
    c.dequeue();
    c.front();
    c.dequeue();
    c.front();
    c.dequeue();
    c.front();

    cout << "empty: " << c.isEmpty() << endl;
    cout << "full= " << c.isFull() << endl;
    //c.~CodaArray();

    cout << c << endl;
}