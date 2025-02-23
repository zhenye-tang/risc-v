#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <string>
#include "rtthread.h"

class Animal
{
public:
    Animal(const std::string& name) : name(name) {
        rt_kprintf("Animal %s.\n", name.c_str());
    }
    virtual ~Animal() {}

    virtual void speak() const = 0;

protected:
    std::string name;
};

class Dog : public Animal
{
public:
    Dog(const std::string& name) : Animal(name) {
        rt_kprintf("Dog %s.\n", name.c_str());
    }

    void speak() const override {
        rt_kprintf("dog %s speak.\n", name.c_str());
    }
};

class Cat : public Animal
{
public:
    Cat(const std::string& name) : Animal(name) {
        rt_kprintf("Cat %s.\n", name.c_str());
    }

    void speak() const override {
        rt_kprintf("cat %s speak.\n", name.c_str());
    }
};

static Cat cat("lami");

extern "C" void cpp_test()
{
    Animal* dog = new Dog("huzi");
    dog->speak();
    delete dog;
}