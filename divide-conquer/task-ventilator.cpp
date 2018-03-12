#include <zmq.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#define within(num) (int) ((float) num * random() / (RAND_MAX + 1.0) )


int main(int argc, char const *argv[])
{
    zmq::context_t context(1);

    // socket to send message on 
    zmq::socket_t sender(context, ZMQ_PUSH);

    sender.bind("tcp://*:5557");

    std::cout << "Press Enter when the workers are ready: " << std::endl;

    getchar();

    std::cout << "Sending tasks to workers..\n" << std::endl;

    zmq::socket_t sink (context, ZMQ_PUSH);

    sink.connect("tcp://localhost:5558");

    zmq::message_t message(2);

    memcpy( message.data(), "0", 1);

    sink.send(message);

    srandom ((unsigned) time( NULL));

    // send 100 tasks

    int task_nbr;
    int total_msec = 0;
    for (task_nbr = 0; task_nbr < 100; task_nbr++)
    {
        int workload;

        workload = within(100) + 1;

        total_msec += workload;

        message.rebuild (10);

        memset( message.data(), '\0', 10);

        sprintf( (char *) message.data(), "%d", workload);

        sender.send(message);

    }

    std::cout << "Total expected cost: " << total_msec << " msec" << std::endl;
    sleep(1);   

    return 0;
}

