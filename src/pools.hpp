#ifndef CMP202SCANNER_POOLS_HPP
#define CMP202SCANNER_POOLS_HPP

#include <queue>
#include <vector>
#include <thread>
#include <mutex>

#include "tasks.hpp"

class Pools {
    public:
        /// Adds tasks to the queue (FIFO)
        /// \param task A pointer to the task that will be added to the queue
        void add_task(Task *task);

        /// Main driver function for the Pools class
        /// This gives each thread a task and executes the task
        ///
        /// \param threads The number of threads to use (default: std::thread::hardware_concurrency)
        void execute(unsigned threads = std::thread::hardware_concurrency());

    private:
        // member variables
        std::queue<Task *> m_taskList;
        std::vector<std::thread *> m_threadPool;
        std::mutex m_tLock;
};

#endif
