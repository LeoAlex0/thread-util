//
// Created by leo on 18-4-9.
//

#include "Semaphore.h"

using namespace std;

namespace CThread{

    void Semaphore::signal() {
        std::unique_lock<std::mutex> lck(this->mtx);
        this->res++;
        if (this->res <= 0) cv.notify_one();
    }

    void Semaphore::wait() {
        std::unique_lock<std::mutex> lck_cv(this->mtx);
        this->res--;
        if (this->res < 0) cv.wait(lck_cv);
    }

}