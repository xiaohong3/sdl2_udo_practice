#include <iostream>
#include <UDPConnection.h>

using namespace std;

UDPConnection udp_connection;

int main()
{
    string ip;
    uint16_t local_port = 0;
    uint16_t remote_port = 0;


    cout
		<< "\n==========================================================================================================\n"
		<< "UDP connection - A simple test for UDP connections using SDL_Net!"
		<< "\n==========================================================================================================\n"
		<< "You'll be asked to enter the following :"
		<< "\n\tRemote IP   : The IP you want to connect to"
		<< "\n\tRemote Port : The port you want to connect to"
		<< "\n\tLocal port  : Uour port"
		<< "\nLocal port should be the same as remote port on the other instance of the application"
		<< "\n==========================================================================================================\n\n";

    cout << "Enter remote IP ( 127.0.0.1  for local connections ) : ";
    cin >> ip;

    cout << "...and remote port : ";
    cin >> remote_port;

    cout << "Enter local port : ";
    cin >> local_port;

    udp_connection.init(ip, remote_port, local_port);

    uint8_t command = 0;

    while (!udp_connection.was_quit())
    {
        cout
			<< "Your command : "
			<< "\n\t0 : Send a message"
			<< "\n\t1 : Quit"
			<< "\n\t2 : Check for data"
			<< endl;

        cin >> command;

        if (command == '0')
        {
            udp_connection.send("This is a test.");
        }
        else if (command == '1')
        {
            udp_connection.send("quit");
        }
        else if (command == '2')
        {
            udp_connection.check_for_data();
        }
        else
        {
            cout << "Illegal command\n";
        }
    }

    return 0;
}
