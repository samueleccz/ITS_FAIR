#include <iostream>


using namespace std;


class prova{
    private:
        int lato1;
        int b;
        int somma;
    public:
        prova(int x, int y) : lato1(x) , b(y){
            somma = lato1+b;
        }
};


int main(){

    cout << "ciao";
}