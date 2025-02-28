#include <iostream>
#include <cmath>
#include <tuple>
#include <string>
#include <stdio.h>

//Structured binding  
std::tuple<std::string, int, std::string> ageinfo(){
    std::string Name ="Jefferson";
    int age =25;
    std::string semester="Quinto";

    return {Name, age, semester};
}
// initialization
int main() {
    int num{12};
   double direct(5.6);
   std::string str("Example");
    bool x=true;

    std::cout<<"Int : "<<num<< ", Doubl: "<<direct<<", String: "<<str <<", bool: "<<x<<std::endl;

    //references:
    int& ref1=num;
    double& ref2=direct;
    std::string& ref3=str;
    bool& ref4=x;

    ref1=15;
    ref2=12.3;
    ref3="Cambio";
    ref4=false;
    std::cout<<"Modified values:"<<std::endl;
    std::cout<<"Int : "<<num<< ", Doubl: "<<direct<<", String: "<<str <<", Bool: "<<ref4<<std::endl;

    //pointer modification
    int* pointer=&ref1;
    *pointer=50;
     std::cout<<"Pointer modificated: \n"<<"Int: "<<*pointer <<std::endl;
     std::cout<<"Structured binding: "<<std::endl;
    auto [Name, age, semester] = ageinfo();
    std::cout <<"Name: "<< Name << ", Age: " << age << ", Semester: "<< semester<< std::endl;

    std::cout << "a = 42; // l-value" << std::endl;
    std::cout << "int x = a + b; // (a + b) is an r-value" << std::endl;
    std::cout << "&a; // l-value" << std::endl;
    std::cout << "std::string s = c + \" World\"; //  (c + \" World\") is an r-value" << std::endl;
    std::cout << "int& refX = x; // l-value reference" << std::endl;
    std::cout << "int&& rref = 100; // r-value reference" << std::endl;

    return 0;
}