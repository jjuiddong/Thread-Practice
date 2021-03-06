
#include "stdafx.h"
#include <iostream>
#include "tpsemaphore.h"

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
	cTPSemaphore tpSema;

	tpSema.Init();
	tpSema.PushTask(new cTaskPrint(0));
	tpSema.PushTask(new cTaskPrint(1));
	tpSema.PushTask(new cTaskPrint(2));
	tpSema.PushTask(new cTaskPrint(3));
	tpSema.PushTask(new cTaskPrint(4));
	tpSema.PushTask(new cTaskPrint(5));
	//tpSema.Wait();

	cout << "end main" << endl;

}
