#include <iostream>
#include <vector>

using namespace std;

class LookForAnimals;
class AnimalsTruck;

class Animal{
public:
    Animal(string m_name) : name(m_name){};
    friend class LookForAnimals;
protected:
    string name;
};

class Bear : public Animal{
public:
    Bear() : Animal("Bear"){};
};

class Pig : public Animal{
public:
    Pig() : Animal("Pig"){};
};

class Zoo{
public:
    Zoo(){};
    friend class AnimalsTruck;
    friend class LookForAnimals;
protected:
    vector <Animal*> animals;
};

class AnimalsTruck{
public:
    AnimalsTruck(){};
    void add(Animal *animal, Zoo *zoo){
        zoo->animals.push_back(animal);
    }
};

class LookForAnimals{
public:
    LookForAnimals(){};
    
    void print(Zoo *zoo){
        for (auto animal : zoo->animals){
            cout << animal->name << endl;
        }
    }
};

int main(){
    Zoo zoo;
    AnimalsTruck truck;

    truck.add(new Bear(), &zoo);
    truck.add(new Bear(), &zoo);
    truck.add(new Pig(), &zoo);

    LookForAnimals look;
    look.print(&zoo);


    return 0;   
}