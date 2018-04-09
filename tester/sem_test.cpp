//
// Created by leo on 18-4-7.
//

#include "Semaphore.h"
#include <thread>
#include <Traits.h>
#include <cmath>
#include <vector>
#include <set>
#include <iostream>

typedef unsigned ull;

using namespace CThread;

const ull limit=1000000;
std::set<ull> map;
ull cur=2,fin=2;

int r_count=0;
void child(Semaphore& mtx_cur,Semaphore& mtx_r_count,Semaphore& mtx_write,Semaphore& ln_writable){
    for (auto lc=sync({mtx_cur},[&](){return ++cur;});lc<limit;lc=sync({mtx_cur},[&](){return ++cur;})) {
        const auto to=sqrt(lc);

        sync({mtx_write},[](){});
        if (sync({mtx_r_count},[&](){ return r_count++==0; }))
            ln_writable.wait();

        bool flag=true;
        for (auto &t:map) {
            if (!flag || t>to) break;
            else flag = lc % t != 0;
        }

        sync({mtx_r_count},[&](){if (--r_count==0) ln_writable.signal();});

        if (flag) sync({mtx_write,ln_writable},[&](){
            map.insert(lc);
            if (fin<lc) fin=lc;
        });
    }
}

int main() {
    const int max_thread=5;
    Semaphore mtx_cur = 1, mtx_r_count = 1, mtx_write = 1, ln_writable = 1;
    std::vector<std::thread> ths;
    map.insert(2);
    while (cur<limit && ths.size()<max_thread) {
        for (int i=0;i<fin*(fin-1)-ths.size() && ths.size()<max_thread;++i) {
            ths.emplace_back(child,
                             std::ref(mtx_cur),
                             std::ref(mtx_r_count),
                             std::ref(mtx_write),
                             std::ref(ln_writable));
        }
    }

    for (auto &t:ths) t.join();
    for (auto &x:map) std::cout<<x<<std::endl;
    std::cout<<map.size()<<std::endl;
    return 0;
};