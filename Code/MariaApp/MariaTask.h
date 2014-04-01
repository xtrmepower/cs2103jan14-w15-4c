#pragma once

#include <functional>
#include <string>
#include "MariaTime.h"
#include "MariaUndoObserver.h"

using namespace std;

class MariaTask : public MariaTaskInterface {
public:
	typedef enum {
		FLOATING, 
		DEADLINE, 
		TIMED
	} TaskType;
	
	MariaTask(string title = "", MariaTime *start = NULL, MariaTime* end = NULL);
	MariaTask(string title, string description, MariaTime* start = NULL, MariaTime* end = NULL);
	~MariaTask();
	
	
	TaskType getType();
	string getTitle();
	string getDescription();
	string getTimeFromNow();
	MariaTime* getStart();
	MariaTime* getEnd();
	MariaTime* getCreated();
	double getDuration();
	MariaTask* getClone();
	
	void setTitle(string);
	void setDescription(string);
	void setStart(MariaTime*);
	void setEnd(MariaTime*);
	void setCreated(MariaTime*);

	void refreshTaskType();

	bool operator<(MariaTask rhs);

	static void initObserver(MariaUndoObserver*);
	

private:
	TaskType	type;
	string		title;
	string		description;
	MariaTime*	start;
	MariaTime*	end;
	MariaTime*	created;

	static MariaUndoObserver *observer;
};
