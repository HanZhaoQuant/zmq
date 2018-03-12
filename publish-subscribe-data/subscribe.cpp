#include <zmq.hpp>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    zmq::context_t context(1);

    cout << "Collecting updates from weather server...\n" << endl;

    zmq::socket_t subscriber(context, ZMQ_SUB);

    subscriber.connect("tcp://localhost:6665");

    const char *filter = (argc > 1) ? argv[1] : "10002";

    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++)
    {
        zmq::message_t update;
        int zipcode, temperature, relhumidity;
        subscriber.recv( &update);

        std::istringstream iss( static_cast<char*> (update.data()));
        iss >> zipcode >> temperature >> relhumidity ;
        total_temp += temperature;
    }

    cout << "Average temperature for zipcode '" << filter << "' was " 
            << (int) (total_temp / update_nbr) << "F" << endl; 

    return 0;
}