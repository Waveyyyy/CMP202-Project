#include "utils.hpp"
#include "scanner.hpp"
#include "pools.hpp"

#include <SFML/Network.hpp>
#include <atomic>
#include <chrono>

int main(int argc, char **argv)
{
        // Print general help message if incorrect amount of arguments are supplied
        if (argc < 3) {
                printf("Examples :\t./CMP202Project 127.0.0.1 8080\n");
                printf("\t\t\t./CMP202Project 127.0.0.1 21,22,53,80\n");
                printf("\t\t\t./CMP202Project 127.0.0.1 0-22\n");
                printf("\t\t\tThe number of threads can be supplied by adding a number after the ports list\n");
                exit(1);
        }

        // check that the user supplied a valid IP address
        // if a valid ip has been supplied, initialise the address variable with it
        if (std::string(argv[1]).find('.') == std::string::npos) {
                fprintf(stderr, "%s\n", std::string(argv[1]).c_str());
                fprintf(stderr, "Invalid IP address\n");
                exit(1);
        }
        auto address = sf::IpAddress(argv[1]);

        // Convert the ports provided by the user into a vector
        // allowing to be used with the Scanner function
        std::vector<uint16_t> ports;
        argumentToPortslist(argv[2], &ports);

        // Initialise variables that will be passed between threads
        std::vector<uint16_t> openPorts;
        std::atomic<int> numOpen = { 0 };
        std::atomic<int> numClosed = { 0 };

        // create an object of type Pools that will contain and run the tasks on threads
        Pools taskPool;

        printf("Scanning...\n\n");

        // Timing stuff, starts right before threads are assigned their tasks
        std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();

        // loop for the amount of items in the ports vector
        for (unsigned i = 0; i < ports.size() - 1; ++i) {
                // ensure the first task ran is the one that sorts the ports vector
                if (i == 0) {
                        taskPool.add_task(
                                new SortPorts(&ports, 0, ports.size()));
                }
                // Add all the scanner tasks with their relevant informatin (e.g which port they will scan)
                taskPool.add_task(new Scanner(address, &ports, i, &openPorts,
                                              numOpen, numClosed));
        }

        // check if the threads argument has been provided
        // if so create taskPool and pass the number of threads in
        // otherwise the default value (std::thread::hardware_concurrency) is used
        if (argc == 4) {
                int numThreads = std::stoi(argv[3]);
                taskPool.execute(numThreads);
        } else {
                taskPool.execute();
        }

        // end the timing, immediately after all work has been completed
        std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();

        // print how long the scan took, and the number of open ports found
        printf("Scan completed in %.3f ms, (%u open ports)\n\n",
               float(std::chrono::duration_cast<std::chrono::microseconds>(
                             end - start)
                             .count()) /
                       1000,
               numOpen.load());

        // only print number of closed ports if it's not 0
        if (numClosed.load() != 0)
                printf("Not shown: %u closed ports\n", numClosed.load());

        // print ports that are open
        if (!openPorts.empty()) {
                // sort the open ports list for nicer outputting
                (new SortPorts(&openPorts, 0, openPorts.size()))->execute();

                for (auto i : openPorts) {
                        printf("Port %d/tcp is open\n", i);
                }
        }
}
