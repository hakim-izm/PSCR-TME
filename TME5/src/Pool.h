#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize){
		queue = queue(qsize);
	}
	void start (int nbthread) {
		// Instanciation des nbthread threads
		for(int i=0; i<nbthread; ++i){
			threads.emplace_back([&](){
				while(true){
					Job *j = queue.pop();
					j->run();
					delete j;
				}
			});
		}
	}
	void submit (Job * job) {
		queue.push(job);
	}
	
	void stop() {
		queue.isBlocking(false);
		for(auto &t : threads){
			t.join();
		}
		threads.clear();
	}
	~Pool() ;
};

}
