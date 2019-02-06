
#include "stdafx.h"
#include "wqsemaphore.h"


cWQSemaphore::cWQSemaphore()
	: m_isThreadLoop(false)
{
}

cWQSemaphore::~cWQSemaphore()
{
	Clear();
}


bool cWQSemaphore::PushTask(cTask *task)
{
	m_cs.Lock();
	m_tasks.push(task);
	m_cs.Unlock();
	m_sema.Signal();

	// thread start
	if (!m_thread.joinable())
	{
		m_isThreadLoop = true;
		m_thread = std::thread(cWQSemaphore::ThreadFunction, this);
	}

	return true;
}


cTask* cWQSemaphore::PopTask()
{
	m_sema.Wait();
	m_cs.Lock();
	cTask *task = m_tasks.front();
	m_tasks.pop();
	m_cs.Unlock();
	return task;
}


// wait all task finish
// no optimize
void cWQSemaphore::Wait()
{
	while (!m_tasks.empty())
		Sleep(10);
}


// thread terminate
void cWQSemaphore::Terminate()
{
	if (m_thread.joinable())
	{
		PushTask(NULL); // finish thread

		m_isThreadLoop = true;
		if (m_thread.joinable())
			m_thread.join();
	}
}


void cWQSemaphore::Clear()
{
	// wait all task finish
	if (m_thread.joinable())
	{
		PushTask(NULL); // finish thread
		if (m_thread.joinable())
			m_thread.join();
	}

	m_sema.Clear();

	AutoCSLock cs(m_cs);
	while (!m_tasks.empty())
	{
		delete m_tasks.front();
		m_tasks.pop();
	}
}


int cWQSemaphore::ThreadFunction(cWQSemaphore *wqSemaphore)
{
	while (wqSemaphore->m_isThreadLoop)
	{
		cTask *task = wqSemaphore->PopTask();
		if (!task) // end thread command
			break;

		task->Run();
		delete task;
	}
	return 1;
}
