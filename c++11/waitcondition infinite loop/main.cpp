#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>


using namespace std;


class CPU
{
public:
	
	void process()
	{
		while(1)
		{
			{
				unique_lock<mutex> lock(mu);
				while(items.size() == 0)
				{
					cout << "sleep" << endl;
					conditon.wait(lock);
				}
				lock.unlock();
			}

			vector<string>::iterator it;
			for(it = items.begin(); it < items.end(); it++)
			{
				cout << "elemento do vector " << *it << endl;
			}
			items.clear();
		}
	}
	
	void wake()
	{
	        cout << "wake = " << items.size() << endl;
		conditon.notify_one();
	}
	
	void add(const string& item)
	{
		unique_lock<mutex> lock(mu);
		cout << "add " << item << endl;
		items.push_back(item);
		lock.unlock();
	}
private:
	vector < string > items;
	condition_variable conditon;
	mutex mu;
};


//worker thread
void worker_thread(CPU& cpu )
{
	for(int i = 0 ; i < 10; i ++)
	{
		cpu.add(std::to_string(i));
      	}	
}


int main(int argc, char *argv[])
{

	CPU cpu;
	std::thread worker(worker_thread, std::ref(cpu));
	worker.join();
	cpu.process();
	cpu.wake();

	return 0;
}
