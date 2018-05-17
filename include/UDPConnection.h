#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <SDL2/SDL_net.h>
#include <iostream>
#include <sstream>

using namespace std;

struct UDPConnection
{
    public:
        UDPConnection();
        ~UDPConnection();
        bool init(const string& ip, uint16_t remote_port, uint16_t local_port);
        bool send(const string& data);
        void check_for_data();
        bool was_quit();

    private:
        bool quit;
        UDPsocket socket;
        IPaddress serverIP;
        UDPpacket* packet;

        bool init_sdl_net();
        bool create_packet(int32_t packet_size);
        bool open_port(uint16_t port);
        bool set_ip_and_port(const string& ip, uint16_t port);
        void prepare_packet(const string& message);
};

#endif // UDPCONNECTION_H
