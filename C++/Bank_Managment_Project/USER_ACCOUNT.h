#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class User{
    private:
        string name, surname, sex;
        unsigned short age, bday, bmonth, byear;
        unsigned short id = 1;
    public:
        User(string n, string s, string se) : name(n), surname(s), sex(se){}

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
