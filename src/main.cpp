#include "scanner.hpp"
#include "tasks.hpp"
#include "pools.hpp"

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string.h>
#include <sstream>

void argumentToPortslist(const char *data, std::vector<uint16_t> *ports)
{
        std::stringstream rawPort;
        rawPort << data;
        std::string tmp;

        if (getline(rawPort, tmp, ',')) {
        }
        ports->push_back(1);
}

int main(int argc, char **argv)
{
        if (argc < 3) {
                printf("Example : ./CMP202Project 127.0.0.1 8080\n");
                exit(1);
        }
        //         auto address = sf::IpAddress(argv[1]);
        std::vector<uint16_t> ports;

        argumentToPortslist(argv[2], &ports);

        //         uint16_t port = strtol(argv[2], nullptr, 10);

        //         for (int i = 0; i < ports.size(); ++i) {
        //         }

        //         auto portScanner = new Scanner(address, port);

        //         portScanner->execute();
}
