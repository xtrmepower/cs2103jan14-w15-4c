#include "MariaLogic.h"

MariaLogic::MariaLogic(int argc, char *argv[]) : QApplication(argc, argv) {
	mariaInterpreter = new MariaInterpreter();
	mariaTaskManager = new MariaTaskManager();
	mariaFileWriter = new MariaFileWriter();
	mariaUI = new MariaUI(this,mariaTaskManager);

	mariaUI->setState(MariaUI::INTRO);
	mariaUI->getLoading()->setDisplayText("Loading");
	//Put loading intensive stuffs in-between changing state to intro and to other state.
	mariaUI->setState(MariaUI::DEFAULT);


	//Below are things that you can edit.
	//mariaUI->setBackgroundColor("#ff88ff");
	mariaUI->setQuestionText("What would you like to do?");
	mariaUI->setStatus(MariaUI::WAIT);
	mariaUI->setBaseText("create Meeting tomorrow for discussion");
}

MariaLogic::~MariaLogic(void) {
	delete mariaFileWriter;
	delete mariaTaskManager;
	delete mariaInterpreter;
	delete mariaUI;
}

bool MariaLogic::processCommand(string inputText) {
	MariaInterpreter::CommandType commandType = mariaInterpreter->getCommandType(inputText);
	mariaUI->setUserInput("");

	if(commandType == MariaInterpreter::CommandType::Invalid) {
		mariaUI->setQuestionText("I don't understand. Please try again.");
		mariaUI->setStatus(MariaUI::UNKNOWN);
		return false;
	} else {
		mariaUI->setStatus(MariaUI::OK);

		if(commandType == MariaInterpreter::CommandType::Exit){
			mariaUI->setState(MariaUI::INTRO);
			mariaUI->getLoading()->setDisplayText("Saving");
			//Do uploading to google etc.
			//Save files operation etc.
			mariaUI->setState(MariaUI::QUIT);
		} else if(commandType == MariaInterpreter::CommandType::Quit){
			quit();
		} else if(commandType == MariaInterpreter::CommandType::AddFloatingTask){
			string taskTitle = mariaInterpreter->getTitle(inputText);
			if(mariaTaskManager->addTask(taskTitle, NULL, NULL)){
				mariaUI->setQuestionText("Task '"+ taskTitle +"' has been added!");
			} else {
				mariaUI->setQuestionText("There is problem adding '"+ inputText + "'");
			}
		} else if(commandType == MariaInterpreter::CommandType::ShowAllTask){
			mariaUI->setQuestionText("Sure, here's a calendar for demo purposes.");
			mariaUI->setState(MariaUI::FOCUS_CALENDAR);
		} else {
			mariaUI->setQuestionText("Its a valid command, but I'm limited.");
			mariaUI->setState(MariaUI::DEFAULT);
		}
	}

	//todo: call interpreter to generate task & pass to task manager
	return true;
}

int main(int argc, char *argv[]) {
	MariaLogic *mariaLogic = new MariaLogic(argc, argv);

	int returnCode = QApplication::exec();
	delete mariaLogic;

	return returnCode;
}