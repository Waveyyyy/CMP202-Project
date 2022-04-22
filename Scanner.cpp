#include "Scanner.hpp"

Scanner::Scanner(sf::IpAddress address, uint16_t port, sf::Time timeout)
	: m_address(address), m_port(port), m_timeout(timeout)
{
}

void Scanner::execute()
{
	if (sf::TcpSocket().connect(m_address, m_port, m_timeout) ==
	    sf::Socket::Done) {
		printf("[*] Connected to : %s ", this->m_address.toString().c_str());
		return;
	}
	printf("[!] Connection failed\n");
}
