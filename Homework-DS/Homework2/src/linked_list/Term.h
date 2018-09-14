//
// Created by yiner on 19/10/2017.
//

#ifndef DS_EX2_TERM_H
#define DS_EX2_TERM_H



class Term {
    friend class Polynomial;

private:
    Term* link;
    int coef;
    int exp;
public:
    Term();
    Term(int coef,int exp);
    static Term* newTerm(int coef, int exp,Term* next= nullptr);
};


#endif //DS_EX2_TERM_H
