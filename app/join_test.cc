// EPOS Thread Join Test Program

#include <utility/ostream.h>
#include <mutex.h>
#include <thread.h>
#include <alarm.h>

Mutex table;

using namespace EPOS;

OStream cout;

int loopThread(int threadNumber){
    int i=0;
    while(i<30) {
        table.lock();
        cout << "threadNumber: " << threadNumber << "\texecution number: " << i << endl;
        table.unlock();
        Delay waitLoop(300000);
        i++;
    }
}

int loopThread(int threadNumber, Thread * toJoin){
    int i = 0;
    while(i < 30) {
        table.lock();
        cout << "threadNumber: " << threadNumber << "\texecution number: " << i << endl;
        table.unlock();
        Delay waitLoop(300000);
        if(i == 10) toJoin->join();
        i++;
    }
}

int main()
{
    Thread * t1 = new Thread(&loopThread, 1);
    Thread * t2 = new Thread(&loopThread, 2, t1);

    return 0;
}
