#ifndef CLASS_H
#define CLASS_H

#include <string>

class StanfordID {
private:
    std::string name;
    int age;
    std::string city;
    std:: string major;
    int semester; 
    public:
    StanfordID(std::string name, int age, std::string city, std::string major, int semester);
    void mostrarInfo();

    std:: string getName();
    
    std::string getMajor();
    
    int getSemester();
};


#endif