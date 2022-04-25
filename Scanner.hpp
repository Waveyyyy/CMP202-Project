#ifndef CMP209SCANNER_SCANNER_HPP
#define CMP209SCANNER_SCANNER_HPP

#include <cstdio>
#include <cstdint>

// SFML stuff
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Scanner {
    public:
        /// Non-default constructor
        ///
        /// @address IP address of remote host
        /// @port Specific port of the host to scan
        /// @timeout Optional argument to specify maximum wait time for a connection
        ///
        Scanner(sf::IpAddress address, uint16_t port,
                sf::Time timeout = sf::milliseconds(100));

        /// The main driving function for class Scanner
        ///
        /// Attempts a TCP connection to a given address and port.
        /// Based on the response will either add to the numberOpen
        /// or numberClosed vectors.
        ///
        void execute();

    private:
        // member variables
        sf::IpAddress m_address;
        uint16_t m_port;
        sf::Time m_timeout;
};

#endif
