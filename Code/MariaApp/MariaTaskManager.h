#pragma once

#include <vector>
#include "MariaTask.h"
using namespace std;

class MariaTaskManager {
public:
	MariaTaskManager(vector<MariaTask*> *inputTaskList = NULL);
	~MariaTaskManager(void);

	bool addTask(MariaTask);
	bool addTask(string name, MariaTime start = NULL, MariaTime end = NULL);
	vector<MariaTask*> findTask(string searchString);
	vector<MariaTask*> findTask(MariaTime start, MariaTime end);

	bool archiveTask(MariaTask);
	bool deleteArchive();

private:
#ifdef _DEBUG
public:
#endif
	vector<MariaTask*> *taskList;
};
