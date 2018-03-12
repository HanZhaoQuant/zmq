#include "zhelpers.hpp"

int main(int argc, char const *argv[])
{
    zmq::context_t context(1);
    zmq::socket_t requester(context, ZMQ_REQ);

    requester.connect("tcp://localhost:5559");

    for(int i = 0; i < 10; i++)
    {
        s_send(requester, "Hello");

        std::string string = s_recv(requester);

        std::cout << "Receiver reply " << i << " [" << string << "] " << std::endl;    
    }
    

    return 0;
}
