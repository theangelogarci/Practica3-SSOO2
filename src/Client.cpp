/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: ssooiigle.c
*
*   Author: Angel García Collado and Andrés Castellanos Cantos.
*
*   Date created:04-05-2022
*
*   Porpuse: Busqueda de una palabra en un fichero divido en hilos para agilizar el proceso.
*
*   Revision History: Se puede encontrar en el repositorio de GitHub.
|*********************************************/

#include <iostream>
//#include <colours.h>

class Client
{
    private:
        int id;
        float balance;
        bool premium;
    public:
        Client(int id);
        Client(int id, float balance);
        void toString();
        int getId();
        float getBalance();
        bool isPremium();
        void payCredit();
        void restoreCredits();
        void operator () ();
};

void Client::operator()() {
    
}

Client::Client(int id) {

}

Client::Client (int id, float balance) {
    this->id =id;
    this->balance = balance;
    this->premium = true;
    toString();
}

int Client::getId() {
    return this->id;
}
float Client::getBalance() {
    return this->balance;
}

bool Client::isPremium () {
    return this->premium;
}

void Client::toString() {
    
}