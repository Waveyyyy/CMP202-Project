#include "utils.hpp"

SortPorts::SortPorts(std::vector<uint16_t> *ports, int leftMost, int rightMost)
        : m_ports(ports), m_leftMost(leftMost), m_rightMost(rightMost - 1)
{
}

void SortPorts::quickSortPortsList(std::vector<uint16_t> *ports, int leftMost,
                                   int rightMost)
{
        if (leftMost < rightMost) {
                int pivot = partitionPortsList(ports, leftMost, rightMost);
                quickSortPortsList(ports, leftMost, pivot - 1);
                quickSortPortsList(ports, pivot + 1, rightMost);
        }
}

int SortPorts::partitionPortsList(std::vector<uint16_t> *ports, int leftMost,
                                  int rightMost)
{
        int pivotIndex = rightMost;
        int storeIndex = leftMost - 1;

        for (int i = leftMost; i < rightMost; ++i) {
                if (ports->at(i) <= ports->at(pivotIndex)) {
                        ++storeIndex;

                        std::iter_swap(ports->begin() + i,
                                       ports->begin() + pivotIndex);
                }
                std::iter_swap(ports->begin() + pivotIndex,
                               ports->begin() + (storeIndex + 1));
        }
        return storeIndex + 1;
}

void SortPorts::execute()
{
        quickSortPortsList(m_ports, m_leftMost, m_rightMost);
}

bool validPort(std::string &port)
{
        if (std::stoi(port) > 65535 || std::stoi(port) < 0) {
                return false;
        }

        return true;
}

void argumentToPortslist(const char *data, std::vector<uint16_t> *ports)
{
        std::stringstream rawPort;
        rawPort << data;
        std::string tmp;

        // iterate through values delimited by commas in the provided ports string
        while (getline(rawPort, tmp, ',')) {
                // check if user has provided a range of ports
                if (tmp.find('-') == std::string::npos) {
                        if (!validPort(tmp)) {
                                fprintf(stderr, "Invalid Port : %s",
                                        tmp.c_str());
                                exit(1);
                        }
                        ports->push_back(std::stoi(tmp));
                        continue;
                }
                // allows user to supply "-" as a shorthand for 0-65535
                if (std::strcmp(tmp.c_str(), "-") == 0) {
                        for (int i = 0; i <= 65535; ++i) {
                                ports->push_back(i);
                        }
                        break;
                }
                std::string rangeStart = tmp.substr(0, tmp.find('-'));
                std::string rangeEnd =
                        tmp.substr(tmp.find('-') + 1, tmp.length());

                if (std::stoi(rangeStart) > std::stoi(rangeEnd)) {
                        fprintf(stderr,
                                "Starting value cannot be greater than end value: %s-%s",
                                rangeStart.c_str(), rangeEnd.c_str());
                        exit(1);
                }

                if (!((validPort(rangeStart) && (validPort(rangeEnd))))) {
                        fprintf(stderr, "Range cannot exceed 65535: %s-%s",
                                rangeStart.c_str(), rangeEnd.c_str());
                        exit(1);
                }
                for (int i = std::stoi(rangeStart); i < std::stoi(rangeEnd);
                     ++i) {
                        ports->push_back(i);
                }
        }
}