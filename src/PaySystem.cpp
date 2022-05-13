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

#ifndef PAYS
#define PAYS

#include <iostream>
#include <condition_variable>
#include <queue>
#include <utility>
#include <definitions.h>
#include "Request.cpp"
#include "QueueProtected.cpp"


class PaySystem
{
private:

public:
    void operator () ();
};

/*Metodo que se estara ejcutando hasta que cambie la flag de control indicando la finalizacion del programa*/
void PaySystem::operator () (){
    while(1){
        if(!requests.checkEmpty()){
            std::this_thread::sleep_for (std::chrono::seconds(1)); //Para añadir un poco de complejidad a la operación de recarga de saldo
            Request r = std::move(requests.remove());
            std::cout<<YELLOW<<"[PAYSYSTEM]"<<MAGENTA<<" Atendiendo la petición de recarga del Cliente "<<RED<<r.getID()<<RESET<<std::endl;
            id_flag=r.getID();
            credits=r.getCredit();
            cv_queue.notify_all();
        }else if(end_program){
            break;
        }
    }
    std::cout<<YELLOW<<"[PAYSYSTEM]"<<MAGENTA<<" Shutdown..."<<RESET<<std::endl;
}

#endif