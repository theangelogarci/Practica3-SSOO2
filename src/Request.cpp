/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: request.cpp
*
*   Author: Angel García Collado and Andrés Castellanos Cantos.
*
*   Date created:04-05-2022
*
*   Porpuse: 
*
*   Revision History: 
|*********************************************/

#ifndef REQUEST
#define REQUEST

#include <iostream>

class Request{
    private:
        int id;
        int credit;

    public:
        Request(int id, int credit);
        int getID();
        int getCredit();
        void setCredit(int credit);
};

Request::Request(int id, int credit){
    this->id = id;
    this->credit = credit;
}

int Request::getID(){
    return this->id;
}

int Request::getCredit(){
    return this->credit;
}

void Request::setCredit(int credit){
    this->credit=credit;
}

#endif