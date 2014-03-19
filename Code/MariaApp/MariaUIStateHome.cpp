#include <assert.h> 
#include "MariaUIStateHome.h"
#include "MariaUI.h"
#include "MariaTaskManager.h"

const float MariaUIStateHome::TASKBAR_STARTHEIGHT_SCALE=0.25;
const float MariaUIStateHome::TASK_STARTHEIGHT_SCALE=0.35;
const float MariaUIStateHome::TASK_STARTHEIGHT_DIFFERENCE=24.0;

MariaUIStateHome::MariaUIStateHome(MariaTaskManager *taskManager,QMainWindow* qmainWindow) : MariaStateObject(qmainWindow) {
	_qmainWindow=qmainWindow;
	_taskManager=taskManager;

	_clock=new MariaUIClock(_qmainWindow);
}

MariaUIStateHome::~MariaUIStateHome() {
	clearTask();
	delete _clock;
}

void MariaUIStateHome::initBeginState() {
	clearTask();
	_clock->startUpdating();
	((MariaUI*)_qmainWindow)->getCommandBar()->setDestination(_qmainWindow->height()*TASKBAR_STARTHEIGHT_SCALE);
	((MariaUI*)_qmainWindow)->setBackgroundColor(114,143,22);
}

void MariaUIStateHome::initActiveState() {
	vector<MariaTask*> tempList = _taskManager->findTask("");
	for(MariaTask* temp : tempList){
		addTask(temp);
	}
	sortTask();
	for(int i=0;i<_taskStack.size();i++) {
		_taskStack.at(i)->setPosition(QPointF(_qmainWindow->width(),_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*i));
		_taskStack.at(i)->setDestination(QPointF(0.0,_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*i));
	}
}

void MariaUIStateHome::initEndState() {

	for(int i=0;i<_taskStack.size();i++) {
		_taskStack.at(i)->setDestination(QPointF(-_qmainWindow->width()-TEXTBOX_X_OFFSET,_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*i));
	}
}

bool MariaUIStateHome::timerBeginState() {
	_clock->updateGUI(getPosition());
	return false;
}

bool MariaUIStateHome::timerActiveState() {
	return false;
}

bool MariaUIStateHome::timerEndState() {
	_clock->updateGUI(getPosition());
	return false;
}

//Function determines which task shall be sorted as smaller.
//Deadline task shall take precedence in the sort.
//Followed by dateline task. Then floating task.
bool MariaUIStateHome::sortTaskFunction(MariaUITask *i,MariaUITask *j) {

	MariaTask *a=i->getMariaTask();
	MariaTask *b=j->getMariaTask();
	if(a->getType()==b->getType()) {

		return false;
	} else {
		return (a->getType()<b->getType());
	}
}

void MariaUIStateHome::updateNumber() {
	for(int i=0;i<_taskStack.size();i++) {
		_taskStack.at(i)->setTitlePretext(std::to_string(i+1)+". ");
	}
}

MariaUITask* MariaUIStateHome::addTask(MariaTask *task) {
	MariaUITask *temp = new MariaUITask(_qmainWindow,task,_qmainWindow->width());

	temp->setPosition(QPointF(_qmainWindow->width(),_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*_taskStack.size()));
	temp->setDestination(QPointF(0.0,_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*_taskStack.size()));
	temp->show();
	temp->startUpdatingTime();

	_taskStack.push_back(temp);

	return temp;
}

void MariaUIStateHome::updateTask() {
	for(int i=0;i<_taskStack.size();i++) {
		_taskStack.at(i)->updateDetails();
		_taskStack.at(i)->setDestination(QPointF(0.0,_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*i));
	}
}

MariaUITask* MariaUIStateHome::eraseTask(int index) {
	
	assert(index<_taskStack.size());

	MariaUITask* temp = NULL;
	temp = _taskStack[index];
	_taskDisposeStack.push_back(temp);
	temp->setDestination(QPointF(-_qmainWindow->width()-TEXTBOX_X_OFFSET,_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*index));
	temp->stopUpdatingTime();
	_taskStack.erase(_taskStack.begin()+index);

	sortTask();
	return temp;
}

MariaUITask* MariaUIStateHome::eraseTask(MariaTask* task) {
	MariaUITask* temp = NULL;
	for (int i = 0; i < _taskStack.size(); i++) {
		if (_taskStack[i]->getMariaTask() == task) {
			temp = _taskStack[i];
			_taskDisposeStack.push_back(temp);
			temp->setDestination(QPointF(-_qmainWindow->width()-TEXTBOX_X_OFFSET,_qmainWindow->height()*TASK_STARTHEIGHT_SCALE+TASK_STARTHEIGHT_DIFFERENCE*i));
			temp->stopUpdatingTime();
			_taskStack.erase(_taskStack.begin()+i);
		}
	}

	sortTask();
	return temp;
}

void MariaUIStateHome::clearTask() {
	for(int i=0;i<_taskStack.size();i++) {
		delete _taskStack.at(i);
	}

	while(_taskStack.size()>0) {
		_taskStack.pop_back();
	}

	for(int i=0;i<_taskDisposeStack.size();i++) {
		delete _taskDisposeStack.at(i);
	}

	while(_taskDisposeStack.size()>0) {
		_taskDisposeStack.pop_back();
	}
}

void MariaUIStateHome::sortTask() {
	std::sort (_taskStack.begin(), _taskStack.end(), MariaUIStateHome::sortTaskFunction);
	updateTask();
}

int MariaUIStateHome::getTotalTask() {
	return _taskStack.size();
}