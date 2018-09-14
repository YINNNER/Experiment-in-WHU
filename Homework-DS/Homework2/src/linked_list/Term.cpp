//
// Created by yiner on 19/10/2017.
//

#include "Term.h"
//default dummy term
Term::Term():link(nullptr),coef(0),exp(0){ }

//new meaningful term
Term::Term(int coef, int exp) :link(nullptr),coef(coef),exp(exp){ }

//new a term with default link to nullptr
Term *Term::newTerm(int coef, int exp,Term* next) {
    Term* newnode = new Term(coef,exp);
    newnode->link=next;
    return newnode;
}
