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

class Request {
    private:

    int id;
    float credit;

    public:

    Request(int id, float credit);
    int getID();
    float getCredit();
    void setCredit(float credit);
};

Request::Request(int id, float credit) {
    this->id = id;
    this->credit = credit;
}

int Request::getID() {
    return this->id;
}

float Request::getCredit(){
    return this->credit;
}

void Request::setCredit(float credit) {
    this->credit = credit;
}