#include <iostream>

class Serializable { public: virtual std::string serialize() const = 0; };

class Entity
{
protected:
    std::string _name;
    int _energy;
public:
    Entity(std::string name, int energy) : _name{name}, _energy{energy} {}
    virtual ~Entity() {}

    virtual void move() = 0;
    virtual void act() const = 0;
    virtual std::string info() const = 0;
};

class Animal : public Serializable, public Entity
{
public:
    Animal(std::string name = "Wolf", int energy = 100) : Entity(name, energy) {}
    
    virtual void move() override { _energy--; std::cout << "Wolf is moving" << std::endl; } 
    virtual void act() const override { std::cout << "Wolf is hunting" << std::endl; }
    virtual std::string info() const override { std::cout << "Name: " << _name << "Energy: " << _energy << std::endl; }
};

class Drone : public Serializable, public Entity
{
public:
    Drone(std::string name = "Krunk", int energy = 100) : Entity(name, energy) {}
    virtual void move() override { _energy -= 10; std::cout << "Drone is flying" << std::endl; } 
    virtual void act() const override { std::cout << "Drone scans the area." << std::endl; }
    virtual std::string info() const override { std::cout << "Name: " << _name << "Energy: " << _energy << std::endl; }
};

class Robot : public Entity
{
public:
    Robot(std::string name = "SeRob", int energy = 100) : Entity(name, energy) {}
    virtual void move() override { _energy -= 20; std::cout << "Robot is moving" << std::endl; } 
    virtual void act() const override { std::cout << "Robot optimizes logistics." << std::endl; }
    virtual std::string info() const override { std::cout << "Name: " << _name << "Energy: " << _energy << std::endl; }
};
int main()
{
    Animal a("Hamlet", 2);
    return 0;
}