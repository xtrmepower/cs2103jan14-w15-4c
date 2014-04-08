#pragma once
#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qlabel.h>
#include <QtCore/QTimer>
#include "MariaTaskManager.h"

using namespace std;

class MariaUIPreview : QWidget {
	Q_OBJECT

public:
	static const string PREVIEW_EVENT_TOMORROW_NONE;
	static const string PREVIEW_EVENT_TOMORROW;
	static const string PREVIEW_EVENT_TOMORROW_MULTIPLE;

	static const string PREVIEW_EVENT_TODAY_NONE;
	static const string PREVIEW_EVENT_TODAY_FIRST_AT;
	static const string PREVIEW_EVENT_TODAY_FIRST_REMAINING_TIME;
	static const string PREVIEW_EVENT_TODAY_NEXT_AT;
	static const string PREVIEW_EVENT_TODAY_NEXT_REMAINING_TIME;

	static const string PREVIEW_DEADLINE_TOMORROW;
	static const string PREVIEW_DEADLINE_TOMORROW_MUTIPLE;

	static const string PREVIEW_DEADLINE_TODAY_AT;
	static const string PREVIEW_DEADLINE_TODAY_REMAINING_TIME;
	static const string PREVIEW_DEADLINE_TODAY_MUTIPLE;
	static const string PREVIEW_DEADLINE_ITEM_AT;
	static const string PREVIEW_DEADLINE_ITEM_REMAINING_TIME;
	static const string PREVIEW_DEADLINE_ITEM_TRIM;

	static const string PREVIEW_FLOATING_SUGGESTION_DEFAULT;

	static const float START_HEIGHT_SCALE;
	static const float MESSAGE_HEIGHT;
	static const int TEXTBOX_X_OFFSET = 30;
	static const int UPDATE_FREQUENCY = 30000;
	static const int FONT_SIZE = 16;
	static const int STRING_BUFFER_SIZE = 255;
	static const int MAX_TASK_SHOWN = 3;

private:
	QMainWindow *_qmainWindow;
	MariaTaskManager *_taskManager;
	
	QTimer *_updateTextTimer;
	QLabel *_mainText;

	MariaTask *_generatedSuggestionTask;
	
	string generateTodayText();
	string generateTomorrowText();

	//Force denotes whether to generate a new task instead of using the existing store task.
	string generateSuggestionText(bool force);

public slots:
	void updateText();

public:
	MariaUIPreview(QMainWindow *qmainWindow,MariaTaskManager *taskManager);
	~MariaUIPreview();

	void startUpdating();
	void updateGUI(QPointF statePosition);
};

