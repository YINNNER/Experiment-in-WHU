//
// Created by yiner on 19/10/2017.
//
#include <iostream>
#include <string>
using namespace std;

#include "Polynomial.h"

void Polynomial::inputPoly() {
    //display guidance statement
    cout<<"Please input a polynomial like this \"1-2x^2+3x^(-5)\", and press Enter to end your input."<<endl;
    cout<<"The coefficient and the exponent can only be number from -9 to 9. "<<endl;
    cout<<"The polynomial can only have less than or equal 5 terms. "<<endl;
    cout<<"Input a polynomial: "<<endl;

    //get input
    char raw[30];
    //initial raw to null string
    for (int n = 0; n <30 ; ++n) {
        raw[n]='\0';
    }
    cin.getline(raw,30);

    //analyse input string and store them into corresponding items
    for (int i = 0; i < 30; ) {
        //add to termArray
        for (; termNumber <Term::Max-1 ; ) {

            //1.store coef
            //a.when occur '+',move to the next item to store coef
            if(raw[i]=='+') {
                //'+x'means the coef =1
                if (raw[i+1]=='x'){
                    termArray[termNumber].coef=1;
                    i++;
                }
                else{
                    i++;
                    termArray[termNumber].coef=raw[i]-'0';
                    i++;
                }


            }
            //b.when occur '-',move to the next item to store coef of the opposite number
            else if(raw[i]=='-'){
                //'-x'means the coef =-1
                if (raw[i+1]=='x'){
                    termArray[termNumber].coef=-1;
                    i++;
                }
                else{
                    i++;
                    int temp;
                    temp=raw[i]-'0';
                    termArray[termNumber].coef=-temp;
                    i++;
                }

            }
            //c.the first char is 'x',means the coef=1
            else if(i==0&&raw[i]=='x') {
                termArray[termNumber].coef=1;
                if(raw[i+1]=='\0') {
                    termArray[termNumber].exp=1;
                    i++;
                    termNumber++;
                    break;
                }

            }
            //d.simply store number
            else{
                termArray[termNumber].coef=raw[i]-'0';
                i++;
            }

            //2.store exp

            if(raw[i]=='x') {
                //the last char is 'x', means exp=1
                if(raw[i+1]=='\0'){
                    termArray[termNumber].exp=1;
                    i++;
                    termNumber++;
                    break;
                }

                i++;
                //a.when occur '^',skip
                if(raw[i]=='^') {
                    i++;
                    //when occur '(', move to the next item to judge if exist a '-'
                    //if exist a '-',move to the next item to store exp of the opposite number
                    if(raw[i]=='('){
                        if(raw[++i]=='-'){
                            i++;
                            int temp;
                            temp=raw[i]-'0';
                            termArray[termNumber].exp=-temp;
                            i++;
                            termNumber++;
                            //when occur ')',skip
                            if(raw[i]==')') i++;
                        }
                    }
                    //store positive exp
                    else{
                        termArray[termNumber].exp=raw[i]-'0';
                        i++;
                        termNumber++;
                    }
                }
                //b.if directly occur '+' or '-', means the exp is 1
                else if (raw[i]=='+'||raw[i]=='-'){
                    termArray[termNumber].exp=1;
                    i++;
                    termNumber++;
                }
            }
            else {
                termNumber++;
            }

            //end the loop
            if(raw[i]=='\0') {
                //termNumber--;
                break;
            }

        }
        //end the loop
        if(raw[i]=='\0') {
            //termNumber--;
            break;
        }


    }

}


void Polynomial::outputPoly() {
    sort();
    for (int j=0; j < termNumber; j++ ) {

        if(j>0&&termArray[j].coef>0){
            cout<<'+';
        }
        cout<<termArray[j].coef;
        if(termArray[j].exp==0) continue;
        cout<<'x';
        cout<<'^';
        if(termArray[j].exp<0)
        {
            cout<<'(';
            cout<<termArray[j].exp;
            cout<<')';
        }
        else cout<<termArray[j].exp;

    }

    cout<<endl;


}


Polynomial Polynomial::operator*(Polynomial const & bh) {
    Polynomial ch;
    for (int i = 0; i < termNumber ; ++i) {
        for (int j = 0; j <bh.termNumber ; ++j) {
            //coef multiplication
            ch.termArray[ch.termNumber].coef= this->termArray[i].coef * bh.termArray[j].coef;

            //exp multiplication
            ch.termArray[ch.termNumber].exp= this->termArray[i].exp + bh.termArray[j].exp;

            ch.termNumber++;
        }
    }

    ch=ch.merge();

    sort();

    return  ch;
}


Polynomial::Polynomial(){
    termNumber=0;
}

//sort the Polynomial in ascending order
void Polynomial::sort() {
    for (int j=0;j<termNumber-1;j++) {
        for (int i=0;i<termNumber-1-j;i++){
            if(termArray[i].exp>=termArray[i+1].exp){
                int temp;
                //change exp
                temp=termArray[i].exp;
                termArray[i].exp=termArray[i+1].exp;
                termArray[i+1].exp=temp;
                //change coef
                temp=termArray[i].coef;
                termArray[i].coef=termArray[i+1].coef;
                termArray[i+1].coef=temp;
            }

        }
    }

}


//merge the term that has the same exponent
Polynomial Polynomial::merge() {
    for (int i = 0; i <termNumber ; ++i) {
        for (int j = 0; j <termNumber ; ++j) {
            //compare each term's exponent
            if (i==j) continue;
            //if euqal, add exp to the front term
            if (termArray[i].exp==termArray[j].exp){
                if(i<j) {
                    termArray[i].coef+=termArray[j].coef;
                    termArray[j].coef=0;
                }

                if(i>j) {
                    termArray[j].coef+=termArray[i].coef;
                    termArray[i].coef=0;
                }
            }
        }
    }
    //remove the term if the coef==0 and sort the polynomial
    Polynomial ch;
    for (int k = 0; k <termNumber ; ++k) {
        if (termArray[k].coef==0) continue;
        ch.termArray[ch.termNumber].coef=termArray[k].coef;
        ch.termArray[ch.termNumber].exp=termArray[k].exp;
        ch.termNumber++;
    }

    return ch;
}
