#include <mutex>
#include <condition_variable>

#pragma once

namespace pr {

class Barrier {
private:
    mutable std::mutex m;
    std::condition_variable cond;
    int cpt;
    const int goal;
public:
    Barrier(const int goal) : goal(goal) {}

    void done(){
        std::unique_lock<std::mutex> l(m);
        cpt++;
        if(cpt==goal){
            cond.notify_all();
        }
    }

    void waitFor(){
        std::unique_lock<std::mutex> l(m);
        while(cpt != goal) {
            cond.wait(l);
        }
    }
};

}