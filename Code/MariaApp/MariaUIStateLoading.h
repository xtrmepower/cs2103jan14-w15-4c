//@author A0111784H
#pragma once

#include <string>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qlabel.h>
#include <QtCore/QTimer>
#include "MariaStateObject.h"

using namespace std;

class MariaUIStateLoading : public MariaStateObject {
public:
	MariaUIStateLoading(QMainWindow* qmainWindow);
	~MariaUIStateLoading();

	void setDisplayText(string text);
	void setLoadingDone();
	void setQuitAfterLoadingTrue();
	
private:
	static const int AMOUNT_OF_DOTS = 5;
	static const int LOGO_SPEED_RETARDER = 80;
	static const float FLOW_FACTOR;
	static const float VALUE_THRESHOLD;
	static const float DISPLAY_TEXT_WIDTH;
	static const float DISPLAY_TEXT_HEIGHT;
	static const float LOGO_START_Y;
	static const float LOGO_STAGE_Y_SCALE;
	static const float TEXT_STAGE_Y_SCALE;
	static const float DOTS_STAGE_Y_SCALE;
	static const float DOTS_X_OFFSET;
	static const float DOTS_SEPARATION_WIDTH;
	static const float DOTS_X_SPEED;
	static const float DOTS_X_VARIABLE_SPEED;
	
	QMainWindow* _qmainWindow;

	QLabel* _displayText;
	QLabel* _logo;
	float _logoYPos;
	int _logoImageIndex;

	QLabel* _loadingDots[AMOUNT_OF_DOTS];
	float _dotsXPos[AMOUNT_OF_DOTS];

	bool _doneLoading;
	bool _quitAfterLoading;

	void initBeginState();
	void initActiveState();
	void initEndState();
	bool timerBeginState();
	bool timerActiveState();
	bool timerEndState();
	
	void animateLogo();
	bool animateDots();
	void updateGUIPosition();
};

