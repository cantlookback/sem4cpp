//!!!! SOLID example
#include <iostream>
#include <vector>

using namespace std;
//?Animal class
class Animal{
public:
    Animal(string m_name) : name(m_name){}
    string getName(){ return name; }
private:
    string name;
};
//?Eating class
class Eating : public Animal{
public: 
    Eating(string m_name) : Animal(m_name){}
    //?Method to feed an animal
    void Feed(string animal){
        cout << "You fed " << animal << endl;
    }
};
//?Patting class
class Pat : public Animal{
public:
    Pat(string m_name) : Animal(m_name){}
    //?Method to pat an animal
    void pat(string animal){
        cout << "You did pat " << animal << endl;
    }
};

int main(){
    Animal pig("pig");

    Eating eat("pig");
    Pat p("pig");

    eat.Feed("Pig");
    p.pat("Wolf");

    return 0;
}