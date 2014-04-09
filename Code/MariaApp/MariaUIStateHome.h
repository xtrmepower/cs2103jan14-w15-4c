#pragma once

#include <algorithm> 
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qlabel.h>
#include "MariaUIStateDisplay.h"
#include "MariaUIClock.h"
#include "MariaUITask.h"
#include "MariaTask.h"
#include "MariaUIPreview.h"

class MariaTaskManager;
class MariaUIStateHome : public MariaUIStateDisplay {
public:
	static const float TASK_STARTHEIGHT_SCALE;
	static const float TASKBAR_STARTHEIGHT_SCALE;
	static const int MAX_ITEM_IN_PAGE = 5;

private:
	MariaUIClock *_clock;
	MariaUIPreview *_preview;
	vector<MariaTask*> _weekTask;

	void initBeginState();
	void initActiveState();
	void initEndState();
	bool timerBeginState();
	bool timerActiveState();
	bool timerEndState();

public:
	MariaUIStateHome(QMainWindow* qmainWindow, vector<MariaTask*> weekTask);
	~MariaUIStateHome();

	void updateGUI();
	MariaUIPreview* getUIPreview();
};

