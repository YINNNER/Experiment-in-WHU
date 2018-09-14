#include <iostream>
#include "Polynomial.h"

int main() {

   Polynomial ah,bh,ch;
   ah.inputPoly();      //input polynomial a
   std::cout<<"The ascending polynomial is: "<<std::endl;
   ah.outputPoly();
   bh.inputPoly();      //input polynomial b
   std::cout<<"The ascending polynomial is: "<<std::endl;
   bh.outputPoly();
   ch = ah*bh;
   std::cout<<"The result is: "<<std::endl;
   ch.outputPoly();    //output the result

   return 0;
}