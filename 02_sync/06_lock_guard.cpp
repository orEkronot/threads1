#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

int shared_resource = 10;
std::mutex mtx;

void test_resource()
{
	try
	{

		for (int i = 0; i < 5; i++)
		{
			std::lock_guard<std::mutex> lck(mtx);

			int res = shared_resource;
			if (res != shared_resource)
			{
				std::cout << "ALARM" << std::endl;
			}
			else
			{
				std::cout << "SAME" << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}//lock released
	}
	catch (std::exception e)
	{
		// exception occured
		// no deadlock!
	}
}

void change_resource()
{
	try
	{
		for (int i = 0; i < 5; i++)
		{
			std::lock_guard<std::mutex> lck(mtx);
			shared_resource++;
			std::cout << "change_resource: Changed resource" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}//lock released
	}
	catch (std::exception e)
	{
		// exception occured
		// no deadlock!

	}
}
int main()
{
	std::thread t1(test_resource);
	std::thread t2(change_resource);

	t1.join();
	t2.join();
	system("pause");
	return 0;
}