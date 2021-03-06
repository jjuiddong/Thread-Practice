
#include "stdafx.h"
#include <iostream>
#include "wqsemaphore.h"

using namespace std;


class cTaskPrint : public cTask
{
public:
	cTaskPrint(const int id) : cTask(id) {}
	
	virtual bool Run() {
		cout << "Task" << m_id << " Run Start" << endl;
		Sleep(1000);
		cout << "Task" << m_id << " Run End" << endl;
		return true;
	}

};


int main()
{
	cWQSemaphore wqSema;

	wqSema.PushTask(new cTaskPrint(0));
	wqSema.PushTask(new cTaskPrint(1));
	wqSema.PushTask(new cTaskPrint(2));
	wqSema.PushTask(new cTaskPrint(3));
	wqSema.Wait();

	cout << "end main" << endl;
	return 0;
}
