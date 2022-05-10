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
#include <atomic>
#include <dirent.h>
#include "WordSearched.cpp"
#include "Client.cpp"
#include "PaySystem.cpp"
#include "QueueProtected.cpp"
#include "SemCounter2.cpp"

/*Funciones definidas*/
int number_of_lines(std::string file);
void create_threads(std::string file, Client& c);
void find_word(int thread,std::vector<std::string> assignedLines, int begin, int end, Client c);
std::map<int, std::vector<std::string>> shareLines(std::string file, int nLines);
std::vector<std::string> splitLine(std::string line);
std::string analizeWord(std::string word);
void printResult();
void list_dir();

void generateClient(int id);
/*Valores estáticos*/
#define NCLIENTS 4
#define NTHREADS 4
#define BUFFER 4

/*Variables globales*/
SemCounter sem(BUFFER);
std::mutex access;
std::vector<std::thread> vThreads;
std::vector<Client> vClients;
std::vector<std::string> vLibros;
std::map<int,std::vector<WordSearched>> vWords;


/* El main se encargara de la creación de hilos y su finalización*/
int main(int argc, char *argv[]){
    int premium;
    //int premium;
    std::string word;
    list_dir();
    for(int i = 0; i<NCLIENTS; i++){
        word = WORDS[(rand()%WORDS.size())];
        generateClient(i);
        // if(i%2==0){
        //     /**/
        //     Client c(i,word);
        //     vClients.push_back(std::thread(generateClient, std::ref(c)));
        // }else{
        //     premium = (rand()%2);
        //     if(premium==0){
        //         Client c(i,-1, word);
        //         vClients.push_back(std::thread(generateClient, std::ref(c)));
        //     }else{
        //         Client c(i,100, word);
        //         vClients.push_back(std::thread(generateClient, std::ref(c)));
        //     }
        // }
    }
    std::for_each(vThreads.begin(), vThreads.end(), std::mem_fn(&std::thread::join));

}

void list_dir(){
    std::string dirPath="./libros";
    DIR * directorio;
    struct dirent *elemento;
    std::string elem;
    std::string ss;
    if((directorio = opendir(dirPath.c_str()))){
        while((elemento = readdir(directorio))){
            elem = elemento->d_name;
            if(elem != "." && elem!=".."){
                vLibros.push_back(elem);
            }  
        
        }
    
    }
    closedir(directorio);    
}

void generateClient(int id){
    std::vector<std::thread> vSearch;
    std::mutex access;

    sem.wait();
    vClients.push_back(Client());
    /*
    for (std::size_t i = 0; i < vLibros.size(); i++){
        vSearch.push_back(std::thread(create_threads, vLibros[i], std::ref(c)));
    }
    std::for_each(vSearch.begin(), vSearch.end(), std::mem_fn(&std::thread::join));
    */
    sem.signal();
}

/* Devuelve el número de lineas de un archivo.*/
int number_of_lines(std::string file){
    int numLines = 0;
    std::string dir = "./libros/"+file;
    std::ifstream File(dir); 

    while (File.good()) 
    { 
        std::string line; 
        std::getline(File, line); 
        ++numLines; 
    } 
    return numLines;
}

void create_threads(std::string file, Client& c){
    int nLines;
    int sizeForThreads;
    std::map<int, std::vector<std::string>> assignedLines;
    int begin, end;

    nLines=number_of_lines(file);
    std::cout<<"[CLiente "<<c.getId()<<"] "<<nLines<<"-"<<file<<std::endl;
    if(nLines<NTHREADS){
        std::cerr << ERROR("[ERROR]-- ")<<WARNING(UNDERLINE("More threads than lines") )  <<std::endl;
        exit(EXIT_FAILURE);
    }
    sizeForThreads = nLines/NTHREADS;
    assignedLines=shareLines(file,nLines);
    for (int i = 0; i < NTHREADS; i++) {
        begin=i*sizeForThreads+1;
        end=begin+sizeForThreads-1;

        if(nLines%NTHREADS!= 0 && i==NTHREADS-1){ //Aquí se realiza un ajuste para el ultimo hilo en el caso que no sea exacta la división de total de lineas entre el número de hilos.
            end++;
        }
        //vThreads.push_back(std::thread(find_word, i, assignedLines[i], begin, end, std::ref(c)));
    }

    std::for_each(vThreads.begin(), vThreads.end(), std::mem_fn(&std::thread::join));
}
/* Es la función que ejecutaran los hilos y buscaran la palabra objetivo en el trozo de lineas asignado*/
void find_word(int thread,std::vector<std::string> assignedLines, int begin, int end, Client c){
    std::string word;
    std::string solution[3]; //vector de 3 posiciones para guardar la palabra anterior (0), la palabra encontrada (1) y la palabra siguiente (2).
    std::vector<std::string> line;
    for(std::size_t nLine = 0; nLine < assignedLines.size(); nLine++){
        line = splitLine(assignedLines[nLine]);
        solution[0]=""; //En caso que se salte a una nueva linea se reseteara el valor de la palabra anterior
        for(std::size_t position = 0; position< line.size(); position++){
            if(!analizeWord(c.getObjective()).compare(analizeWord(line[position]))){
                if(c.getBalance()==0){
                    //ps.rechargeBalance();
                }else{
                    c.payCredit();
                }
                solution[1]=line[position];
                if(position+1==line.size()){ // En el caso que se encuentre la palabra objetivo al final de la linea, el valor de la palabra siguiente sera nulo 
                    solution[2]="";
                }else{
                    solution[2]=line[position+1];
                }
                WordSearched wordFounded(c.getObjective(), thread, begin, end, nLine+begin, solution[0], solution[1], solution[2]);
                std::lock_guard<std::mutex> semaphore(access); //Aquí bloquearemos el acceso a la estructura de datos
                vWords[thread].push_back(wordFounded);
            }
            solution[0]=line[position];//Las palabras ya leidas paran a la varible palabra anterior.
        }
            
    }
    sem.signal();
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
std::map<int,std::vector<std::string>> shareLines(std::string file, int nLines){
    std::ifstream File(file);
    std::string line;
    std::map<int, std::vector<std::string>> result;
    int sizeOfThreads = nLines/NTHREADS;
    for(int i = 0; i < NTHREADS; i++){
        for (int j = 0; j < sizeOfThreads; j++){
            std::getline(File, line);
            result[i].push_back(line);
        }
        if(i==NTHREADS-1 && nLines%NTHREADS!= 0){
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