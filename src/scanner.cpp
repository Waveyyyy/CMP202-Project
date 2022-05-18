#include "scanner.hpp"

Scanner::Scanner(sf::IpAddress address, std::vector<uint16_t> *port,
                 size_t portIndex, std::vector<uint16_t> *openPorts,
                 std::atomic<int> &numOpen, std::atomic<int> &numClosed,
                 sf::Time timeout)
        : m_address(address), m_portsList(port), m_portIndex(portIndex),
          m_openPorts(openPorts), m_numOpen(numOpen), m_numClosed(numClosed),
          m_timeout(timeout)
{
}

void Scanner::execute()
{
        // Connect to a TCP socket with the supplied address, port and timeout(default 200ms)
        if (sf::TcpSocket().connect(m_address, m_portsList->at(m_portIndex),
                                    m_timeout) == sf::Socket::Done) {
                // lock the openPortsLock mutex to allow for safely adding the port value to the m_openPorts vector
                std::unique_lock<std::mutex> lock(openPortsLock);
                m_openPorts->emplace_back(m_portsList->at(m_portIndex));

                // Since a port has been found open, increment the m_numOpen counter
                ++m_numOpen;
                return;
        }
        // If the execution path reaches here the port was found to be closed, therefore increment the m_numClosed counter
        ++m_numClosed;
}
