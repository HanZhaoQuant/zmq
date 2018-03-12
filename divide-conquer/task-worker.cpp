#include "zhelpers.hpp"
#include <string>

int main(int argc, char const *argv[])
{
    zmq::context_t context(1);

    zmq::socket_t receiver(context, ZMQ_PULL);

    receiver.connect("tcp://localhost:5557");

    zmq::socket_t sender(context, ZMQ_PUSH);

    sender.connect("tcp://localhost:5558");

    while(true)
    {
        zmq::message_t message;

        int workload;

        receiver.recv(&message);

        std::string smessage( static_cast<char*> (message.data()), message.size());
        std::cout << "workload:" << smessage << std::endl;
        std::istringstream iss(smessage);
        iss >> workload;

        //s_sleep(workload);
        std::string s((char *)message.data());

        message.rebuild();

        

        zmq::message_t msg(s.size()+1);
        memcpy(msg.data(), s.c_str(), s.size() + 1);

        std::cout << "send message:" <<  s <<  std::endl;

        sender.send(msg);

        std::cout << "." << std::flush;
    }
    
    return 0;
}
