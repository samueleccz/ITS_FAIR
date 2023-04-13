#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class User{
    private:
        string name, surname, cf;
        bool sex;
        unsigned short age, bday, bmonth, byear;
        unsigned short id = 1;
    public:
        User(string n, string s, char se) : name(n), surname(s){
                if(se == 'm' or se == 'M')
                    sex = true;
                else
                    sex = false;    
        }

        void modifyName(string);
        void modifyAge(int, int, int, int);
        int getIdentity();
        string getName();
};

void User::modifyName(string n){
    name = n;
}

void User::modifyAge(int a, int d, int m, int y){
    age = a;
    bday = d;
    bmonth = m;
    byear = y;
}

int User::getIdentity(){
    return id;
}

string User::getName(){
    return name;
}
