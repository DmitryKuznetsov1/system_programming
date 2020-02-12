#pragma once
#include <signal.h>
#include <sched.h>
#include <functional>
#include <sys/types.h>
#include <sys/wait.h>

#define CHECK(func) \
if ((func) == -1) { \
    throw std::system_error(errno, std::generic_category()); \
}

#define STACK_SIZE (1024 * 1024)


int childFunc(void *ptr) {
    auto *fn = static_cast<std::function<int()> *>(ptr);
    return (*fn)();
}


class my_thread {
protected:
    pid_t pid;
    char *stack;
public:
    // constructors
    my_thread() noexcept = default;

    my_thread(std::function<int()> &&fn) {
        stack = new char[STACK_SIZE];
        CHECK(pid = clone(childFunc, stack + STACK_SIZE, SIGCHLD, &fn));
    }

    // destructor
    ~my_thread() {
        if (joinable())
            kill(pid, SIGTERM);
        delete[] stack;
    }

    // operator =
    my_thread& operator=(my_thread&& thr) noexcept {
        if (joinable())
            kill(pid, SIGTERM);
        swap(thr);
        return *this;
    }

    // joinable
    bool joinable() const noexcept {
        return !(pid == kill(pid, 0));
    }

    // join
    void join() {
        if (joinable()) {
            int wstatus;
            CHECK(waitpid(pid, &wstatus, 0));
        }
    }

    // get id
    int get_id() const noexcept {
        return pid;
    }

    // swap
    void swap(my_thread& thr) noexcept {
        std::swap(this->pid, thr.pid);
        std::swap(this->stack, thr.stack);
    }
};