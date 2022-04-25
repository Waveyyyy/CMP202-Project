#include "pools.hpp"

void Pools::add_task(Task *task)
{
        this->taskList.push(task);
}

void Pools::execute()
{
        // create sane amount of threads relating to machines number of logical processors/cores
        for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
                // [&] in a lambda function means all variables are captured by reference
                this->threadPool.push_back(new std::thread([&] {
                        // null pointer for task storing a reference to currently running task
                        Task *task;
                        while (true) {
                                // lock while messing with taskList queue
                                std::unique_lock<std::mutex> lock(tLock);
                                if (taskList.empty()) {
                                        return;
                                }
                                // set current task to first task in queue
                                // then remove said task from list
                                task = taskList.front();
                                taskList.pop();

                                // remove lock on task and run the task
                                tLock.unlock();
                                task->execute();

                                // delete completed task cos memory management :)
                                delete task;
                        }
                }));
                // auto because threadPool is of type std::thread *
                for (auto i : this->threadPool) {
                        i->join();
                }
        }
}
