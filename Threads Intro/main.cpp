#include <iostream>
#include <thread>
#include <vector>

class Loop
{
public:
	void Run()
	{
		while(!hasToStop)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		std::cout << "Finishing the loop" << std::endl;
	}

	bool hasToStop{false};
};

int main()
{
	srand(time(NULL));
	Loop loop;
	std::thread t1(&Loop::Run, &loop);

	std::thread t2([&loop]()   // this is a lambda... an anonymous function
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
		loop.hasToStop = true;
	});

	t2.join();
	t1.join();
	return 0;
}