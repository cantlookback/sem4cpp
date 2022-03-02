//!!!! SOLID example
#include <iostream>
#include <vector>

using namespace std;

class Animal{
public:
    Animal(string m_name) : name(m_name){}
    string getName(){ return name; }
private:
    string name;
};

class Eating : public Animal{
public: 
    Eating(string m_name) : Animal(m_name){}
    void Feed(string beb){
        cout << "You fed " << beb << endl;
    }
};

class Pat : public Animal{
public:
    Pat(string m_name) : Animal(m_name){}
    void pat(string beb){
        cout << "You did pat " << beb << endl;
    }
};

int main(){
    Eating eat("pig");
    Pat p("wolf");

    eat.Feed("Pig");
    p.pat("Wolf");

    return 0;
}