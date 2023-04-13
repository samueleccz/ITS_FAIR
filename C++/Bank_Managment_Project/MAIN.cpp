#include <iostream>
#include <iomanip>
#include <cmath>

#include "LIST.h"

using namespace std;

int main(){
    List l;
    User* u = new User("Samuele", "cucuzza", 'm');
    Bank* b = new Bank(u);

    User* u1 = new User("S", "c", 'm');
    Bank* b1 = new Bank(u1); 

    User* u2 = new User("C", "DG", 'm');
    Bank* b2 = new Bank(u2);

    l.insertNode(u, b);
    l.insertNode(u1, b1);
    l.insertNode(u2, b2);
    
    cout << l << endl;
}