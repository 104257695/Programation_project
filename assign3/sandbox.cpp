#include <iostream>
 #include "class.h"

void sandbox() {
     
  StanfordID persona("Jefferson", 21, "San Francisco","Computation",5);
 
     
  persona.mostrarInfo();
  std::cout<<"Name with get: "<<persona.getName()
           <<" Major with get: "<<persona.getMajor()
           <<" Semester with get: "<<persona.getSemester()<<std::endl;
}
