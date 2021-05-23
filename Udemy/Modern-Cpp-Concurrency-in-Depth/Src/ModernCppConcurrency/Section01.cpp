#include <thread>
#include <iostream>
#include <chrono>

#include "common_objs.h"
#include "Section01.h"

///////////////////////////////////////////////////////////////////////////////
// SECTION 01 - EXERCISES
///////////////////////////////////////////////////////////////////////////////

//
// Section 01.04
//

void foo();
void run_01_04();
class callable_class;

void foo()
{
	printf("[%d] Hello from foo trhread\n", std::this_thread::get_id());
}

class callable_class
{
public:

	void operator()()
	{
		printf("[%d] Hello callable_class from operator()\n", std::this_thread::get_id());
	}
private:
};

void run_01_04()
{
	printf("[%d] Hello from main\n", std::this_thread::get_id());

	// function
	std::thread thread1(foo);
	// objects
	callable_class obj;
	std::thread thread2(obj);
	// lambda functions
	std::thread thread3([]
	{
		printf("[%d] Hellow form lambda\n", std::this_thread::get_id());
	});

	thread1.join();
	thread2.join();
	thread3.join();

	printf("[%d] Back from main\n", std::this_thread::get_id());
}

//
// Section 01.05
//

void test_01_05();
void functionA();
void functionB();

void test_01_05()
{
	printf("[%d] Hello from test_01_05()\n", std::this_thread::get_id());
}

void functionA()
{
	printf("[%d] Hello from functionA()\n", std::this_thread::get_id());
	std::thread threadC(test_01_05);
	threadC.join();
}

void functionB()
{
	printf("[%d] hello from functionB()\n", std::this_thread::get_id());
}

//
// Section 01.06 Joinability of threads
//

void test_01_06();
void run_01_06();

void test_01_06()
{
	printf("Actual thread: Hello from test01_06\n");
}

void run_01_06()
{
	std::thread thread01(test_01_06);

	if (thread01.joinable())
	{
		printf("Thread01 is joinable before join\n");
	}
	else
	{
		printf("Thread01 is not joinable before join\n");
	}

	thread01.join();

	if (thread01.joinable())
	{
		printf("Thread01 is joinable after join\n");
	}
	else
	{
		printf("Thread01 is not joinable after join\n");
	}

}

//
// Section 01.07
//

void run_01_07();
void foo_01_07();
void bar_01_07();


void run_01_07()
{
	std::thread foo_thread(foo_01_07);
	std::thread bar_thread(bar_01_07);

	bar_thread.detach();
	printf("This is after bar_01_07 thread detach\n");

	foo_thread.join();
	printf("This is after foo_01_07 thread join\n");
}

void foo_01_07()
{
	printf("Hello from foo_01_07 enter\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	printf("Hello from foo_01_07 exit\n");
}

void bar_01_07()
{
	printf("Hello from bar_01_07 enter\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	printf("Hello from bar_01_07 exit\n");
}

//
// Section 01.08 How to handle join, in exceptions scenarios
//

void run_01_08();
void foo_01_08();
void other_operations_01_08();

void run_01_08()
{
	std::thread foo_thread(foo_01_08);
	thread_guard tg(foo_thread);
	try
	{
		other_operations_01_08();

	}
	catch (...)
	{
	}


}

void foo_01_08()
{

}

void other_operations_01_08()
{
	std::cout << "This is other oprations" << std::endl;
	throw std::runtime_error("this is a runtime error");
}


//
// Section 01.10 how to pass parameters to a thread
//

void run_01_10();
void func1_01_10(int x, int y);
void func2_value_01_10(int x);
void func2_ref_01_10(int& x);


void run_01_10()
{
	printf("-- test01\n");
	int p = 9;
	int q = 8;
	std::thread thread_01(func1_01_10, p, q);
	thread_01.join();

	printf("-- test02 value\n");

	int x = 9;
	printf("(main thread) x:%d\n", x);
	std::thread thread_02(func2_value_01_10, x);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	x = 15;
	printf("(main thread) x:%d\n", x);
	//if(thread_02.joinable()) 
		thread_02.join();

	printf("-- test02 ref\n");
	x = 9;
	printf("(main thread) x:%d\n", x);
	std::thread thread_03(func2_ref_01_10, std::ref(x));
	std::this_thread::sleep_for(std::chrono::seconds(5));
	x = 15;
	printf("(main thread) x:%d\n", x);
	if (thread_03.joinable())  
		thread_03.join();


}

void func1_01_10(int x, int y)
{
	printf("x + y = %d \n", x+y);
}

void func2_value_01_10(int x)
{
	int i = 0;
	while (true)
	{
		printf("Thread func2_value_01_10 x:%d\n", x);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::this_thread::sleep_for(std::chrono::microseconds(1000));
		i++;
		if (i == 15)
		{
			break;
		}
	}
}

void func2_ref_01_10(int& x)
{
	int i = 0;
	while (true)
	{
		printf("Thread func2_ref_01_10 x:%d\n", x);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		i++;
		if (i == 15)
		{
			break;
		}
	}
}



///////////////////////////////////////////////////////////////////////////////
// SECTION 01 - MAIN CLASS
///////////////////////////////////////////////////////////////////////////////

void Section01::printHeader(const char* title)
{
	printf("###################################################################\n");
	printf("# %s\n", title);
	printf("###################################################################\n");
	printf("\n");
}

void Section01::s1_04_launch_a_thread()
{
	Section01::printHeader("s1_04_launch_a_thread()");
	run_01_04();
}

// - I want you to launch 2 threads fom the main chread call threadA and threadB
// - Thread A Should execute a function called functionA and the ThreadB should 
//   execute a function called FunctionB
// - From function A you have to launch another thread call threadC which will tun 
//   the function call test. This test function should printout hello from test
// - Then I want you to order the thread in the order htey are going to finish execution. 
//   First thread in the order should be the first one to finish, Last thread in the 
//   order should be the last one to finish. Consider the main thread as well
void Section01::s1_05_programming_exercise01()
{
	Section01::printHeader("s1_05_programming_exercise()");
	printf("[%d] s1_05_programming_exercise\n", std::this_thread::get_id());
	std::thread threadA(functionA);
	std::thread threadB(functionB);
	threadA.join();
	threadB.join();
}

void Section01::s1_06_joinable_threads()
{
	run_01_06();
}

void Section01::s1_07_join_and_detach_functions()
{
	run_01_07();
}

void Section01::s1_08_handle_join_in_exceptions()
{
	run_01_08();
}

void Section01::s1_10_how_to_pass_parameters_to_a_thread()
{
	run_01_10();
}


