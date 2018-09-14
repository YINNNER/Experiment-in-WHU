//
// Created by yiner on 19/10/2017.
//

#ifndef DS_EX2_POLYNOMIAL_H
#define DS_EX2_POLYNOMIAL_H


#include "Term.h"

class Polynomial {
private:
    //const int Max;
    Term termArray[Term::Max];
    int termNumber;
public:
    void inputPoly();
    void outputPoly();
    void sort();
    Polynomial merge();
    Polynomial operator *(Polynomial const & bh);
    Polynomial();

};




#endif //DS_EX2_POLYNOMIAL_H
