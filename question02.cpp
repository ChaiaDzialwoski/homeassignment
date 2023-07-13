//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex> 

constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t gSum = 0;
std::mutex gSumMutex;

void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	gSumMutex.lock();
	for (size_t i = 0; i < ITERATIONS; i++) {
		gSum += (arg + i);
	}
	gSumMutex.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	gSumMutex.lock();
	for (size_t i = 0; i < ITERATIONS; i++) {
		gSum += (arg * i);
	}
	gSumMutex.unlock();
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	//operation1(OP1_PARAM);
	//operation2(OP2_PARAM);
	std::thread t1(operation1, OP1_PARAM);
	std::thread t2(operation2, OP2_PARAM);
	t1.join();
	t2.join();
	auto end = std::chrono::steady_clock::now();
	size_t sum = gSum;
	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << sum << ", " << (sum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}

//The main changes I made to the code to shift from serial execution to parallel execution were :
//
//I added the std::mutex class to the code.This class provides a lock that can be held by only one thread at a time.This prevents two threads from accessing the gSum variable at the same time, which can lead to race conditions.
//I added the lock() and unlock() calls to the operation1() and operation2() functions.These calls ensure that the gSum variable is only accessed by one thread at a time.
//I used the join() function to wait for the threads to finish executing before the main thread continues.This ensures that the main thread does not continue until the final value of the gSum variable is known.
//These changes are important for ensuring that the code is thread - safe and that the results are correct.
//
//When shifting from serial execution to parallel execution, I had to deal with the following new aspects :
//
//	Race conditions : Race conditions are a situation where two or more threads are accessing the same data at the same time and the results of the access are not deterministic.I had to be careful to avoid race conditions by using the std::mutex class to synchronize access to the gSum variable.
//	Thread safety : Thread safety is the property of a program that ensures that it produces the same results regardless of the number of threads that are executing it.I had to make sure that my code was thread - safe by using the std::mutex class to synchronize access to shared data.
//	Performance : Parallel execution can improve the performance of a program by allowing multiple threads to execute different parts of the program at the same time.However, it is important to make sure that the program is thread - safe, otherwise the performance improvements can be negated by race conditions.