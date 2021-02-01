#include <iostream>
#include <thread>

void foo()
{
	std::cout << "Hello from thread" << std::endl;
}

int main()
{
	std::thread thread(foo);
	std::cout << "Hello from main" << std::endl;
	thread.join(); // Waits for the thread to finish
}