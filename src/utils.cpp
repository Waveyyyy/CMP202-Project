#include "utils.hpp"

SortPorts::SortPorts(std::vector<uint16_t> *ports, int leftMost, int rightMost)
        : m_ports(ports), m_leftMost(leftMost), m_rightMost(rightMost - 1)
{
}

void SortPorts::quickSortPortsList(std::vector<uint16_t> *ports, int leftMost,
                                   int rightMost)
{
        if (leftMost < rightMost) {
                // find pivot element
                // elements smaller than pivot are on the left
                // elements larger than pivot are on the right
                int pivot = partitionPortsList(ports, leftMost, rightMost);

                // recursive call on the left of pivot
                quickSortPortsList(ports, leftMost, pivot - 1);

                // recursive call on the right of pivot
                quickSortPortsList(ports, pivot + 1, rightMost);
        }
}

int SortPorts::partitionPortsList(std::vector<uint16_t> *ports, int leftMost,
                                  int rightMost)
{
        // rightmost value is pivot
        int pivot = ports->at(rightMost);

        // pointer for the greater element
        int storeIndex = leftMost - 1;

        // loop through each element and compare against pivot
        for (int i = leftMost; i < rightMost; ++i) {
                if (ports->at(i) <= pivot) {
                        // if element smaller than or equal to pivot is found
                        // swap with greater element found at storeIndex
                        ++storeIndex;

                        // swapping of current value at i with value at storeIndex
                        std::iter_swap(ports->begin() + i,
                                       ports->begin() + storeIndex);
                }
        }
        // swap pivot with the greater element found at storeIndex
        std::iter_swap(ports->begin() + rightMost,
                       ports->begin() + (storeIndex + 1));

        // return index from where the partition is done
        return storeIndex + 1;
}

void SortPorts::execute()
{
        quickSortPortsList(m_ports, m_leftMost, m_rightMost);
}

bool validPort(std::string &port)
{
        // check if port is within the bounds of a unsigned short (0-65535)
        if (std::stoi(port) > 65535 || std::stoi(port) < 0) {
                return false;
        }
        return true;
}

void argumentToPortslist(const char *data, std::vector<uint16_t> *ports)
{
        // convert the raw port string from argv (*data) to a stringstream
        // this allows for using getline to split on commas
        std::stringstream rawPort;
        rawPort << data;
        std::string tmp;

        // iterate through values delimited by commas in the provided ports string
        // values between commas are put into the tmp variable
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
                // allows user to supply "-" as a shorthand for scanning all ports
                if (std::strcmp(tmp.c_str(), "-") == 0) {
                        for (int i = 0; i <= 65535; ++i) {
                                ports->push_back(i);
                        }
                        break;
                }

                // initialise two variables one containing the value on the left side of the "-" symbol
                // and one containing the value on the right side of the "-" symbol
                std::string rangeStart = tmp.substr(0, tmp.find('-'));
                std::string rangeEnd =
                        tmp.substr(tmp.find('-') + 1, tmp.length());

                // if either value is not deemed a valid port then error out
                if (!((validPort(rangeStart) && (validPort(rangeEnd))))) {
                        fprintf(stderr, "Range cannot exceed 65535: %s-%s",
                                rangeStart.c_str(), rangeEnd.c_str());
                        exit(1);
                }

                // if the starting value is greater than the end value error out
                if (std::stoi(rangeStart) > std::stoi(rangeEnd)) {
                        fprintf(stderr,
                                "Starting value cannot be greater than end value: %s-%s",
                                rangeStart.c_str(), rangeEnd.c_str());
                        exit(1);
                }

                // loop through range and add i to ports vector
                for (int i = std::stoi(rangeStart); i < std::stoi(rangeEnd);
                     ++i) {
                        ports->push_back(i);
                }
        }
}