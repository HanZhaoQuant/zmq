#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    zmq::context_t context(1);

    zmq::socket_t socket(context, ZMQ_REP);

    socket.bind("tcp://*:6666");

    while (true)
    {
        zmq::message_t request;

        socket.recv(&request);

        std::string smessage(static_cast<char *>(request.data()), request.size());

        std::cout << "get data:" << smessage << std::endl;

        sleep(1);

        zmq::message_t reply(6);

        memcpy(reply.data(), "Hello", 6);

        socket.send(reply);
    }

    return 0;
}
