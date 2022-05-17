#ifndef CMP202PROJECT_UTILS_HPP
#define CMP202PROJECT_UTILS_HPP

#include "tasks.hpp"

#include <vector>
#include <cstring>
#include <sstream>

class SortPorts : public Task {
    public:
        /// Non-default constructor
        ///
        /// \param ports Pointer to (unsorted) ports vector
        /// \param leftMost Argument specifying the index where smallest values should begin
        /// \param rightMost The size of the vector minus 1
        ///
        SortPorts(std::vector<uint16_t> *ports, int leftMost, int rightMost);

        /// Recursive function implementing the quicksort algorithm
        /// \param ports Pointer to the ports vector
        /// \param leftMost Index at which sorted values will be placed
        /// \param rightMost Index of value that will be sorted next
        void quickSortPortsList(std::vector<uint16_t> *ports, int leftMost,
                                int rightMost);

        /// Effectively searches through a subarray and sorts the values within
        ///
        /// \param ports Pointer to the ports vector
        /// \param leftMost Index at which subarray starts
        /// \param rightMost Index at which subarray ends
        /// \return Pivot point used with quickSortPortsList which gives new subarray in next recursive call
        static int partitionPortsList(std::vector<uint16_t> *ports,
                                      int leftMost, int rightMost);

        /// Main driver function for SortPorts class
        ///
        /// Runs the recursive function, quickSortPortsList
        void execute() override;

    private:
        // Member variables
        std::vector<uint16_t> *m_ports;
        int m_leftMost;
        int m_rightMost;
};

/// Checks if a supplied port value is within the bounds of a unsigned short
///
/// \param port The string representation of the port to be checked
/// \return true or false depending if port is between 0 and 65535
bool validPort(std::string &port);

/// Converts the supplied argument string of ports to a vector of ports
///
/// \param data The string of ports supplied in argv[2]
/// \param ports The vector to store the individual ports into
void argumentToPortslist(const char *data, std::vector<uint16_t> *ports);

#endif //CMP202PROJECT_UTILS_HPP
