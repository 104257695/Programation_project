#include <iostream>
#include "class.h"
#include <string>
// Constructor con lista de inicialización
StanfordID::StanfordID(std::string name, int age, std::string city, std::string major, int semester)
    : name(name), age(age), city(city),major(major), semester(semester) {}

// Método para imprimir información
void StanfordID::mostrarInfo() {
    std::cout << "Nombre: " << name << ", Edad: " << age << ", Ciudad: " << city << " , Major:"<<major<<" , Semester:"<<semester <<std::endl;
}

std::string StanfordID::getName(){
    return name;
}
std::string StanfordID::getMajor(){
    return major;
}
int StanfordID::getSemester(){
    return semester;
}

