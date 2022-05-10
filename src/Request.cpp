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
#include <cctype>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <future>
#include "colours.h"

class Request
{
private:
    int id;
    int credit;
public:

    Request(int id, int credit){
        this->id = id;
        this->credit=credit;
    }
    int getID(){
        return this->id;
    }
    int getCredit(){
        return this->credit;
    }
    void toString(){
        std::cout<<"[Request "<<this->id<<"] Credit: "<<this->credit<<std::endl;
    };
};

#endif