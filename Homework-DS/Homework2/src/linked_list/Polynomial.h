//
// Created by yiner on 19/10/2017.
//

#ifndef DS_EX2_POLYNOMIAL_H
#define DS_EX2_POLYNOMIAL_H


#include "Term.h"

class Polynomial {
private:
    //pointer to the head,the dummy node of the linked list
    Term *first;

public:
    void inputPoly();
    void outputPoly();
    void sort();
    void merge();
    Polynomial operator *(const Polynomial & bh);
    Polynomial& operator =(const Polynomial & ch);

    //functions to manipulate linked list
    Polynomial();
    ~Polynomial();
    void makeEmpty();
    int getLength()const;
    bool insertTerm(int coef, int exp, int i);
    bool removeTerm(int i);
    Term* findTerm(int i)const;

};




#endif //DS_EX2_POLYNOMIAL_H
