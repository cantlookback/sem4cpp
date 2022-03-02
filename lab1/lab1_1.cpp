//!!!! Singleton example
#include <iostream>
#include <vector>

using namespace std;
//?Declaration for proper work
class Zoo;
//?Animal classes
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
//?Zoo class with all stuff in it
class Zoo{
public:
    //?Get instance of zoo class
    static Zoo* getInstance(){
        static Zoo *z = new Zoo();
        return z;
    }
    //?Adding animals to vector
    void add(Animal *animal){
        animals.push_back(animal);
    }
    //?Feeding specific animal in zoo
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
    //?Vector of animals
    vector<Animal*> animals;
    //?Prohibition of creation of new instances
    Zoo() = default;
    Zoo(const Zoo&) = delete;
    Zoo& operator=(const Zoo&) = delete;
    Zoo(Zoo&&) = delete;
    Zoo& operator=(Zoo&&) = delete;
};


int main(){
    Zoo *zoo = Zoo::getInstance();
    zoo->add(new Bear());
    zoo->add(new Pig());

    zoo->feed("Pig");
    zoo->feed("Bear");
    zoo->feed("Giraffe");

    return 0;
}