#include "pools.hpp"

void Pools::add_task(Task *task)
{
        // Add the task to the end of the queue
        this->m_taskList.push(task);
}

void Pools::execute(unsigned threads)
{
        // loop for the desired number of threads
        for (unsigned i = 0; i < threads; ++i) {
                // lambda function adds new threads to the m_threadPool vector
                m_threadPool.push_back(new std::thread([&]() {
                        while (true) {
                                // check if there are any tasks in the task list
                                if (!m_taskList.empty()) {
                                        // assign the first element of tasklist to task then pop said
                                        // task from the list, otherwise this will continually create threads
                                        // all with the same task

                                        m_tLock.lock();
                                        Task *task = m_taskList.front();
                                        m_taskList.pop();
                                        m_tLock.unlock();

                                        // the actual execution of the task, e.g runs Scanners execute member function
                                        task->execute();

                                        // once task is complete, delete it
                                        delete task;

                                        // this continue ensures the execution path doesn't hit the return
                                        // which causes only five tasks to be assigned to a single thread
                                        continue;
                                }
                                return;
                        }
                }));
        }
        // join all the threads once they're done their task
        std::for_each(m_threadPool.begin(), m_threadPool.end(),
                      [](std::thread *thread) { thread->join(); });

        // Clear all data from the vector, so it can be initialised again
        m_threadPool.clear();
}
