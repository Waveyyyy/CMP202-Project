#include "scanner.hpp"
#include "tasks.hpp"
#include "pools.hpp"

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <sstream>

// TODO: Extract to utils.cpp
bool validPort(std::string &port)
{
        if (std::stol(port) > 65535 || std::stol(port) < 0)
        {
                return false;
        }

        return true;
}

// TODO: Extract to utils.cpp
void argumentToPortslist(const char *data, std::vector<uint16_t> *ports)
{
        std::stringstream rawPort;
        rawPort << data;
        std::string tmp;

        // reads the raw port string and splits on commas
        while (getline(rawPort, tmp, ',')) {
                // check if user has provided a range of ports
                if (tmp.find('-') != std::string::npos)
                {
                        // TODO: find more concise way to do this
                        std::string rangeStart = tmp.substr(0, tmp.find('-'));
                        std::string rangeEnd = tmp.substr(tmp.find('-')+1, tmp.length());

                        if (!((validPort(rangeStart) && (validPort(rangeEnd)))))
                        {
                               fprintf(stderr, "Range exceeds 16 bit int bounds: %s-%s", rangeStart.c_str(), rangeEnd.c_str());
                               exit(1);
                        }
                        for (int i = std::stoi(rangeStart); i < std::stoi(rangeEnd); ++i)
                        {
                                ports->push_back(i);
                        }
                        continue;
                }

                if (!validPort(tmp))
                {
                        fprintf(stderr, "Invalid Port : %s", tmp.c_str());
                        exit(1);
                }

                ports->push_back(std::stoi(tmp));
        }
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

        // TODO: this is debug code PLEASE REMOVE
        for (unsigned short port : ports)
        {
               printf("Port %d\n", port);
        }

        //         uint16_t port = strtol(argv[2], nullptr, 10);

        //         for (int i = 0; i < ports.size(); ++i) {
        //         }

        //         auto portScanner = new Scanner(address, port);

        //         portScanner->execute();
}
