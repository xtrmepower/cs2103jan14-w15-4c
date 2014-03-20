#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "MariaTask.h"
using namespace std;

class MariaTaskManager {
public:
	MariaTaskManager(vector<MariaTask*> *inputTaskList = NULL);
	~MariaTaskManager(void);

	MariaTask* addTask(string name, MariaTime* start = NULL, MariaTime* end = NULL);
	vector<MariaTask*> findTask(string searchString);
	vector<MariaTask*> findTask(MariaTime* start, MariaTime* end, MariaTask::TaskType type);
	vector<MariaTask*> getAllTasks(MariaTask::TaskType);
	vector<MariaTask*> getAllTasks();

	bool archiveTask(MariaTask*); //Note: For now, this deletes tasks!
	bool deleteArchive();

private:
#ifdef _DEBUG
public:
#endif
	vector<MariaTask*> *taskList;
	string lowercaseString(string text);
	void sortTasks();
	static bool compareTasks(MariaTask* d1, MariaTask* d2);
};
