//! Singleton example
#include <iostream>
#include <vector>

using namespace std;

class Zoo;

class Animal{
public:
    Animal(string m_name) : name(m_name){};
    friend class Zoo;
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
    static Zoo& getInstance(){
        static Zoo *z = new Zoo();
        return *z;
    }

    void add(Animal *animal){
        animals.push_back(animal);
    }

    void feed(string name){
        for (auto animal : animals){
            if (animal->name == name){
                cout << "You fed " << name << '!' << endl;
                return;
            }
        }
        cout << "There are no " << name << " in this Zoo :(" << endl;
    }
private:
    vector<Animal*> animals;
    Zoo() = default;
    Zoo(const Zoo&) = delete;
    Zoo& operator=(const Zoo&) = delete;
    Zoo(Zoo&&) = delete;
    Zoo& operator=(Zoo&&) = delete;
};


int main(){
    Zoo &zoo = Zoo::getInstance();
    zoo.add(new Bear());
    zoo.add(new Pig());

    zoo.feed("Pig");
    zoo.feed("Bear");
    zoo.feed("Giraffe");

    return 0;
}