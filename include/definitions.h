#ifndef DEFINITIONS
#define DEFINITIONS


#define LIBROS "./libros"
#define LOG_PATH "./log"

/*Valores estáticos*/
#define NCLIENTS 50
#define NTHREADS 2
#define BUFFER 4

#include "../src/Request.cpp"
#include "../src/QueueProtected.cpp"
#include "../src/Client.cpp"
#include <queue>


/*Flag para comprobar el id del cliente con el devuelto en la operacion de pago*/
int id_flag=-1;
int credits=-1;
bool end_program=false;

/*Variable para controlar a los clientes*/
std::condition_variable cv_queue;

/*Semaforo para controlar la cola de peticiones de pago*/
std::mutex sem_queue;

/*Cola de peticiones de recarga*/
QueueProtected requests;

std::vector<Client> vClients;

std::vector<std::string> WORDS =
{
    "lineas",
    "la",
    "palabra",
    "ley"
};

#endif