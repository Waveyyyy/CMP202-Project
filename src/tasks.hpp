#ifndef CMP202SCANNER_THREADS_HPP
#define CMP202SCANNER_THREADS_HPP
class Task {
    public:
        /// virtual deconstructor for Task required for delete kword in pools.cpp
        virtual ~Task() = default;

        /// virtual function that gets overwritten by Scanner's .execute() method
        virtual void execute() = 0;
};

#endif
