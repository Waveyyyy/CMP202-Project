#include "Scanner.hpp"

Scanner::Scanner(sf::IpAddress address, uint16_t port, sf::Time timeout)
        : m_address(address), m_port(port), m_timeout(timeout)
{
}

void Scanner::execute()
{
        // Connect to a TCP socket with the supplied address, port and timeout
        if (sf::TcpSocket().connect(m_address, m_port, m_timeout) ==
            sf::Socket::Done) {
                // Add to the numOpen counter and openPort vector
                printf("[*] Connected to : %s:%d\n",
                       this->m_address.toString().c_str(), this->m_port);
                return;
        }
        // Add to the numClosed counter
        printf("[!] Connection failed\n");
}
