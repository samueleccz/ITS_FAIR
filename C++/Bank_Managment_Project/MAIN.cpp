#include <iostream>
#include <iomanip>
#include <cmath>

#include "LIST.h"

using namespace std;

int main(){
    List l;
    char o = 'n';
    string op = "", operation = "";
    char choose;
    bool option = true;

    string name = "", surname = "", sex = "";
    while(option != false){
        cout << "what do you want to do? (Create, Modify or Delete)" << endl;
        cin >> operation;
            
            for(unsigned short i=0; i<operation.length(); i++)
                op += tolower(operation[i]);
            
            if(op == "create"){
                cout << "insert name, surname and sex" << endl;
                cin >> name >> surname >> sex;
                    
                    User* u = new User(name, surname, sex);
                    Bank* b = new Bank(u);
                    l.insertNode(u, b);         

            }else if(op == "print"){
                cout << l;
            }else if(op == "modify"){

            }
    

        cout << "Wanna exit? y/n" << endl;
        cin >> o;

        switch(o){
            case 'y':
                option = false;
                break;
            case 'n':
                option = true;
                break; 
        }
    }

}

