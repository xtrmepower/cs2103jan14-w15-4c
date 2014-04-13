//@author A0111821X
#include "MariaInterpreter.h"

const string MariaInterpreter::MESSAGE_BLANK = "";
const string MariaInterpreter::MESSAGE_INVALID_COMMAND = "Invalid command detected.";
const string MariaInterpreter::MESSAGE_INVALID_COMMAND_FORMAT = "Invalid command format detected.";
const string MariaInterpreter::MESSAGE_INVALID_COMMAND_LOCATION = "You can't enter that command here.";
const string MariaInterpreter::MESSAGE_INVALID_OPTION = "Invalid option.";
const string MariaInterpreter::MESSAGE_INVALID_DATE_TIME = "Invalid date/time detected.";
const string MariaInterpreter::MESSAGE_NO_ACTIVITY_TITLE = "No activity title detected.";
const string MariaInterpreter::MESSAGE_NO_ACTIVITY_TITLE_EDIT = "No new activity title detected.";
const string MariaInterpreter::MESSAGE_NO_DESCRIPTION = "No description detected.";
const string MariaInterpreter::MESSAGE_NO_INPUT = "No input detected.";
const string MariaInterpreter::MESSAGE_NO_OPTION = "No option selected.";

const string MariaInterpreter::EXPRESSION_DATE_FORMAT = "(^(0?[1-9]|[12][0-9]|3[01])[-/](0?[1-9]|1[012])[-/](19|20)?[0-9][0-9]$)";
const string MariaInterpreter::EXPRESSION_DAYS_OF_WEEK = "mon(day)?|tues?(day)?|wed(nesday)?|thur?s?(day)?|fri(day)?|sat(urday)?|(sun)?day";
const string MariaInterpreter::EXPRESSION_DAYS_OF_WEEK_INDIVIDUAL[] = { "mon(day)?", "tues?(day)?", "wed(nesday)?", "thur?s?(day)?", "fri(day)?", "sat(urday)?", "(sun)?day" };
const string MariaInterpreter::EXPRESSION_MONTHS_OF_YEAR = "jan(uary)?|feb(ruary)?|mar(ch)?|apr(il)?|may|june?|july?|aug(ust)?|sept?(ember)?|oct(tober)?|nov(ember)?|dec(ember)?";
const string MariaInterpreter::EXPRESSION_MONTHS_OF_YEAR_INDIVIDUAL[] = { "jan(uary)?", "feb(ruary)?", "mar(ch)?", "apr(il)?", "may", "june?", "july?", "aug(ust)?", "sept?(ember)?", "oct(tober)?", "nov(ember)?", "dec(ember)?" };
const string MariaInterpreter::EXPRESSION_TODAY = "today";
const string MariaInterpreter::EXPRESSION_TOMORROW = "tomorrow";
const string MariaInterpreter::EXPRESSION_TIME_FORMAT = "([01]?[0-9]|2[0-3])([.:][0-5][0-9])?(\\s*[AaPp][Mm])?";

const string MariaInterpreter::MODIFIER_ALL_TASKS = "all";

const string MariaInterpreter::DELIMITER_ADD_DEADLINE_TASK = " by ";
const string MariaInterpreter::DELIMITER_ADD_TIMED_TASK_START = " from ";
const string MariaInterpreter::DELIMITER_ADD_TIMED_TASK_END = " to ";
const string MariaInterpreter::DELIMITER_EDIT_TITLE = " change title ";
const string MariaInterpreter::DELIMITER_EDIT_START_TIME = " change start ";
const string MariaInterpreter::DELIMITER_EDIT_END_TIME = " change end ";
const string MariaInterpreter::DELIMITER_EDIT_DESCRIPTION = " change description ";
const string MariaInterpreter::DELIMITER_SHOW_DATE_RANGE_START = "from ";
const string MariaInterpreter::DELIMITER_SHOW_DATE_RANGE_END = " to ";

MariaInterpreter::MariaInterpreter(map<string, MariaInputObject::COMMAND_TYPE>* inputCommandList) {
	commandKeywordList = inputCommandList;
	if (commandKeywordList == NULL) {
		commandKeywordList = new map<string, MariaInputObject::COMMAND_TYPE>();
	}

	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("add", MariaInputObject::COMMAND_TYPE::ADD));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("create", MariaInputObject::COMMAND_TYPE::ADD));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("edit", MariaInputObject::COMMAND_TYPE::EDIT));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("update", MariaInputObject::COMMAND_TYPE::EDIT));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("show", MariaInputObject::COMMAND_TYPE::SHOW));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("view", MariaInputObject::COMMAND_TYPE::SHOW));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("search", MariaInputObject::COMMAND_TYPE::SEARCH));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("find", MariaInputObject::COMMAND_TYPE::SEARCH));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("complete", MariaInputObject::COMMAND_TYPE::MARK_DONE));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("done", MariaInputObject::COMMAND_TYPE::MARK_DONE));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("incomplete", MariaInputObject::COMMAND_TYPE::MARK_UNDONE));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("uncomplete", MariaInputObject::COMMAND_TYPE::MARK_UNDONE));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("undone", MariaInputObject::COMMAND_TYPE::MARK_UNDONE));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("delete", MariaInputObject::COMMAND_TYPE::DELETE_TASK));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("remove", MariaInputObject::COMMAND_TYPE::DELETE_TASK));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("clear", MariaInputObject::COMMAND_TYPE::DELETE_ALL));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("undo", MariaInputObject::COMMAND_TYPE::UNDO));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("back", MariaInputObject::COMMAND_TYPE::GO_HOME));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("home", MariaInputObject::COMMAND_TYPE::GO_HOME));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("help", MariaInputObject::COMMAND_TYPE::GO_HELP));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("credits", MariaInputObject::COMMAND_TYPE::GO_CREDITS));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("credit", MariaInputObject::COMMAND_TYPE::GO_CREDITS));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("up", MariaInputObject::COMMAND_TYPE::PAGE_UP));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("down", MariaInputObject::COMMAND_TYPE::PAGE_DOWN));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("left", MariaInputObject::COMMAND_TYPE::PAGE_LEFT));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("right", MariaInputObject::COMMAND_TYPE::PAGE_RIGHT));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("exit", MariaInputObject::COMMAND_TYPE::EXIT));
	commandKeywordList->insert(pair<string, MariaInputObject::COMMAND_TYPE>("quit", MariaInputObject::COMMAND_TYPE::EXIT));
}

MariaInterpreter::~MariaInterpreter(void) {
	commandKeywordList->clear();
	SAFE_DELETE(commandKeywordList);
}

bool MariaInterpreter::checkValidCommand(string input) {
	if (input.size() == 0) {
		return false;
	}

	vector<string> tokenizedInput = tokenizeString(input);
	map<string, MariaInputObject::COMMAND_TYPE>::iterator commandKeyword = commandKeywordList->find(lowercaseString(tokenizedInput[0]));

	if (commandKeyword == commandKeywordList->end()) {
		return false;
	}

	return true;
}

MariaInputObject* MariaInterpreter::parseInput(string input, STATE_TYPE currentState) {
	MariaInputObject* toReturn = NULL;

	input = trimWhiteSpace(input);

	if (input.size() == 0) {
		throw exception(MESSAGE_NO_INPUT.c_str());
	}

	toReturn = new MariaInputObject();
	toReturn->setOriginalInput(input);

	// First I want to remove the first word to see if it is a valid command keyword.
	vector<string> tokenizedInput = tokenizeString(input);
	map<string, MariaInputObject::COMMAND_TYPE>::iterator commandKeyword;
	commandKeyword = commandKeywordList->find(lowercaseString(tokenizedInput[0]));

	if (commandKeyword == commandKeywordList->end()) {
		SAFE_DELETE(toReturn);
		throw exception(MESSAGE_INVALID_COMMAND.c_str());
	}

	// Now remove that command keyword with the trailing space.
	toReturn->setCOMMAND_TYPE(commandKeyword->second);
	removeTokens(tokenizedInput, 0, 1);
	input = stitchString(tokenizedInput, 0, tokenizedInput.size());

	switch (commandKeyword->second) {
	case MariaInputObject::COMMAND_TYPE::ADD:
		parseAdd(input, toReturn, currentState);
		break;

	case MariaInputObject::COMMAND_TYPE::EDIT:
		parseEdit(input, toReturn, currentState);
		break;

	case MariaInputObject::COMMAND_TYPE::SHOW:
		parseShow(input, toReturn, currentState);
		break;

	case MariaInputObject::COMMAND_TYPE::SEARCH:
		parseSearch(input, toReturn, currentState);
		break;

	case MariaInputObject::COMMAND_TYPE::DELETE_TASK:
		parseDelete(input, toReturn, currentState);
		break;

	case MariaInputObject::COMMAND_TYPE::MARK_DONE:
		parseMarkDone(input, toReturn, currentState);
		break;

	case MariaInputObject::COMMAND_TYPE::MARK_UNDONE:
		parseMarkUndone(input, toReturn, currentState);
		break;
	}

	return toReturn;
}

void MariaInterpreter::parseAdd(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (input.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_NO_ACTIVITY_TITLE.c_str());
	}

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	int dummyVar = 0;

	if (hasDateTime(input)) {
		// Check if the substring after the last by/from/to contains a valid date/time.
		if (hasDateTime(extractFromBackOfString(input, DELIMITER_ADD_TIMED_TASK_START, dummyVar)) && hasDateTime(extractFromBackOfString(input, DELIMITER_ADD_TIMED_TASK_END, dummyVar))) {
			parseAddTimedTask(input, inputObject);
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::ADD_TIMED);
		} else if (hasDateTime(extractFromBackOfString(input, DELIMITER_ADD_DEADLINE_TASK, dummyVar))) {
			parseAddDeadlineTask(input, inputObject);
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::ADD_DEADLINE);
		} else {
			// Something's wrong with the string but nevermind. We'll just put it as a floating task.
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::ADD_FLOATING);
			inputObject->setTitle(input);
		}
	} else {
		inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::ADD_FLOATING);
		inputObject->setTitle(input);
	}
}

void MariaInterpreter::parseAddDeadlineTask(string input, MariaInputObject* inputObject) {
	assert(inputObject != NULL);
	int delimiterPos = 0;
	string dateTimeString = extractFromBackOfString(input, DELIMITER_ADD_DEADLINE_TASK, delimiterPos);

	input = input.substr(0, delimiterPos);
	inputObject->setTitle(input);

	if (dateTimeString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
	}

	dateTimeString = trimWhiteSpace(dateTimeString);
	vector<string> tokenizedDateTime = tokenizeString(dateTimeString);
	removeTokens(tokenizedDateTime, 0, 1);

	MariaTime* endTime;

	try {
		endTime = parseDateTimeString(tokenizedDateTime);
	} catch (exception& e) {
		SAFE_DELETE(inputObject);
		throw;
	}

	inputObject->setEndTime(endTime);
}

void MariaInterpreter::parseAddTimedTask(string input, MariaInputObject* inputObject) {
	assert(inputObject != NULL);

	// End time
	int delimiterPos = 0;
	string dateTimeString = extractFromBackOfString(input, DELIMITER_ADD_TIMED_TASK_END, delimiterPos);

	input = input.substr(0, delimiterPos);

	if (dateTimeString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
	}

	dateTimeString = trimWhiteSpace(dateTimeString);
	vector<string> tokenizedDateTime = tokenizeString(dateTimeString);
	removeTokens(tokenizedDateTime, 0, 1);

	MariaTime* endTime;

	try {
		endTime = parseDateTimeString(tokenizedDateTime);
	} catch (exception& e) {
		SAFE_DELETE(inputObject);
		throw;
	}

	inputObject->setEndTime(endTime);

	// Start time
	delimiterPos = 0;
	dateTimeString = extractFromBackOfString(input, DELIMITER_ADD_TIMED_TASK_START, delimiterPos);

	input = input.substr(0, delimiterPos);

	inputObject->setTitle(input);

	if (dateTimeString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
	}

	dateTimeString = trimWhiteSpace(dateTimeString);
	tokenizedDateTime = tokenizeString(dateTimeString);
	removeTokens(tokenizedDateTime, 0, 1);

	MariaTime* startTime;

	try {
		startTime = parseDateTimeString(tokenizedDateTime);
	} catch (exception& e) {
		SAFE_DELETE(inputObject);
		throw;
	}

	inputObject->setStartTime(startTime);

	while (inputObject->getStartTime()->compareTo(*inputObject->getEndTime()) > 0) {
		MariaTime* newEndTime = new MariaTime(inputObject->getEndTime()->getYear(), inputObject->getEndTime()->getMonth(), inputObject->getEndTime()->getDay()+7, inputObject->getEndTime()->getHour(), inputObject->getEndTime()->getMin());

		inputObject->setEndTime(newEndTime);
	}
}

void MariaInterpreter::parseEdit(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (input.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_NO_ACTIVITY_TITLE.c_str());
	}

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW && currentState != STATE_TYPE::CONFLICT) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	vector<string> tokenizedInput = tokenizeString(input);
	// <task title> change title/start/end <editfield>
	// therefore 4 tokens minimum
	if (tokenizedInput.size() < 4) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_FORMAT.c_str());
	}

	int changeTitlePos;
	int changeStartPos;
	int changeEndPos;
	int changeDescPos;
	string editFieldString;
	
	extractFromBackOfString(input, DELIMITER_EDIT_TITLE, changeTitlePos);
	extractFromBackOfString(input, DELIMITER_EDIT_START_TIME, changeStartPos);
	extractFromBackOfString(input, DELIMITER_EDIT_END_TIME, changeEndPos);
	extractFromBackOfString(input, DELIMITER_EDIT_DESCRIPTION, changeDescPos);

	switch (currentState) {
	case STATE_TYPE::CONFLICT:
		if (isInteger(tokenizedInput[0])) {
			inputObject->setOptionID(atoi(tokenizedInput[0].c_str()));
			parseEditType(input, inputObject, changeTitlePos, changeStartPos, changeEndPos, changeDescPos);
		} else {
			throw exception(MESSAGE_INVALID_OPTION.c_str());
		}
		break;

	default:
		parseEditType(input, inputObject, changeTitlePos, changeStartPos, changeEndPos, changeDescPos);
		break;
	}
}

void MariaInterpreter::parseEditType(string input, MariaInputObject* inputObject, int changeTitlePos, int changeStartPos, int changeEndPos, int changeDescPos) {
	int inputSize = input.size();

	if (changeTitlePos != inputSize &&
		changeStartPos == inputSize &&
		changeEndPos == inputSize &&
		changeDescPos == inputSize) {
			parseEditTitle(input, inputObject);
	} else if (changeTitlePos == inputSize &&
		changeStartPos != inputSize &&
		changeEndPos == inputSize &&
		changeDescPos == inputSize) {
			parseEditStartTime(input, inputObject);
	} else if (changeTitlePos == inputSize &&
		changeStartPos == inputSize &&
		changeEndPos != inputSize &&
		changeDescPos == inputSize) {
			parseEditEndTime(input, inputObject);
	} else if (changeTitlePos == inputSize &&
		changeStartPos == inputSize &&
		changeEndPos == inputSize &&
		changeDescPos != inputSize) {
			parseEditDescription(input, inputObject);
	} else {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_FORMAT.c_str());
	}
}

void MariaInterpreter::parseEditTitle(string input, MariaInputObject* inputObject) {
	vector<string> tokenizedInput = tokenizeString(input);
	int changeTitlePos;
	int inputSize = input.size();
	string editFieldString;
	const static int editFieldStringStartPos = 3;

	editFieldString = extractFromBackOfString(input, DELIMITER_EDIT_TITLE, changeTitlePos);
	input = input.substr(0, changeTitlePos);
	inputObject->setTitle(input);
	tokenizedInput = tokenizeString(editFieldString);
	editFieldString = stitchString(tokenizedInput, editFieldStringStartPos, tokenizedInput.size());

	if (editFieldString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_NO_ACTIVITY_TITLE_EDIT.c_str());
	}
	inputObject->setEditField(editFieldString);
	inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::EDIT_TITLE);
}

void MariaInterpreter::parseEditStartTime(string input, MariaInputObject* inputObject) {
	int changeStartPos;
	string editFieldString = extractFromBackOfString(input, DELIMITER_EDIT_START_TIME, changeStartPos);
	input = input.substr(0, changeStartPos);
	inputObject->setTitle(input);

	if (editFieldString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
	}

	editFieldString = trimWhiteSpace(editFieldString);
	vector<string> tokenizedDateTime = tokenizeString(editFieldString);
	removeTokens(tokenizedDateTime, 0, 1);

	MariaTime* editTime;

	try {
		editTime = parseDateTimeString(tokenizedDateTime);
	} catch (exception& e) {
		SAFE_DELETE(inputObject);
		throw;
	}

	inputObject->setEditTime(editTime);
	inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::EDIT_START_TIME);
}

void MariaInterpreter::parseEditEndTime(string input, MariaInputObject* inputObject) {
	int changeEndPos;
	string editFieldString = extractFromBackOfString(input, DELIMITER_EDIT_END_TIME, changeEndPos);
	input = input.substr(0, changeEndPos);
	inputObject->setTitle(input);

	if (editFieldString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
	}

	editFieldString = trimWhiteSpace(editFieldString);
	vector<string> tokenizedDateTime = tokenizeString(editFieldString);
	removeTokens(tokenizedDateTime, 0, 1);

	MariaTime* editTime;

	try {
		editTime = parseDateTimeString(tokenizedDateTime);
	} catch (exception& e) {
		SAFE_DELETE(inputObject);
		throw;
	}

	inputObject->setEditTime(editTime);
	inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::EDIT_END_TIME);
}

void MariaInterpreter::parseEditDescription(string input, MariaInputObject* inputObject) {
	vector<string> tokenizedInput = tokenizeString(input);
	int changeDescPos;
	int inputSize = input.size();
	string editFieldString;

	editFieldString = extractFromBackOfString(input, DELIMITER_EDIT_DESCRIPTION, changeDescPos);
	input = input.substr(0, changeDescPos);
	inputObject->setTitle(input);
	tokenizedInput = tokenizeString(editFieldString);
	editFieldString = stitchString(tokenizedInput, 3, tokenizedInput.size());

	if (editFieldString.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_NO_DESCRIPTION.c_str());
	}
	inputObject->setEditField(editFieldString);
	inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::EDIT_DESCRIPTION);
}

void MariaInterpreter::parseShow(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW && currentState != STATE_TYPE::CONFLICT) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	int dummyVar = 0;

	if (input.size() == 0) {
		inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE);
		inputObject->setEndTime(new MariaTime(MariaTime::getCurrentTime()));
	} else if (isStringEqual(input, MODIFIER_ALL_TASKS)) {
		inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_ALL);
	} else if (isStringEqual(input, EXPRESSION_TODAY)) {
		inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE);
		inputObject->setEndTime(new MariaTime(MariaTime::getCurrentTime()));
	} else if (isStringEqual(input, EXPRESSION_TOMORROW)) {
		inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE);
		inputObject->setEndTime(new MariaTime(MariaTime::getCurrentTime().getYear(), MariaTime::getCurrentTime().getMonth(), MariaTime::getCurrentTime().getDay()+1));
	} else if (hasDate(input)) {
		// Need to check if there are 1 or more dates.
		if (hasDateTime(extractFromBackOfString(input, DELIMITER_SHOW_DATE_RANGE_START, dummyVar)) && hasDateTime(extractFromBackOfString(input, DELIMITER_SHOW_DATE_RANGE_END, dummyVar))) {
			// End time
			int delimiterPos = 0;
			string dateTimeString = extractFromBackOfString(input, DELIMITER_SHOW_DATE_RANGE_END, delimiterPos);

			input = input.substr(0, delimiterPos);

			if (dateTimeString.size() == 0) {
				SAFE_DELETE(inputObject);
				throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
			}

			dateTimeString = trimWhiteSpace(dateTimeString);
			vector<string> tokenizedDateTime = tokenizeString(dateTimeString);
			removeTokens(tokenizedDateTime, 0, 1);

			MariaTime* endTime;

			try {
				endTime = parseDateTimeString(tokenizedDateTime);
			} catch (exception& e) {
				SAFE_DELETE(inputObject);
				throw;
			}

			inputObject->setEndTime(endTime);

			// Start time
			delimiterPos = 0;
			dateTimeString = extractFromBackOfString(input, DELIMITER_SHOW_DATE_RANGE_START, delimiterPos);

			input = input.substr(0, delimiterPos);

			if (dateTimeString.size() == 0) {
				SAFE_DELETE(inputObject);
				throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
			}

			dateTimeString = trimWhiteSpace(dateTimeString);
			tokenizedDateTime = tokenizeString(dateTimeString);
			removeTokens(tokenizedDateTime, 0, 1);

			MariaTime* startTime;

			try {
				startTime = parseDateTimeString(tokenizedDateTime);
			} catch (exception& e) {
				SAFE_DELETE(inputObject);
				throw;
			}

			inputObject->setStartTime(startTime);
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE_RANGE);

			while (inputObject->getStartTime()->compareTo(*inputObject->getEndTime()) > 0) {
				MariaTime* newEndTime = new MariaTime(inputObject->getEndTime()->getYear(), inputObject->getEndTime()->getMonth(), inputObject->getEndTime()->getDay()+7, inputObject->getEndTime()->getHour(), inputObject->getEndTime()->getMin());

				inputObject->setEndTime(newEndTime);
			}
		} else if (isStringEqual(input, EXPRESSION_DATE_FORMAT)) {
			int seperatorPos = 0;
			char seperatorArray[2] = { '/', '-' };

			for (int j = 0; j < 2; j++) {
				seperatorPos = input.find(seperatorArray[j]);

				if (seperatorPos != string::npos) {
					vector<string> workingList = tokenizeString(input, seperatorArray[j]);

					if (workingList.size() != 3) {
						SAFE_DELETE(inputObject);
						throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
					}

					int day = atoi(workingList[0].c_str());
					int month = atoi(workingList[1].c_str());
					int year = atoi(workingList[2].c_str());

					if (day <= 0) {
						day = 1;
					} else if (day >= 32) {
						day = 31;
					}

					if (month <= 0) {
						month = 1;
					} else if (month >= 13) {
						month = 12;
					}

					if (year < 100) {
						year += 2000;
					}

					break;
				}
			}
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE);
		} else if (isStringContain(input, EXPRESSION_MONTHS_OF_YEAR)) {
			int year = MariaTime::getCurrentTime().getYear();
			int month;
			int day;

			vector<string> workingList = tokenizeString(input);

			if (workingList.size() == 1) {
				// Just show month
				if (isStringEqual(workingList[0], EXPRESSION_MONTHS_OF_YEAR)) {
					month = getMonth(workingList[0]);
				} else {
					SAFE_DELETE(inputObject);
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
				// Need a function to get last day of month...
				inputObject->setStartTime(new MariaTime(year, month, 1));
				inputObject->setEndTime(new MariaTime(year, month, getLastDayOfMonth(year, month)));
				inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE_RANGE);
				return;
			} else if (workingList.size() == 2) {
				// Show date
				if (isStringEqual(workingList[1], EXPRESSION_MONTHS_OF_YEAR)) {
					month = getMonth(workingList[1]);
				} else {
					SAFE_DELETE(inputObject);
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}

				day = atoi(workingList[0].c_str());
				if (day <= 0) {
					day = 1;
				} else if (day >= 32) {
					day = 31;
				}

				inputObject->setEndTime(new MariaTime(year, month, day));
				inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE);
			}

			// Check to see if the month is past today's date.
			// If it is, advance by one year.
			if (month < MariaTime::getCurrentTime().getMonth()) {
				year++;
			}
			inputObject->setEndTime(new MariaTime(year, month, day));
		} else if (isStringEqual(input, EXPRESSION_DAYS_OF_WEEK)) {
			int year = MariaTime::getCurrentTime().getYear();
			int month = MariaTime::getCurrentTime().getMonth();
			int day = MariaTime::getCurrentTime().getDay();

			// do that minus magic thingy
			int currentDayOfWeek = MariaTime::getCurrentTime().getDayWeek();
			int inputDayOfWeek = getDayOfWeek(input);
			int differenceInDays = inputDayOfWeek - currentDayOfWeek;

			if (differenceInDays < 0) {
				day += (7 - abs(differenceInDays));
			} else {
				day += differenceInDays;
			}

			// Also check if the preceding token is "next".
			// If it is, add a week to this day.
			inputObject->setEndTime(new MariaTime(year, month, day));
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::SHOW_DATE);
		}
	} else {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND.c_str());
	}
}

void MariaInterpreter::parseSearch(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW && currentState != STATE_TYPE::CONFLICT) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	if (input.size() == 0) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_NO_ACTIVITY_TITLE.c_str());
	} else {
		inputObject->setTitle(input);
	}
}

void MariaInterpreter::parseDelete(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW && currentState != STATE_TYPE::CONFLICT) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	switch (currentState) {
	case STATE_TYPE::CONFLICT:
		if (input.size() == 0) {
			SAFE_DELETE(inputObject);
			throw exception(MESSAGE_NO_OPTION.c_str());
		} else {
			if (isInteger(input)) {
				inputObject->setOptionID(atoi(input.c_str()));
			} else {
				throw exception(MESSAGE_INVALID_OPTION.c_str());
			}
		}
		break;

	default:
		if (input.size() == 0) {
			SAFE_DELETE(inputObject);
			throw exception(MESSAGE_NO_ACTIVITY_TITLE.c_str());
		} else if (isStringEqual(input, MODIFIER_ALL_TASKS)) {
			inputObject->setCOMMAND_TYPE(MariaInputObject::COMMAND_TYPE::DELETE_ALL);
		} else {
			inputObject->setTitle(input);
		}
		break;
	}
}

void MariaInterpreter::parseMarkDone(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW && currentState != STATE_TYPE::CONFLICT) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	switch (currentState) {
	case STATE_TYPE::CONFLICT:
		if (input.size() == 0) {
			SAFE_DELETE(inputObject);
			throw exception(MESSAGE_NO_OPTION.c_str());
		} else {
			if (isInteger(input)) {
				inputObject->setOptionID(atoi(input.c_str()));
			} else {
				throw exception(MESSAGE_INVALID_OPTION.c_str());
			}
		}
		break;

	default:
		if (input.size() == 0) {
			SAFE_DELETE(inputObject);
			throw exception(MESSAGE_NO_ACTIVITY_TITLE.c_str());
		} else {
			inputObject->setTitle(input);
		}
		break;
	}
}

void MariaInterpreter::parseMarkUndone(string input, MariaInputObject* inputObject, STATE_TYPE currentState) {
	assert(inputObject != NULL);

	if (currentState != STATE_TYPE::HOME && currentState != STATE_TYPE::SHOW && currentState != STATE_TYPE::CONFLICT) {
		SAFE_DELETE(inputObject);
		throw exception(MESSAGE_INVALID_COMMAND_LOCATION.c_str());
	}

	switch (currentState) {
	case STATE_TYPE::CONFLICT:
		if (input.size() == 0) {
			SAFE_DELETE(inputObject);
			throw exception(MESSAGE_NO_OPTION.c_str());
		} else {
			if (isInteger(input)) {
				inputObject->setOptionID(atoi(input.c_str()));
			} else {
				throw exception(MESSAGE_INVALID_OPTION.c_str());
			}
		}
		break;

	default:
		if (input.size() == 0) {
			SAFE_DELETE(inputObject);
			throw exception(MESSAGE_NO_ACTIVITY_TITLE.c_str());
		} else {
			inputObject->setTitle(input);
		}
		break;
	}
}

void MariaInterpreter::parseTime(string input, int& hour, int& min) {
	const static char colon = ':';
	const static char period = '.';
	const static string amString = "am";
	const static string pmString = "pm";
	const static int hourPos = 0;
	const static int minPos = 1;
	const static int tenMinutes = 10;
	size_t colonPos = input.find(colon);
	size_t periodPos = input.find(period);
	vector<string> workingList;

	// Colon can only appear as delimiter only in the following time format: 14:30
	if (colonPos != string::npos) {
		workingList = tokenizeString(input, colon);

		if (workingList.size() != 2 ||
			!isInteger(workingList[hourPos]) ||
			!isInteger(workingList[minPos])) {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}

		hour = atoi(workingList[hourPos].c_str());
		min = atoi(workingList[minPos].c_str());

		if (!checkValidTime(hour, min)) {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}
	} else if (periodPos != string::npos) {
		// 9.30pm
		workingList = tokenizeString(input, period);

		if (workingList.size() != 2 ||
			!isInteger(workingList[hourPos]) ||
			(workingList[minPos].size() != 2 &&
			workingList[minPos].size() != 4)) {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}

		hour = atoi(workingList[hourPos].c_str());

		if (isInteger(workingList[minPos].substr(0, 1))) {
			min = (atoi(workingList[minPos].substr(0, 1).c_str()) * tenMinutes);
		} else {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}

		if (isInteger(workingList[minPos].substr(1, 1))) {
			min += atoi(workingList[minPos].substr(1, 1).c_str());
		} else {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}

		if (workingList[1].size() == 4) {
			if (isStringEqual(workingList[minPos].substr(2, 2), amString)) {
				if (hour > 12) {
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
			} else if (isStringEqual(workingList[minPos].substr(2, 2), pmString)) {
				if (hour < 12) {
					hour += 12;
				} else {
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
			}
		}

		if (!checkValidTime(hour, min)) {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}
	} else {
		// Format of input here will be like: 9pm
		if (input.size() == 3) {
			if (isInteger(input.substr(0, 1))) {
				hour = atoi(input.substr(0, 1).c_str());
			} else {
				throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
			}

			if (isStringEqual(input.substr(1, 2), amString)) {
				if (hour > 12) {
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
			} else if (isStringEqual(input.substr(1, 2), pmString)) {
				if (hour < 12) {
					hour += 12;
				} else {
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
			}
			min = 0;
		} else if (input.size() == 4) {
			if (isInteger(input.substr(0, 1))) {
				hour = atoi(input.substr(0, 1).c_str()) * tenMinutes;
			} else {
				throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
			}

			if (isInteger(input.substr(1, 1))) {
				hour += atoi(input.substr(1, 1).c_str());
			} else {
				throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
			}

			if (isStringEqual(input.substr(2, 2), amString)) {
				if (hour > 12) {
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
			} else if (isStringEqual(input.substr(2, 2), pmString)) {
				if (hour < 12) {
					hour += 12;
				} else {
					throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
				}
			}
			min = 0;
		} else {
			throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
		}
	}
}

MariaTime* MariaInterpreter::parseDateTimeString(vector<string> tokenizedDateTime) {
	int year, month, day, hour, min;
	bool hasDateString = false;
	bool hasTimeString = false;
	const static int dayPos = 0;
	const static int monthPos = 1;
	const static int yearPos = 2;

	for (int i = tokenizedDateTime.size() - 1; i >= 0; i--) {
		if (isStringEqual(tokenizedDateTime[i], EXPRESSION_TODAY) && !hasDateString) {
			year = MariaTime::getCurrentTime().getYear();
			month = MariaTime::getCurrentTime().getMonth();
			day = MariaTime::getCurrentTime().getDay();
			hasDateString = true;
		} else if (isStringEqual(tokenizedDateTime[i], EXPRESSION_TOMORROW) && !hasDateString) {
			year = MariaTime::getCurrentTime().getYear();
			month = MariaTime::getCurrentTime().getMonth();
			day = MariaTime::getCurrentTime().getDay() + 1;
			hasDateString = true;
		} else if (isStringEqual(tokenizedDateTime[i], EXPRESSION_DATE_FORMAT) && !hasDateString) {
			int seperatorPos = 0;
			char seperatorArray[2] = { '/', '-' };

			for (int j = 0; j < 2; j++) {
				seperatorPos = tokenizedDateTime[i].find(seperatorArray[j]);

				if (seperatorPos != string::npos) {
					vector<string> workingList = tokenizeString(tokenizedDateTime[i], seperatorArray[j]);

					if (workingList.size() != 3) {
						throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
					}

					day = atoi(workingList[dayPos].c_str());
					month = atoi(workingList[monthPos].c_str());
					year = atoi(workingList[yearPos].c_str());

					if (day <= 0) {
						day = 1;
					} else if (day >= 32) {
						day = 31;
					}

					if (month <= 0) {
						month = 1;
					} else if (month >= 13) {
						month = 12;
					}

					if (year < 100) {
						year += 2000;
					}

					hasDateString = true;
					break;
				}
			}
		} else if (isStringEqual(tokenizedDateTime[i], EXPRESSION_MONTHS_OF_YEAR) && !hasDateString) {
			year = MariaTime::getCurrentTime().getYear();
			month = getMonth(tokenizedDateTime[i]);

			// If the month is past today's date, advance by one year.
			if (month < MariaTime::getCurrentTime().getMonth()) {
				year++;
			}

			// Check the previous token if it is a valid day.
			// If it isn't, just set it to 1st of whatever month this is.
			if (i >= 1 && isInteger(tokenizedDateTime[i-1])) {
				day = atoi(tokenizedDateTime[i-1].c_str());

				if (day <= 0) {
					day = 1;
				} else if (day >= 32) {
					day = 31;
				}
				i--;
			} else {
				if (month == MariaTime::getCurrentTime().getMonth()) {
					year++;
				}
				day = 1;
			}
			hasDateString = true;
		} else if (isStringEqual(tokenizedDateTime[i], EXPRESSION_DAYS_OF_WEEK) && !hasDateString) {
			year = MariaTime::getCurrentTime().getYear();
			month = MariaTime::getCurrentTime().getMonth();
			day = MariaTime::getCurrentTime().getDay();

			int currentDayOfWeek = MariaTime::getCurrentTime().getDayWeek();
			int inputDayOfWeek = getDayOfWeek(tokenizedDateTime[i]);
			int differenceInDays = inputDayOfWeek - currentDayOfWeek;

			if (differenceInDays < 0) {
				day += (7 - abs(differenceInDays));
			} else {
				day += differenceInDays;
			}
			hasDateString = true;
		} else if (hasTime(tokenizedDateTime[i]) && !hasTimeString) {
			try {
				parseTime(tokenizedDateTime[i], hour, min);
			} catch (exception& e) {
				throw;
			}
			hasTimeString = true;
		}
	}

	if (hasDateString && !hasTimeString) {
		if (year == MariaTime::getCurrentTime().getYear() &&
			month == MariaTime::getCurrentTime().getMonth() &&
			day == MariaTime::getCurrentTime().getDay()) {
				hour = MariaTime::getCurrentTime().getHour()+1;
		} else {
			hour = 9;
		}
		min = 0;
	} else if (!hasDateString && hasTimeString) {
		// Check if the time wanted has already passed. If so, go to next day.
		year = MariaTime::getCurrentTime().getYear();
		month = MariaTime::getCurrentTime().getMonth();
		day = MariaTime::getCurrentTime().getDay();

		if ((hour < MariaTime::getCurrentTime().getHour()) ||
			(hour == MariaTime::getCurrentTime().getHour() && min <= MariaTime::getCurrentTime().getMin())){
			day++;
		}
	} else if (!hasDateString && !hasTimeString) {
		throw exception(MESSAGE_INVALID_DATE_TIME.c_str());
	}

	return new MariaTime(year, month, day, hour, min);
}

bool MariaInterpreter::hasDate(string text) {
	bool isDatePresent = hasDateFormat(text);
	bool isDayOfWeekPresent = hasDayOfWeek(text);
	bool isMonthPresent = hasMonth(text);
	bool isTodayPresent = hasToday(text);
	bool isTomorrowPresent = hasTomorrow(text);

	return (isDatePresent || isDayOfWeekPresent || isMonthPresent || isTodayPresent || isTomorrowPresent);
}

bool MariaInterpreter::hasTime(string text) {
	regex timeExpression(EXPRESSION_TIME_FORMAT, regex_constants::icase);

	return regex_search(text, timeExpression);
}

bool MariaInterpreter::hasDateTime(string text) {
	return (hasDate(text) || hasTime(text));
}

bool MariaInterpreter::hasDateFormat(string text) {
	regex dateExpression("(by|from|to)[ ]" + EXPRESSION_DATE_FORMAT, regex_constants::icase);

	return regex_search(text, dateExpression);
}

bool MariaInterpreter::hasDayOfWeek(string text) {
	regex dayOfWeekExpression("(by|from|to)[ ]" + EXPRESSION_DAYS_OF_WEEK, regex_constants::icase);

	return regex_search(text, dayOfWeekExpression);
}

bool MariaInterpreter::hasMonth(string text) {
	regex monthExpression("(by|from|to)[ ](0?[1-9]|[12][0-9]|3[01])[ ]" + EXPRESSION_MONTHS_OF_YEAR, regex_constants::icase);

	return regex_search(text, monthExpression);
}

bool MariaInterpreter::hasToday(string text) {
	regex todayExpression("(by|from|to)[ ]" + EXPRESSION_TODAY, regex_constants::icase);

	return regex_search(text, todayExpression);
}

bool MariaInterpreter::hasTomorrow(string text) {
	regex tomorrowExpression("(by|from|to)[ ]" + EXPRESSION_TOMORROW, regex_constants::icase);

	return regex_search(text, tomorrowExpression);
}

bool MariaInterpreter::checkValidTime(int hour, int min) {
	if (hour < 0 || hour > 23 || min < 0 || min > 59) {
		return false;
	}
	return true;
}

string MariaInterpreter::extractFromBackOfString(string text, string delimiter, int& delimiterPos) {
	size_t occ1 = text.find(delimiter);
	size_t occ2;

	if (occ1 != string::npos) {
		do {
			occ2 = text.find(delimiter.c_str(), occ1+1, delimiter.size());

			if (occ2 != string::npos) {
				occ1 = occ2;
			} else {
				delimiterPos = occ1;
				return text.substr(occ1);
			}
		} while (occ2 != string::npos);
	}
	delimiterPos = text.size();
	return ("");
}

int MariaInterpreter::getDayOfWeek(string text) {
	regex dayExpression(EXPRESSION_DAYS_OF_WEEK, regex_constants::icase);
	smatch matches;

	if (regex_match(text, matches, dayExpression)) {
		for (int i = 0; i < 7; i++) {
			if (isStringEqual(matches[0], EXPRESSION_DAYS_OF_WEEK_INDIVIDUAL[i])) {
				return i+1;
			}
		}
	}

	return -1;
}

int MariaInterpreter::getLastDayOfMonth(int year, int month) {
	MariaTime* tempDate = new MariaTime(year, month+1, 0);

	int day = tempDate->getDay();

	SAFE_DELETE(tempDate);

	return day;
}

int MariaInterpreter::getMonth(string text) {
	regex monthExpression(EXPRESSION_MONTHS_OF_YEAR, regex_constants::icase);
	smatch matches;

	if (regex_match(text, matches, monthExpression)) {
		for (int i = 0; i < 12; i++) {
			if (isStringEqual(matches[0], EXPRESSION_MONTHS_OF_YEAR_INDIVIDUAL[i])) {
				return i+1;
			}
		}
	}

	return -1;
}

bool MariaInterpreter::isInteger(string text) {
	return !text.empty() &&
		text.find_first_not_of("0123456789") == string::npos;
}

bool MariaInterpreter::isStringContain(string text, string expr, bool ignoreCasing) {
	regex* expression;

	if (ignoreCasing) {
		expression = new regex(expr, regex_constants::icase);
	} else {
		expression = new regex(expr);
	}

	bool result = regex_search(text, *expression);

	SAFE_DELETE(expression);

	return result;
}

bool MariaInterpreter::isStringEqual(string text, string expr, bool ignoreCasing) {
	regex* expression;

	if (ignoreCasing) {
		expression = new regex(expr, regex_constants::icase);
	} else {
		expression = new regex(expr);
	}

	bool result = regex_match(text, *expression);

	SAFE_DELETE(expression);

	return result;
}

string MariaInterpreter::lowercaseString(string text) {
	string toReturn = "";

	for (int i = 0; i < text.size(); i++ ) {
		toReturn += tolower(text[i]);
	}

	return toReturn;
}

void MariaInterpreter::removeTokens(vector<string> &input, int startPos, int endPos) {
	int lengthToRemove = endPos - startPos;

	for (int i = 0; i < lengthToRemove; i++) {
		input.erase(input.begin()+startPos);
	}
}

string MariaInterpreter::stitchString(vector<string> token, int startPos, int endPos, string delimiter) {
	string toReturn = "";

	for (int i = startPos; i < endPos; i++) {
		toReturn += token[i];

		if (i != endPos - 1) {
			toReturn += delimiter;
		}
	}

	return toReturn;
}

vector<string> MariaInterpreter::tokenizeString(string inputString, char delimiter) {
	vector<string> tokens;
	stringstream ss(inputString);
	string token;

	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

string MariaInterpreter::trimWhiteSpaceLeft(string text) {
	text.erase(text.begin(), find_if(text.begin(), text.end(), not1(ptr_fun<int, int>(isspace))));
	return text;
}

string MariaInterpreter::trimWhiteSpaceRight(string text) {
	text.erase(find_if(text.rbegin(), text.rend(), not1(ptr_fun<int, int>(isspace))).base(), text.end());
	return text;
}

string MariaInterpreter::trimWhiteSpace(string text) {
	return trimWhiteSpaceLeft(trimWhiteSpaceRight(text));
}