#pragma once

#include <string>
#include <map>
#include <sstream>
#include <functional>
#include <regex>
#include "MariaInputObject.h"
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
	MariaInputObject* parseInput(string inputString);

#ifdef _DEBUG
public:
#else
private:
#endif
	map<string, MariaInputObject::CommandType>* commandKeywordList;

	/// Gets a CommandType flag depending on the user's input.
	/// The command keyword would also be removed from the inputString.
	///
	/// @param	inputString	User's input.
	///
	/// @return	The command's flag will be returned on valid input. Invalid flag otherwise.
	MariaInputObject::CommandType getCommandType(string &inputString);

	MariaInputObject::AddType getAddType(string &inputString);

	/// Gets the task's title from the user's input.
	/// The title would also be removed from the inputString.
	///
	/// @param	inputString	User's input.
	///
	/// @return	The task's title would be returned on valid input. Blank otherwise.
	string getTitle(string &inputString);

	string getEditField(string &inputString);

	MariaTime* getStartTime(string &inputString);
	MariaTime* getEndTime(string &inputString);

	/// Checks the validity of the user's input depending on
	/// the presence of certain keywords, number of words and so on.
	///
	/// @param	User's input.
	///
	/// @return	True if valid. False otherwise.
	bool checkInputValidity(string inputString);

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

	string lowercaseString(string text);

	// To trim whitespace.
	inline string trimWhiteSpaceLeft(string text);
	inline string trimWhiteSpaceRight(string text);
	inline string trimWhiteSpace(string text);
};