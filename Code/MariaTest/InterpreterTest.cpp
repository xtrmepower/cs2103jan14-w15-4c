#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MariaTest {
	TEST_CLASS(Interpreter) {
	public:
		TEST_METHOD(Interpreter_EmptyInput) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "";

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::INVALID);

			delete output;
			output = NULL;

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_AddFloatingTask) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add Lunch with Jon";
			string expectedTitle = "Lunch with Jon";

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::ADD_FLOATING);
			Assert::AreEqual(expectedTitle, output->getTitle());

			delete output;
			output = NULL;

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_AddDeadlineTask) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add Do homework by 15/02/2014 23:59";
			string expectedTitle = "Do homework";
			MariaTime* expected = new MariaTime(2014, 2, 15, 23, 59, 0);

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::ADD_DEADLINE);

			Assert::AreEqual(expectedTitle, output->getTitle());

			Assert::AreEqual(expected->getYear(), output->getEndTime()->getYear());
			Assert::AreEqual(expected->getMonth(), output->getEndTime()->getMonth());
			Assert::AreEqual(expected->getDay(), output->getEndTime()->getDay());
			Assert::AreEqual(expected->getHour(), output->getEndTime()->getHour());
			Assert::AreEqual(expected->getMin(), output->getEndTime()->getMin());

			delete expected;
			expected = NULL;

			delete output;
			output = NULL;

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_AddDeadlineTask_Negative) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add by 15/02/2014 23:59";

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::INVALID);

			delete output;
			output = NULL;

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_AddTimedTask) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add Go on a holiday with friends from 15/02/2014 09:00 to 17/02/2014 09:00";
			string expectedTitle = "Go on a holiday with friends";
			MariaTime* expectedStartTime = new MariaTime(2014, 2, 15, 9, 0, 0);
			MariaTime* expectedEndTime = new MariaTime(2014, 2, 17, 9, 0, 0);

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::ADD_TIMED);

			Assert::AreEqual(expectedTitle, output->getTitle());

			Assert::AreEqual(expectedStartTime->getYear(), output->getStartTime()->getYear());
			Assert::AreEqual(expectedStartTime->getMonth(), output->getStartTime()->getMonth());
			Assert::AreEqual(expectedStartTime->getDay(), output->getStartTime()->getDay());
			Assert::AreEqual(expectedStartTime->getHour(), output->getStartTime()->getHour());
			Assert::AreEqual(expectedStartTime->getMin(), output->getStartTime()->getMin());

			Assert::AreEqual(expectedEndTime->getYear(), output->getEndTime()->getYear());
			Assert::AreEqual(expectedEndTime->getMonth(), output->getEndTime()->getMonth());
			Assert::AreEqual(expectedEndTime->getDay(), output->getEndTime()->getDay());
			Assert::AreEqual(expectedEndTime->getHour(), output->getEndTime()->getHour());
			Assert::AreEqual(expectedEndTime->getMin(), output->getEndTime()->getMin());

			delete output;
			output = NULL;

			delete expectedStartTime;
			expectedStartTime = NULL;

			delete expectedEndTime;
			expectedEndTime = NULL;

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_EditTitle) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "edit Do some homework change title Eat dinner";
			string expectedTitle = "Do some homework";
			string expectedEditField = "Eat dinner";

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EDIT_TITLE);
			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedEditField, output->getEditField());

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_EditStartTime) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "edit Lunch with James change start 22/03/2014 1400";
			string expectedTitle = "Lunch with James";
			MariaTime* expectedEditTime = new MariaTime(2014, 3, 22, 14, 0, 0);

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EDIT_START_TIME);
			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedEditTime->getYear(), output->getEditTime()->getYear());
			Assert::AreEqual(expectedEditTime->getMonth(), output->getEditTime()->getMonth());
			Assert::AreEqual(expectedEditTime->getDay(), output->getEditTime()->getDay());
			Assert::AreEqual(expectedEditTime->getHour(), output->getEditTime()->getHour());
			Assert::AreEqual(expectedEditTime->getMin(), output->getEditTime()->getMin());

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_EditEndTime) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "edit Breakfast at Tiffany change end 15.02.2015 1130";
			string expectedTitle = "Breakfast at Tiffany";
			MariaTime* expectedEditTime = new MariaTime(2015, 2, 15, 11, 30, 0);

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EDIT_END_TIME);
			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedEditTime->getYear(), output->getEditTime()->getYear());
			Assert::AreEqual(expectedEditTime->getMonth(), output->getEditTime()->getMonth());
			Assert::AreEqual(expectedEditTime->getDay(), output->getEditTime()->getDay());
			Assert::AreEqual(expectedEditTime->getHour(), output->getEditTime()->getHour());
			Assert::AreEqual(expectedEditTime->getMin(), output->getEditTime()->getMin());

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_ParseDateToday) {
			MariaInterpreter* program = new MariaInterpreter();

			int year, month, day;

			program->parseDate("today", year, month, day);
			Assert::AreEqual(MariaTime::getCurrentTime().getYear(), year);
			Assert::AreEqual(MariaTime::getCurrentTime().getMonth(), month);
			Assert::AreEqual(MariaTime::getCurrentTime().getDay(), day);

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_ParseDateTomorrow) {
			MariaInterpreter* program = new MariaInterpreter();

			int year, month, day;

			program->parseDate("tomorrow", year, month, day);
			Assert::AreEqual(MariaTime::getCurrentTime().getYear(), year);
			Assert::AreEqual(MariaTime::getCurrentTime().getMonth(), month);
			Assert::AreEqual(MariaTime::getCurrentTime().getDay()+1, day);

			// NOTE: Does not account for end of month scenario.

			delete program;
			program = NULL;
		}

		//Test check if parse dat is working with different separators.
		TEST_METHOD(Interpreter_ParseDate) {
			MariaInterpreter* program = new MariaInterpreter();

			int expectedYear = 2014;
			int expectedMonth = 2;
			int expectedDay = 15;
			int year, month, day;

			program->parseDate("15/02/2014", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15-02-2014", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15-02-2014", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15/2/2014", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15-2-2014", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15.2.2014", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15/2/14", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15-2-14", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			program->parseDate("15.2.14", year, month, day);
			Assert::AreEqual(expectedYear, year);
			Assert::AreEqual(expectedMonth, month);
			Assert::AreEqual(expectedDay, day);

			delete program;
			program = NULL;
		}

		//Test dates that are out of the boundary. Test whether if parsse Time corrects it.
		TEST_METHOD(Interpreter_ParseDateBoundary) {
			MariaInterpreter* program = new MariaInterpreter();

			int expectedYear;
			int expectedMonth;
			int expectedDay;
			vector<string> input;
			MariaTime* output = NULL;

			expectedYear = 1900;
			expectedMonth = 12;
			expectedDay = 12;
			input.push_back("12/12/1900");
			output = program->parseDateTimeString(input)[0];
			Assert::AreEqual(expectedYear, output->getYear());
			Assert::AreEqual(expectedMonth, output->getMonth());
			Assert::AreEqual(expectedDay, output->getDay());
			input.clear();

			expectedYear = 2038;
			expectedMonth = 1;
			expectedDay = 20;
			input.push_back("20/01/2038");
			output = program->parseDateTimeString(input)[0];
			Assert::AreEqual(expectedYear, output->getYear());
			Assert::AreEqual(expectedMonth, output->getMonth());
			Assert::AreEqual(expectedDay, output->getDay());
			input.clear();

			expectedYear = 2000;
			expectedMonth = 2;
			expectedDay = 1;
			input.push_back("32/01/2000");
			output = program->parseDateTimeString(input)[0];
			Assert::AreEqual(expectedYear, output->getYear());
			Assert::AreEqual(expectedMonth, output->getMonth());
			Assert::AreEqual(expectedDay, output->getDay());
			input.clear();

			expectedYear = 2014;
			expectedMonth = 3;
			expectedDay = 2;
			input.push_back("30/02/2014");
			output = program->parseDateTimeString(input)[0];
			Assert::AreEqual(expectedYear, output->getYear());
			Assert::AreEqual(expectedMonth, output->getMonth());
			Assert::AreEqual(expectedDay, output->getDay());
			input.clear();

			expectedYear = 2012;
			expectedMonth = 3;
			expectedDay = 1;
			input.push_back("30/02/2012");
			output = program->parseDateTimeString(input)[0];
			Assert::AreEqual(expectedYear, output->getYear());
			Assert::AreEqual(expectedMonth, output->getMonth());
			Assert::AreEqual(expectedDay, output->getDay());
			input.clear();

			delete program;
			program = NULL;
		}

		//Test whether if time ranges work with different separators.
		TEST_METHOD(Interpreter_ParseTime) {
			MariaInterpreter* program = new MariaInterpreter();

			int expectedHour = 12;
			int expectedMin = 34;
			int hour, min;

			program->parseTime("1234", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			program->parseTime("12:34", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			program->parseTime("12.34", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			// Change of format
			expectedHour = 9;
			expectedMin = 37;

			program->parseTime("937", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			delete program;
			program = NULL;
		}

		//Test the boundary whether if time ranges given are out of the expected range.
		TEST_METHOD(Interpreter_ParseTimeBoundary) {
			MariaInterpreter* program = new MariaInterpreter();

			int expectedHour;
			int expectedMin;
			int hour, min;

			expectedHour = 0;
			expectedMin = 0;
			program->parseTime("-1:-1", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			expectedHour = 23;
			expectedMin = 59;
			program->parseTime("24:00", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			expectedHour = 0;
			expectedMin = 1;
			program->parseTime("0:01", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			expectedHour = 23;
			expectedMin = 59;
			program->parseTime("23:59", hour, min);
			Assert::AreEqual(expectedHour, hour);
			Assert::AreEqual(expectedMin, min);

			delete program;
			program = NULL;
		}

		TEST_METHOD(Interpreter_Exit) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "exit";

			MariaInputObject* output = program->parseInput(input);

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EXIT);

			delete program;
			program = NULL;
		}
	};
}