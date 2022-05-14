#include "scanner.hpp"

Scanner::Scanner(sf::IpAddress address, uint16_t port, sf::Time timeout)
        : m_address(address), m_port(port), m_timeout(timeout)
{
}

void Scanner::execute()
{
        // Connect to a TCP socket with the supplied address, port and timeout(default 200ms)
        if (sf::TcpSocket().connect(m_address, m_port, m_timeout) ==
            sf::Socket::Done) {
                // TODO: Increment the numOpen counter and add port to the openPort vector
                printf("[*] Port tcp/%d is open\n", this->m_port);
                return;
        }
        // TODO: Increment the numClosed counter
        printf("[!] Connection failed\n");
}
