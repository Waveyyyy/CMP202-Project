#ifndef CMP202SCANNER_SCANNER_HPP
#define CMP202SCANNER_SCANNER_HPP

#include <cstdio>
#include <cstdint>
#include <atomic>
#include <mutex>

// SFML stuff
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "tasks.hpp"

class Scanner : public Task {
    public:
        /// Non-default constructor
        ///
        /// \param address IP address of remote host
        /// \param ports Vector containing ports supplied as command line args
        /// \param portIndex Index of the ports vector whose value will be scanned
        /// \param openPorts Vector containing ports that are open
        /// \param numOpen Atomic int that gets incremented each time an OPEN port is found
        /// \param numClosed Atomic int that gets increased each time a CLOSED port is found
        /// \param timeout Optional argument to specify maximum wait time for a connection
        ///
        Scanner(sf::IpAddress address, std::vector<uint16_t> *ports,
                size_t portIndex, std::vector<uint16_t> *openPorts,
                std::atomic<int> &numOpen, std::atomic<int> &numClosed,
                sf::Time timeout = sf::milliseconds(200));

        /// The main driving function for class Scanner
        ///
        /// Attempts a TCP connection to a given address and port.
        /// Based on the response will either add to the numberOpen
        /// or numberClosed vectors.
        ///
        void execute() override;

    private:
        // member variables
        sf::IpAddress m_address;
        std::vector<uint16_t> *m_portsList;
        size_t m_portIndex;
        std::vector<uint16_t> *m_openPorts;
        std::atomic<int> &m_numOpen;
        std::atomic<int> &m_numClosed;
        sf::Time m_timeout;
        std::mutex openPortsLock;
};

#endif
