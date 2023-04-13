#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Bank{
    private:
        long double money = 0;
        User* user_bank;
        
    public:
        Bank(User* ur) : user_bank(ur){}
        void increaseMoney(double);
        void decreaseMoney(double);
        void modifyMoney(char, double);
        double getMoney();
};

void Bank::modifyMoney(char s, double m){
    m = abs(m);
    if(s == 'd' or s == 'D')
        decreaseMoney(m);
    if(s == 'i' or s == 'I')
        increaseMoney(m);
}

void Bank::increaseMoney(double in){
    money += in;
}

void Bank::decreaseMoney(double de){
    money -=de;
}

double Bank::getMoney(){
    return money;
}