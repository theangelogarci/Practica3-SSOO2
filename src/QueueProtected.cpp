#ifndef QUEU
#define QUEU

#include <queue>
#include <mutex>
#include "Request.cpp"
class QueueProtected
{
private:
    std::queue<Request> queue;
public:
    QueueProtected();
    void add(Request r);
    Request remove();
    bool checkEmpty();
};

QueueProtected::QueueProtected()
{
}
bool QueueProtected::checkEmpty(){
    return this->queue.empty();
}

void QueueProtected::add(Request r){
    queue.push(r);
}


Request QueueProtected::remove(){
    Request r = queue.front();
    queue.pop();
    return r;
}
#endif