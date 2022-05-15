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
        /// @ports Pointer to (unsorted) ports vector
        /// @leftMost Optional argument specifying the index where smallest values should begin
        /// @rightMost The size of the vector minus 1
        ///
        SortPorts(std::vector<uint16_t> *ports, int leftMost, int rightMost);

        /// Recursive function implementing the quicksort algorithm
        /// @ports Pointer to the ports vector
        /// @leftMost Index at which sorted values will be placed
        /// @rightMost Index of value that will be sorted next
        void quickSortPortsList(std::vector<uint16_t> *ports, int leftMost,
                                int rightMost);

        /// Effectively searches through a subarray and sorts the values within
        /// @ports Pointer to the ports vector
        /// @leftMost Index at which subarray starts
        /// @rightMost Index at which subarray ends
        /// @return Pivot point used with quickSortPortsList which gives new subarray in next recursive call
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

bool validPort(std::string &port);

void argumentToPortslist(const char *data, std::vector<uint16_t> *ports);

#endif //CMP202PROJECT_UTILS_HPP
