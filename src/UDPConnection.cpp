#include "UDPConnection.h"

UDPConnection::UDPConnection()
{
    quit = false;
}

UDPConnection::~UDPConnection()
{
    SDLNet_FreePacket(packet);
    SDLNet_Quit();
}

bool UDPConnection::init(const string& ip, uint16_t remote_port, uint16_t local_port)
{
    cout << "Connecting to \n\tIP : " << ip << "\n\tPort : " << remote_port << endl;
	cout << "Local port : " << local_port << "\n\n";

	if (!init_sdl_net())
	{
        return false;
	}

	if (!open_port(local_port))
	{
        return false;
	}

	if (!set_ip_and_port(ip, remote_port))
	{
        return false;
	}

	if (!create_packet(512))
	{
        return false;
	}

	return true;
}

bool UDPConnection::init_sdl_net()
{
    cout << "Initializing SDL_net...\n";

    if (SDLNet_Init() == -1)
    {
        cout << "\tSDLNet_Init failed : " << SDLNet_GetError() << endl;
        return false;
    }

    cout << "\tSuccess!\n\n";
    return true;
}

bool UDPConnection::open_port(uint16_t port)
{
    cout << "Opening port " << port << "...\n";
    socket = SDLNet_UDP_Open(port);

    if (socket == nullptr)
    {
        cout << "\tSDLNet_UDP_Open failed : " << SDLNet_GetError() << endl;
        return false;
    }

    cout << "\tSuccess!\n\n";
    return true;
}

bool UDPConnection::set_ip_and_port(const string& ip, uint16_t port)
{
    cout << "Setting IP ( " << ip << " ) " << "and port ( " << port << " )\n";
    if (SDLNet_ResolveHost(&serverIP, ip.c_str(), port) == -1)
    {
        cout << "\tSDLNet_ResolveHost failed : " << SDLNet_GetError() << endl;
        return false;
    }

    cout << "\tSuccess!\n\n";
    return true;
}

bool UDPConnection::create_packet(int32_t packet_size)
{
    cout << "Creating packet with size " << packet_size << "...\n";

    packet = SDLNet_AllocPacket(packet_size);

    if (packet == nullptr)
    {
        cout << "\tSDLNet_AllocPacket failed : " << SDLNet_GetError() << endl;
        return false;
    }

    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;

    cout << "\tSuccess!\n\n";
    return true;
}

bool UDPConnection::send(const string& data)
{
    if (data == "quit")
    {
        prepare_packet(data);
        quit = true;
    }
    else
    {
        cout << "Type a message and hit enter\n";
        string msg = "";
        cin.ignore();
        getline(cin, msg);
        prepare_packet(msg);
    }

    if (SDLNet_UDP_Send(socket, -1, packet) == 0)
    {
        cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n"
				<< "==========================================================================================================\n";
        return false;
    }

    cout << "\tSuccess!\n"
        << "==========================================================================================================\n";

    return true;

}

void UDPConnection::prepare_packet(const string& message)
{
    const string str = "";
    memcpy(packet->data, str.c_str(), str.length());
    memcpy(packet->data, message.c_str(), message.length());
    packet->len = message.length();

    cout
        << "==========================================================================================================\n"
        << "Sending : \'" << packet->data << "\', Length : " << packet->len << "\n";
}

void UDPConnection::check_for_data()
{
    cout
        << "==========================================================================================================\n"
        << "Check for data...\n";

    if (SDLNet_UDP_Recv(socket, packet))
    {
        cout << "\tData received : " << packet->data << "\n";
        if (strcmp((char*) packet->data, "quit") == 0)
        {
            quit = true;
        }
    }
    else
    {
        cout  << "\tNo data received!\n";
    }
    cout << "==========================================================================================================\n";
}

bool UDPConnection::was_quit()
{
    return quit;
}
