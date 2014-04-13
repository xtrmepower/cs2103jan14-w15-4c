#include <assert.h>
#include "MariaMacros.h"
#include "MariaUIStateHome.h"
#include "MariaUI.h"

const float MariaUIStateHome::TASK_STARTHEIGHT_SCALE = 0.65;
const float MariaUIStateHome::TASKBAR_STARTHEIGHT_SCALE = 0.1;

MariaUIStateHome::MariaUIStateHome(QMainWindow* qmainWindow, vector<MariaTask*> weekTask) : MariaUIStateDisplay(qmainWindow, TASK_STARTHEIGHT_SCALE, MAX_ITEM_IN_PAGE) {
	assert(qmainWindow != NULL);

	_preview = new MariaUIPreview(_qmainWindow);
	_clock = new MariaUIClock(_qmainWindow);
	_weekTask = weekTask;
}

MariaUIStateHome::~MariaUIStateHome() {
	clearUITask();
	SAFE_DELETE(_clock);
	SAFE_DELETE(_preview);
}

void MariaUIStateHome::updateGUI() {
	((MariaUI*)_qmainWindow)->forceLogicCall();
	_preview->updateGUI(getPosition());
}

MariaUIPreview* MariaUIStateHome::getUIPreview() {
	return _preview;
}

void MariaUIStateHome::initBeginState() {
	clearUITask();
	_clock->startUpdating();

	((MariaUI*)_qmainWindow)->getCommandBar()->setDestination(_qmainWindow->height()*TASKBAR_STARTHEIGHT_SCALE);
	((MariaUI*)_qmainWindow)->setBackgroundColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B);
}

void MariaUIStateHome::initActiveState() {
	for(MariaTask* temp : _weekTask) {
		addUITask(temp, MariaUITask::DISPLAY_TYPE::NORMAL);
	}

	updateUITaskPosition();
	updatePage();
}

void MariaUIStateHome::initEndState() {
	eraseAllUITask();
}

bool MariaUIStateHome::timerBeginState() {
	_preview->updateGUI(getPosition());
	_clock->updateGUI(getPosition());
	updatePageTitleGUI();

	return false;
}

bool MariaUIStateHome::timerActiveState() {
	return false;
}

bool MariaUIStateHome::timerEndState() {
	_preview->updateGUI(getPosition());
	_clock->updateGUI(getPosition());
	updatePageTitleGUI();

	return false;
}