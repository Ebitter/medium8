#include <iostream>
#include <thread>
#include <stdio.h>
#include "blockingqueue.h"
using namespace std;
const int QUEUE_SIZE  = 100;
typedef BlockQueue<int> TQueue;

void produce(TQueue &queue)
{
    printf("produce start thread id=%d\n", std::this_thread::get_id().hash());
    for (int i = 0; i < QUEUE_SIZE*2; ++i)
    {
        queue.push_back(i);
        printf("thread id =%d, push=%d\n",std::this_thread::get_id().hash(), i);
    }
    printf("produce finish thread id=%d\n", std::this_thread::get_id().hash());
}

void consume(TQueue &queue)
{
    printf("conssume start thread id=%d\n", std::this_thread::get_id().hash());
    //while (false==queue.empty())
    while(1)
    {
        int tmp = queue.pop();
        printf("threadID=%d, consume=%d\n",std::this_thread::get_id().hash(), tmp);
        std::this_thread::sleep_for(chrono::milliseconds(100));
    }
    {
        printf("threadID=%d, finish!\n",std::this_thread::get_id().hash());
    }
}

int main()
{
    TQueue queue(QUEUE_SIZE);
    std::thread t1(produce, std::ref(queue));
    std::thread t2(consume, std::ref(queue));
    std::thread t3(consume, std::ref(queue));
    t3.join();
    t2.join();
    t1.join();
    return 0;
}
