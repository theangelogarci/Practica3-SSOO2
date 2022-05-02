/*********************************************
*   Project: Práctica 2 de Sistemas Operativos II 
*
*   Program name: WordSearched.c
*
*   Author: Angel García Collado and Andrés Castellanos Cantos.
*
*   Date created: 14-03-2022
*
*   Porpuse: Clases para almacenar información relacionada con palabras buscadas.
*
*   Revision History: Se puede encontrar en el repositorio de GitHub.
|*********************************************/

#include <iostream>
#include <colours.h>

class WordSearched
{
private:
    std::string objetivo;
    int nThread;
    int begin;
    int end;
    int line;
    std::string word_before;
    std::string word;
    std::string word_after;

public:
    WordSearched(std::string objetivo, int nThread, int begin, int end, int line, std::string word_before, std::string word, std::string word_after);
    void toString();
};

WordSearched::WordSearched(std::string objetivo,int nThread, int begin, int end, int line, std::string word_before, std::string word, std::string word_after)
{
    this->objetivo=objetivo;
    this->nThread=nThread;
    this->begin=begin;
    this->end=end;
    this->line=line;
    this->word_before=word_before;
    this->word=word;
    this->word_after=word_after;
}

void WordSearched::toString(){
    std::cout<< RESULT("[Hilo ")<< RED <<std::to_string(this->nThread) << RESULT(" inicio: ")<< RED<< std::to_string(this->begin)<<  RESULT(" – final: ")<< RED << std::to_string(this->end)<<  RESULT("] :: línea ")<< RED <<std::to_string(this->line)<<RESULT(" :: ")<< CIAN <<"... "+this->word_before<<" "<< ULINE <<this->word<< RESET<< CIAN<<" "<<this->word_after<<" ..."<<std::endl;
}
