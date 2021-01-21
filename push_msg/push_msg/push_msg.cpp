#include <iostream>
#include <thread>
#include <Windows.h>

using namespace std;

void thread_crontab()
{   
    int i = 0;
    while (true) {
        cout << "Thread 01 is working ！" << i<< endl;
        int sum = 0;
        for (int j = 0; j < 100000; j++) {
            cout << "demo" << endl;
            sum += j;
        }
        std::this_thread::sleep_for(std::chrono::seconds(100));
        i++;

    }
}

int main()
{
    thread task01(thread_crontab);
    task01.join();

    for (int i = 0; i < 5; i++)
    {
        cout << "Main thread is working ！" << endl;
        Sleep(200);
    }
    while (1) {};
}