#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>


using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    zmq::context_t context (1);

    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to server....." << std::endl;

    socket.connect ("tcp://localhost:6666");

    for (int i = 0; i < 10; i++)
    {
        zmq::message_t send_message(6);
        memcpy (send_message.data(), "hello", 6);

        std::cout << "sending message:" << i << ".." << std::endl;

        socket.send (send_message);

        zmq::message_t reply;
        socket.recv (&reply);
        std::string smessage(static_cast<char *>(reply.data()), reply.size());
        std::cout << "received word:" << i << ": " << smessage << std::endl;
    }

    return 0;
}
