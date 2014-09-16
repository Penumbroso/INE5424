// join_test2.cc
#include <thread.h>
#include <utility/ostream.h>
#include <mutex.h>
#include <alarm.h>

#define NUM 2

Mutex table;
OStream cout;

int function(int i)
{
    cout << "Thread " << i << " ran.\n";
    return i;
}

int main (int argc, char *argv[])
{
    cout << "Creating thread\n";
    Thread * t = new Thread(function, 1);

    cout << "Yield...\n";
    Thread::yield();

    cout << "Join:\n";
    int r = t->join();

    cout << "Return: " << r << '\n';
    return 0;
}
