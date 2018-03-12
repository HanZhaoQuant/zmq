#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

#define within(num) (int)((float)num * random() / (RAND_MAX + 1.0))

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    zmq::context_t context(1);

    zmq::socket_t publisher (context, ZMQ_PUB);

    publisher.bind("tcp://*:6665");
    //publisher.bind("ipc://weather.ipc");

    srandom( (unsigned) time (NULL));

    while(true)
    {
        int zipcode, temperature, relhumidity;
        zipcode = within(100000);
        temperature = within(215) -80;
        relhumidity = within(50) + 10;

        zmq::message_t message(20);
        snprintf( (char*) message.data(), 20 , "%05d %d %d", zipcode, temperature, relhumidity);
        publisher.send( message);
    }

    return 0;
}