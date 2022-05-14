#include "utils.hpp"
#include "scanner.hpp"
#include "tasks.hpp"
#include "pools.hpp"

#include <SFML/Network.hpp>

int main(int argc, char **argv)
{
        if (argc < 3) {
                printf("Examples : ./CMP202Project 127.0.0.1 8080\n");
                printf("\t\t   ./CMP202Project 127.0.0.1 21,22,53,80\n");
                printf("\t\t   ./CMP202Project 127.0.0.1 0-22\n");
                exit(1);
        }

        auto address = sf::IpAddress(argv[1]);
        std::vector<uint16_t> ports;

        argumentToPortslist(argv[2], &ports);
//
//        // TODO: this is debug code PLEASE REMOVE
//        for (unsigned short port : ports)
//        {
//               printf("Port %d\n", port);
//        }

        // TODO: Test code pls remove before submission
        for(unsigned short port : ports){
                auto test = new Scanner(address, port);
                test->execute();
                delete test;
        }

}
