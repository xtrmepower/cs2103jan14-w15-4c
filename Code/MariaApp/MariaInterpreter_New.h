#pragma once

#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <functional>
#include <regex>
#include <exception>
#include <cassert>
#include "MariaInputObject.h"
#include "MariaUIStateType.h"
using namespace std;

// Safely deletes a pointer.
#define SAFE_DELETE(ptr)	\
	if (ptr != NULL)		\
	{						\
		delete ptr;			\
		ptr = NULL;			\
	}

using namespace std;

class MariaInterpreter_New {
public:
	// Warning Messages
	static const string MESSAGE_INVALID_COMMAND;
	static const string MESSAGE_NO_ACTIVITY_TITLE;
	static const string MESSAGE_NO_INPUT;


	MariaInterpreter_New(map<string, MariaInputObject::COMMAND_TYPE>* inputCommandList = NULL);
	~MariaInterpreter_New(void);

	MariaInputObject* parseInput(string input, STATE_TYPE currentState = STATE_TYPE::HOME);

private:
	map<string, MariaInputObject::COMMAND_TYPE>* commandKeywordList;

	void parseAdd(string input, MariaInputObject* inputObject);
	void parseShow(string input, MariaInputObject* inputObject);
	void parseDelete(string input, MariaInputObject* inputObject);

	bool hasDate(string text);
	bool hasDateTime(string text);
	bool hasDateFormat(string text);
	bool hasDayOfWeek(string text);
	bool hasToday(string text);
	bool hasTomorrow(string text);

	bool isStringEqual(string text, string expr, bool ignoreCasing = true);
	string lowercaseString(string text);
	void removeTokens(vector<string> &input, int startPos, int endPos);
	string stitchString(vector<string> token, int startPos, int endPos, string delimiter = " ");
	vector<string> tokenizeString(string inputString, char delimiter = ' ');
	string trimWhiteSpaceLeft(string text);
	string trimWhiteSpaceRight(string text);
	string trimWhiteSpace(string text);
};