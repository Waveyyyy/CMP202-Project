#ifndef CMP202PROJECT_UTILS_HPP
#define CMP202PROJECT_UTILS_HPP

#include <vector>
#include <cstring>
#include <sstream>

bool validPort(std::string &port);

void argumentToPortslist(const char *data, std::vector<uint16_t> *ports);

#endif //CMP202PROJECT_UTILS_HPP
