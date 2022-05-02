/*********************************************
*   Project: Práctica 2 de Sistemas Operativos II 
*
*   Program name: ssooiigle.c
*
*   Author: Angel García Collado and Andrés Castellanos Cantos.
*
*   Date created: 14-03-2022
*
*   Porpuse: Busqueda de una palabra en un fichero divido en hilos para agilizar el proceso.
*
*   Revision History: Se puede encontrar en el repositorio de GitHub.
|*********************************************/

#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <string.h>
#include <functional>
#include <definitions.h>

#include <colours.h>
#include "wordSearched.cpp"

void arguments_control(char *argv[],std::string &file, std::string &objective, int &nThreads);
int number_of_lines(std::string file);
void find_word(int thread,std::vector<std::string> assignedLines, int begin, int end, std::string objective);
std::map<int, std::vector<std::string>> shareLines(std::string file, int nLines, int nThreads);
std::vector<std::string> splitLine(std::string line);
std::string analizeWord(std::string word);
void printResult();

std::mutex access;
std::vector<std::thread> vThreads;
std::map<int,std::vector<WordSearched>> vWords;

/* El main se encargara de la creación de hilos y su finalización*/
int main(int argc, char *argv[]){
    std::string file;
    std::string objective;
    std::map<int, std::vector<std::string>> assignedLines;
    int nThreads;
    int nLines;
    int sizeForThreads;
    int begin, end;
    if(argc!=4){
        std::cerr <<ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("Number of arguments is incorrect") ) <<std::endl;
        exit(EXIT_FAILURE);
    } 
    arguments_control(argv,file,objective,nThreads);

    nLines=number_of_lines(file);

    if(nLines<nThreads){
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("More threads than lines") )  <<std::endl;
        exit(EXIT_FAILURE);
    }
    sizeForThreads = nLines/nThreads;
    assignedLines=shareLines(file,nLines,nThreads);
    for (int i = 0; i < nThreads; i++) {
        begin=i*sizeForThreads+1;
        end=begin+sizeForThreads-1;

        if(nLines%nThreads!= 0 && i==nThreads-1){ //Aquí se realiza un ajuste para el ultimo hilo en el caso que no sea exacta la división de total de lineas entre el número de hilos.
            end++;
        }
        vThreads.push_back(std::thread(find_word, i, assignedLines[i], begin, end, objective));
    }

    std::for_each(vThreads.begin(), vThreads.end(), std::mem_fn(&std::thread::join));
    printResult();

    return EXIT_SUCCESS;
}
/* Controlar los argumentos que pasamos a la hora de ejecutarlo*/
void arguments_control( char *argv[],std::string &file, std::string &objective, int &nThreads){
    std::string archivo =LIBROS + std::string(argv[1]);
    std::ifstream File(archivo);
    if(File.good()){
        file=archivo;
    }else{
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("File does not exits.") )  <<std::endl;
        exit(EXIT_FAILURE);
    }
    
    objective=argv[2];
    if(isdigit(atoi(argv[3]))==0){
        nThreads=atoi(argv[3]);
    }else{
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("Please, introduce a valid number of threads.") )  <<std::endl;
        exit(EXIT_FAILURE);
    }
    
}
/* Devuelve el número de lineas de un archivo.*/
int number_of_lines(std::string file){
    int numLines = 0; 
    std::ifstream File(file); 

    while (File.good()) 
    { 
        std::string line; 
        std::getline(File, line); 
        ++numLines; 
    } 
    return numLines;
}

/* Es la función que ejecutaran los hilos y buscaran la palabra objetivo en el trozo de lineas asignado*/
void find_word(int thread,std::vector<std::string> assignedLines, int begin, int end, std::string objective){
    std::string word;
    std::string solution[3]; //vector de 3 posiciones para guardar la palabra anterior (0), la palabra encontrada (1) y la palabra siguiente (2).
    std::vector<std::string> line;
    for(std::size_t nLine = 0; nLine < assignedLines.size(); nLine++){
        line = splitLine(assignedLines[nLine]);
        solution[0]=""; //En caso que se salte a una nueva linea se reseteara el valor de la palabra anterior
        for(std::size_t position = 0; position< line.size(); position++){
            if(!analizeWord(objective).compare(analizeWord(line[position]))){
                solution[1]=line[position];
                if(position+1==line.size()){ // En el caso que se encuentre la palabra objetivo al final de la linea, el valor de la palabra siguiente sera nulo 
                    solution[2]="";
                }else{
                    solution[2]=line[position+1];
                }
                WordSearched wordFounded(objective, thread, begin, end, nLine+begin, solution[0], solution[1], solution[2]);
                std::lock_guard<std::mutex> semaphore(access); //Aquí bloquearemos el acceso a la estructura de datos
                vWords[thread].push_back(wordFounded);
            }
            solution[0]=line[position];//Las palabras ya leidas paran a la varible palabra anterior.
        }
            
    }
}
/* Se encarga de formatear una palabra para compararla con la con la palabra objetivo*/
std::string analizeWord(std::string word){
    std::string result;
    for (std::size_t i = 0; i < word.length(); i++) { //Esto sera para pasarlos a minuscula
        word[i] = tolower(word[i]);
    }
     std::remove_copy_if(word.begin(), word.end(), std::back_inserter(result), std::ptr_fun<int, int>(&std::ispunct));//Y esto para eliminar simbilos que no sean letras
    return result;
}

/* Devolvera una linea en un vector para recorrerla sin espacios*/
std::vector<std::string> splitLine(std::string line){
    std::string word;
    std::vector<std::string> result;
    std::stringstream buffer(line);
    while(std::getline(buffer, word, ' ')){
        result.push_back(word);
    }
    return result;
}

/* Asignara a cada hilo el número correspondiente de linea a leer*/
std::map<int,std::vector<std::string>> shareLines(std::string file, int nLines, int nThreads){
    std::ifstream File(file);
    std::string line;
    std::map<int, std::vector<std::string>> result;
    int sizeOfThreads = nLines/nThreads;
    for(int i = 0; i < nThreads; i++){
        for (int j = 0; j < sizeOfThreads; j++){
            std::getline(File, line);
            result[i].push_back(line);
        }
        if(i==nThreads-1 && nLines%nThreads!= 0){
                std::getline(File, line);
                result[i].push_back(line);
            }
    }
    return result;   
}
/* Mostrará el resultado por pantalla*/
void printResult(){
    for (std::size_t i = 0; i < vWords.size(); i++){
        for (std::size_t j = 0; j < vWords[i].size(); j++){
            vWords[i][j].toString();
        }   
    }
}