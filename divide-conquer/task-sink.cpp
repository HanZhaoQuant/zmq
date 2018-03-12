#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    zmq::context_t context(1);

    zmq::socket_t receiver(context, ZMQ_PULL);

    receiver.bind("tcp://*:5558");

    zmq::message_t message;
    receiver.recv(&message);

    std::string smessage(static_cast<char *>(message.data()), message.size());
    std::cout << "message--:" << smessage << std::endl;

    /*struct timeval tstart;

    gettimeofday(&tstart, NULL);*/

    int task_nbr;
    int total_msec = 0;
    std::cout << "starting receiver...." << std::endl;
    for ( task_nbr = 0; task_nbr < 100; task_nbr++)
    {
        std::cout <<  task_nbr << std::endl;

        zmq::message_t message1;
        receiver.recv(&message1);
        std::string smessage(static_cast<char *>(message1.data()), message1.size());
        std::cout << "get results:" << smessage << std::endl;
        /*if ((task_nbr / 10) * 10 == task_nbr)
        {
            //std::cout << ":" << std::flush;
        }
        else
        {
            //std::cout << "." << std::flush;
        }*/
        std::cout << "task_nbr = " << task_nbr << std::endl;
    }

    struct timeval tend, tdiff;
    gettimeofday(&tend, NULL);

    /*if (tend.tv_usec < tstart.tv_usec)
    {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
        tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
    }
    else
    {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
        tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
    }*/

    total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
    std::cout << "\nTotal elapsed time: " << total_msec << " msec\n" << std::endl;

    return 0;
}
