#ifndef CMP202SCANNER_POOLS_HPP
#define CMP202SCANNER_POOLS_HPP

#include <queue>
#include <vector>
#include <thread>
#include <mutex>

#include "tasks.hpp"

class Pools {
        /// adds a task queue (FIFO)
        void add_task(Task *task);

        void execute();

    private:
        // member variables
        std::queue<Task *> taskList;
        std::vector<std::thread *> threadPool;
        std::mutex tLock;
};

#endif
