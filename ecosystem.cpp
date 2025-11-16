#include <iostream>

class Serializable { 
public:
    virtual ~Serializable() = default;  
    virtual std::string serialize() const = 0;
};

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
    virtual std::string serialize() const override{ return "\"name\" : \"" + _name + "\" \n \"age\" : " + std::to_string(_energy) + "\n"; }
    virtual void move() override { _energy--; std::cout << "Wolf is moving" << std::endl; } 
    virtual void act() const override { std::cout << "Wolf is hunting" << std::endl; }
    virtual std::string info() const override { return "Name: " + _name + "\n Energy: " + std::to_string(_energy) + '\n'; }
};

class Drone : public Serializable, public Entity
{
public:
    Drone(std::string name = "Krunk", int energy = 100) : Entity(name, energy) {}
    virtual std::string serialize() const override{ return "\"name\" : \"" + _name + "\" \n \"age\" : \"" + std::to_string(_energy) + "\"\n"; }
    virtual void move() override { _energy -= 10; std::cout << "Drone is flying" << std::endl; } 
    virtual void act() const override { std::cout << "Drone scans the area." << std::endl; }
    virtual std::string info() const override { return "Name: " + _name + "\n Energy: " + std::to_string(_energy) + '\n'; }

};

class Robot : public Entity
{
public:
    Robot(std::string name = "SeRob", int energy = 100) : Entity(name, energy) {}
    virtual void move() override { _energy -= 20; std::cout << "Robot is moving" << std::endl; } 
    virtual void act() const override { std::cout << "Robot optimizes logistics." << std::endl; }
    virtual std::string info() const override { return "Name: " + _name + "\n Energy: " + std::to_string(_energy) + '\n'; }
};
int main()
{
    std::cout << "===== INDIVIDUAL OBJECT TESTS =====\n";
    
    Animal wolf("Hamlet", 50);
    Drone drone("Krunk-1", 120);
    Robot robot("SeRobX", 200);

    std::cout << "\n--- Serialization Tests ---\n";
    std::cout << "Animal JSON:\n" << wolf.serialize() << "\n";
    std::cout << "Drone JSON:\n"  << drone.serialize() << "\n";
    // Robot has no serialize(), should NOT compile if tried. Good test of interface separation.

    std::cout << "\n--- Info Tests ---\n";
    std::cout << wolf.info();
    std::cout << drone.info();
    std::cout << robot.info();

    std::cout << "\n--- Movement Tests ---\n";
    wolf.move();
    drone.move();
    robot.move();

    std::cout << wolf.info();
    std::cout << drone.info();
    std::cout << robot.info();

    std::cout << "\n--- Action Tests ---\n";
    wolf.act();
    drone.act();
    robot.act();

    std::cout << "\n===== POLYMORPHISM TESTS =====\n";

    Entity* entities[3];
    entities[0] = new Animal("Fox", 10);
    entities[1] = new Drone("HawkEye", 80);
    entities[2] = new Robot("Unit-9", 150);

    for (int i = 0; i < 3; i++)
    {
        std::cout << "\nENTITY #" << i << ":\n";
        std::cout << entities[i]->info();
        entities[i]->move();
        entities[i]->act();
        std::cout << entities[i]->info();
    }

    std::cout << "\n===== SERIALIZABLE INTERFACE TEST =====\n";

    Serializable* serializables[2];
    serializables[0] = new Animal("Tiger", 90);
    serializables[1] = new Drone("Flyer", 40);

    for (int i = 0; i < 2; i++)
    {
        std::cout << "\nSerializable #" << i << ":\n";
        std::cout << serializables[i]->serialize() << "\n";
    }

    std::cout << "\n===== EDGE CASE TESTS =====\n";

    Animal emptyName("", 5);
    Drone zeroEnergy("ZeroBot", 0);

    std::cout << emptyName.info();
    std::cout << zeroEnergy.info();

    emptyName.move();
    zeroEnergy.move();  // Should go negative — still allowed

    std::cout << emptyName.info();
    std::cout << zeroEnergy.info();

    std::cout << "\n===== MEMORY CLEANUP =====\n";
    for (int i = 0; i < 3; i++) delete entities[i];
    for (int i = 0; i < 2; i++) delete serializables[i];

    std::cout << "Done!\n";

    return 0;
}
