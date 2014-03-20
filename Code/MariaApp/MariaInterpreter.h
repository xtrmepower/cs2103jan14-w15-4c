#pragma once

#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <functional>
#include <regex>
#include <exception>
#include "MariaInputObject.h"
#include "MariaStateManager.h"
using namespace std;

/**
 *
 * Features not working:
 *	- getEditType()
 *	- getConflictID()
 *
 *
 *
 */

class MariaInterpreter{
public:
	MariaInterpreter(map<string, MariaInputObject::CommandType>* inputCommandList = NULL);
	~MariaInterpreter(void);

	/// Takes in the user's input, works its magic on it
	/// and churns out a MariaInputObject that contains everything
	/// you need to know about the original input!
	///
	/// @param	inputString		This be the user's input.
	///
	/// @return	This be the magical object that holds the answer to everything...
	MariaInputObject* parseInput(string inputString, MariaStateManager::STATE_TYPE currentState = MariaStateManager::STATE_TYPE::HOME);

#ifdef _DEBUG
public:
#else
private:
#endif
	map<string, MariaInputObject::CommandType>* commandKeywordList;

	MariaInputObject::EditType getEditType(vector<string> &tokenizedInput);

	/// Gets the task's title from the user's input.
	/// The title would also be removed from the inputString.
	///
	/// @param	inputString	User's input.
	///
	/// @return	The task's title would be returned on valid input. Blank otherwise.
	//string getTitle(string &inputString);
	string getTitle(vector<string> &tokenizedInput);

	string getEditField(vector<string> &tokenizedInput);

	vector<MariaTime*> parseDateTimeString(vector<string> &tokenizedInput);
	MariaTime* parseDateTime(vector<string> dateTimeList, bool hasDate, bool hasTime);
	void parseDate(string text, int &year, int &month, int &day);
	void parseTime(string text, int &hour, int &min);

	/// Replaces oldText in the inputString with newText.
	///
	/// @param inputString			String to be modified.
	/// @param oldText				Text to be replaced.
	/// @param newText				Text to replace oldText
	/// @param firstInstanceOnly	Whether only the first instance of oldText will be replaced. Default is true.
	///
	/// @return						String with oldText replaced with newText.
	string replaceText(string inputString, string oldText, string newText, bool firstInstanceOnly = true);

	vector<string> tokenizeString(string inputString, char delimiter = ' ');

	string stitchString(vector<string> token, int startPos, int endPos, string delimiter = " ");

	void removeTokens(vector<string> &input, int startPos, int endPos);

	string lowercaseString(string text);
	bool isInteger(string text);
	bool isDate(string text);
	bool isTime(string text);

	bool isStringToday(string text);
	bool isStringTomorrow(string text);
	bool isStringDayFormat(string text);
	bool isStringDateFormat(string text);
	int getDayOfWeek(string text);
	bool isStringMatch(string text, string expr, bool ignoreCasing = true);
	bool doesStringContain(string text, string expr, bool ignoreCasing = true);

	void getDate(string input, int &day, int &month, int &year);
	void getTime(string input, int &hour, int &min);

	// To trim whitespace.
	inline string trimWhiteSpaceLeft(string text);
	inline string trimWhiteSpaceRight(string text);
	inline string trimWhiteSpace(string text);
};