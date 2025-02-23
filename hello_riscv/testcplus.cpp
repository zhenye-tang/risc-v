#include <cstdlib>
#include <vector>
#include <cstdio>
#include "uart.h"
#include <cstddef>
#include <string>

class Animal
{
public:
    Animal(const std::string& name) : name(name) {
        uart_printf("animal %s.\n", name.c_str());
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
        uart_printf("dog %s.\n", name.c_str());
    }

    void speak() const override {
        uart_printf("%s speek.\n", name.c_str());
    }
};

class Cat : public Animal
{
public:
    Cat(const std::string& name) : Animal(name) {
        uart_printf("cat %s.\n", name.c_str());
    }

    void speak() const override {
        uart_printf("%s speek.\n", name.c_str());
    }
};

static Cat cat("lami");

extern "C" void cpp_test()
{
    Animal* dog = new Dog("huzi");
    dog->speak();
    delete dog;

    std::vector<int> arry;
    arry.push_back(10);
    arry.push_back(20);
}