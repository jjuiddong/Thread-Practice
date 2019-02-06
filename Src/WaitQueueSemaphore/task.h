//
// 2019-02-06, jjuiddong
// task
//
#pragma once


class cTask
{
public:
	cTask(const int id) : m_id(id) {
	}
	virtual ~cTask() {
	}

	virtual bool Run() {

		return true;
	}

public:
	int m_id;
};

