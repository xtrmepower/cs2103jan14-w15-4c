//@author A0111821X
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MariaTest {
	TEST_CLASS(Interpreter_New) {
	public:
		TEST_METHOD(I2_AddFloatingTask) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add Buy apples";
			string expectedTitle = "Buy apples";

			MariaInputObject* output;
			try {
				output = program->parseInput(input);
			} catch (exception& e) {
				Assert::IsFalse(1);
				e=e;
			}

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::ADD_FLOATING);
			Assert::AreEqual(expectedTitle, output->getTitle());

			SAFE_DELETE(output);
			SAFE_DELETE(program);
		}

		TEST_METHOD(I2_AddDeadlineTask) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add Buy apples by Sunday";
			string expectedTitle = "Buy apples";

			MariaInputObject* output;
			try {
				output = program->parseInput(input);
			} catch (exception& e) {
				Assert::IsFalse(1);
				e=e;
			}

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::ADD_DEADLINE);

			int expectedYear = MariaTime::getCurrentTime().getYear();
			int expectedMonth = MariaTime::getCurrentTime().getMonth();
			int expectedDay = MariaTime::getCurrentTime().getDay();
			int expectedDayOfWeek = 0;

			int currentDayOfWeek = MariaTime::getCurrentTime().getDayWeek();
			int differenceInDays = expectedDayOfWeek - currentDayOfWeek;

			if (differenceInDays < 0) {
				expectedDay += (7 - abs(differenceInDays));
			} else {
				expectedDay += differenceInDays;
			}

			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedYear, output->getEndTime()->getYear());
			Assert::AreEqual(expectedMonth, output->getEndTime()->getMonth());
			Assert::AreEqual(expectedDay, output->getEndTime()->getDay());
			Assert::AreEqual(expectedDayOfWeek, output->getEndTime()->getDayWeek());

			SAFE_DELETE(output);
			SAFE_DELETE(program);
		}

		TEST_METHOD(I2_AddTimedTask) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "add Buy apples from today to tomorrow";
			string expectedTitle = "Buy apples";

			MariaInputObject* output;
			try {
				output = program->parseInput(input);
			} catch (exception& e) {
				Assert::IsFalse(1);
				e=e;
			}

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::ADD_TIMED);
			Assert::AreEqual(expectedTitle, output->getTitle());

			MariaTime* expectedStartTime = new MariaTime(MariaTime::getCurrentTime());
			Assert::AreEqual(expectedStartTime->getYear(), output->getStartTime()->getYear());
			Assert::AreEqual(expectedStartTime->getMonth(), output->getStartTime()->getMonth());
			Assert::AreEqual(expectedStartTime->getDay(), output->getStartTime()->getDay());
			Assert::AreEqual(expectedStartTime->getDayWeek(), output->getStartTime()->getDayWeek());

			MariaTime* expectedEndTime = new MariaTime(expectedStartTime->getYear(), expectedStartTime->getMonth(), expectedStartTime->getDay()+1);
			Assert::AreEqual(expectedEndTime->getYear(), output->getEndTime()->getYear());
			Assert::AreEqual(expectedEndTime->getMonth(), output->getEndTime()->getMonth());
			Assert::AreEqual(expectedEndTime->getDay(), output->getEndTime()->getDay());
			Assert::AreEqual(expectedEndTime->getDayWeek(), output->getEndTime()->getDayWeek());

			SAFE_DELETE(expectedStartTime);
			SAFE_DELETE(expectedEndTime);
			SAFE_DELETE(output);
			SAFE_DELETE(program);
		}

		TEST_METHOD(I2_EditTitle) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "edit apple change title banana";
			string expectedTitle = "apple";
			string expectedEditField = "banana";

			MariaInputObject* output;
			try {
				output = program->parseInput(input);
			} catch (exception& e) {
				Assert::IsFalse(1);
				e=e;
			}

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EDIT_TITLE);
			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedEditField, output->getEditField());

			SAFE_DELETE(output);
			SAFE_DELETE(program);
		}

		TEST_METHOD(I2_EditStartTime) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "edit apple change start Sunday";
			string expectedTitle = "apple";

			MariaInputObject* output;
			try {
				output = program->parseInput(input);
			} catch (exception& e) {
				Assert::IsFalse(1);
				e=e;
			}

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EDIT_START_TIME);

			int expectedYear = MariaTime::getCurrentTime().getYear();
			int expectedMonth = MariaTime::getCurrentTime().getMonth();
			int expectedDay = MariaTime::getCurrentTime().getDay();
			int expectedDayOfWeek = 0;

			int currentDayOfWeek = MariaTime::getCurrentTime().getDayWeek();
			int differenceInDays = expectedDayOfWeek - currentDayOfWeek;

			if (differenceInDays < 0) {
				expectedDay += (7 - abs(differenceInDays));
			} else {
				expectedDay += differenceInDays;
			}

			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedYear, output->getEditTime()->getYear());
			Assert::AreEqual(expectedMonth, output->getEditTime()->getMonth());
			Assert::AreEqual(expectedDay, output->getEditTime()->getDay());
			Assert::AreEqual(expectedDayOfWeek, output->getEditTime()->getDayWeek());

			SAFE_DELETE(output);
			SAFE_DELETE(program);
		}

		TEST_METHOD(I2_EditEndTime) {
			MariaInterpreter* program = new MariaInterpreter();

			string input = "edit apple change end Sunday";
			string expectedTitle = "apple";

			MariaInputObject* output;
			try {
				output = program->parseInput(input);
			} catch (exception& e) {
				Assert::IsFalse(1);
				e=e;
			}

			Assert::IsTrue(output->getCommandType() == MariaInputObject::COMMAND_TYPE::EDIT_END_TIME);

			int expectedYear = MariaTime::getCurrentTime().getYear();
			int expectedMonth = MariaTime::getCurrentTime().getMonth();
			int expectedDay = MariaTime::getCurrentTime().getDay();
			int expectedDayOfWeek = 0;

			int currentDayOfWeek = MariaTime::getCurrentTime().getDayWeek();
			int differenceInDays = expectedDayOfWeek - currentDayOfWeek;

			if (differenceInDays < 0) {
				expectedDay += (7 - abs(differenceInDays));
			} else {
				expectedDay += differenceInDays;
			}

			Assert::AreEqual(expectedTitle, output->getTitle());
			Assert::AreEqual(expectedYear, output->getEditTime()->getYear());
			Assert::AreEqual(expectedMonth, output->getEditTime()->getMonth());
			Assert::AreEqual(expectedDay, output->getEditTime()->getDay());
			Assert::AreEqual(expectedDayOfWeek, output->getEditTime()->getDayWeek());

			SAFE_DELETE(output);
			SAFE_DELETE(program);
		}
	};
}