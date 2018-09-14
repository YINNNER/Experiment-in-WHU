//
// Created by yiner on 19/10/2017.
//

#ifndef DS_EX2_TERM_H
#define DS_EX2_TERM_H



class Term {
    friend class Polynomial;

private:
    static const int Max=30;
    float coef;
    int exp;
public:
    Term();
};


#endif //DS_EX2_TERM_H
