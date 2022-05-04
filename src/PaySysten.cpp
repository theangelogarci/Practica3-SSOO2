/*********************************************
*   Project: Práctica 3 de Sistemas Operativos II 
*
*   Program name: ssooiigle.c
*
*   Author: Angel García Collado and Andrés Castellanos Cantos.
*
*   Date created:04-05-2022
*
*   Porpuse: 
*
*   Revision History: Se puede encontrar en el repositorio de GitHub.
|*********************************************/

#include <iostream>
#include <condition_variable>
#include "Request.cpp"
#include "QueueProtected.cpp"


#include <iostream>
#include <condition_variable>
#include "Request.cpp"
#include "QueueProtected.cpp"


class PaySystem
{
private:
    std::condition_variable cv_queue;
    QueueProtected q_request;

public:
    PaySystem();
    void rechargeBalance();
    void operator () ();
};
void PaySystem::operator () (){
        
    }

PaySystem::PaySystem()
{
}

void PaySystem::rechargeBalance()
{
    if(!q_request.checkEmpty()){
        Request r = q_request.remove();
        r.setCredit(100);
        q_request.add(r);
    }
}
