#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <atomic>
#include <condition_variable>
#include "Traits.h"

namespace CThread {
    class Semaphore {
        volatile std::atomic_long res;
        std::condition_variable cv;
        std::mutex mtx;
    public:
        Semaphore(long res = 1l) : res(res) {}
        void signal();
        void wait();
    };

    template<class Fn, typename R=typename __CThread::LambdaTraits<Fn>::ReturnType>
    R sync(std::initializer_list<std::reference_wrapper<Semaphore>> const &lck,
           Fn const &blk) {
        if constexpr (std::is_same<R, void>::value) {
            for (auto &l:lck) l.get().wait();
            blk();
            for (auto &l:lck) l.get().signal();
        } else {
            for (auto &l:lck) l.get().wait();
            R ret = blk();
            for (auto &l:lck) l.get().signal();
            return ret;
        }
    }
};

#endif