#include "Scanner.hpp"

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

int main(int argc, char **argv)
{
        if (argc < 3) {
                printf("Example : ./CMP202Project 127.0.0.1 8080\n");
                exit(1);
        }
        auto address = sf::IpAddress(argv[1]);
        uint16_t port = strtol(argv[2], nullptr, 10);

        auto portScanner = new Scanner(address, port);

        portScanner->execute();
}
