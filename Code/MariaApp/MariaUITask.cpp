#include "MariaUITask.h"
#include "MariaTime.h"

const float MariaUITask::FLOW_FACTOR=0.1;
const float MariaUITask::VALUE_THRESHOLD=1.0;
const float MariaUITask::FONT_SIZE=10.0;
const float MariaUITask::TASK_HEIGHT=14.0;
const float MariaUITask::TIMESTAMP_X_OFFSET=-3.0;
const string MariaUITask::MESSAGE_DEADLINETASK_DUE="Due in ";
const string MariaUITask::MESSAGE_DEADLINETASK_OVERDUE="Overdue";
const string MariaUITask::MESSAGE_TIMEDTASK_BEFORE="Starting in ";
const string MariaUITask::MESSAGE_TIMEDTASK_AFTER="Event started";

MariaUITask::MariaUITask(QMainWindow *qmainWindow, MariaTask *task, float width) {
	_qmainWindow=qmainWindow;

	_destination=QPoint(0,0);
	_position=QPoint(0,0);

	_taskReference=task;
	_displayTitle = new QLabel(_qmainWindow);
	_timeText = new QLabel(_qmainWindow);
	switch(_taskReference->getType()) {
	case MariaTask::FLOATING:
		_displayTitle->setStyleSheet("color:#ffffff; background-color:rgba(255,0,0,128);border: 1px solid rgba(25,25,25,25);font-size:"+QString::number(FONT_SIZE)+"px;");		
		break;
	case MariaTask::DEADLINE:
		_displayTitle->setStyleSheet("color:#ffffff; background-color:rgba(255,255,0,128);border: 1px solid rgba(25,25,25,25);font-size:"+QString::number(FONT_SIZE)+"px;");
		break;
	case MariaTask::TIMED:
		_displayTitle->setStyleSheet("color:#ffffff; background-color:rgba(0,128,255,128);border: 1px solid rgba(25,25,25,25);font-size:"+QString::number(FONT_SIZE)+"px;");
		break;
	default:
		_displayTitle->setStyleSheet("color:#ffffff; background-color:rgba(0,0,255,128);border: 1px solid white;font-size:"+QString::number(FONT_SIZE)+"px;");
		break;
	}
	_displayTitle->setText(QString::fromStdString(_taskReference->getTitle()));
	_displayTitle->setAlignment(Qt::AlignLeft);
	_timeText->setAlignment(Qt::AlignRight);
	_displayTitle->hide();
	_timeText->setStyleSheet("color:#ffffff;font-size:"+QString::number(FONT_SIZE)+"px;");
	_timeText->hide();

	_width=width;
	
	_updatePositionTimer = new QTimer(this);
	connect(_updatePositionTimer, SIGNAL(timeout()), this, SLOT(updatePosition()));
	_updatePositionTimer->start(1);

	_updateTimeTextTimer = new QTimer(this);
	connect(_updateTimeTextTimer, SIGNAL(timeout()), this, SLOT(updateTimeText()));
	updateTimeText();
	_updateTimeTextTimer->start(1000);
}

MariaUITask::~MariaUITask() {
	if(_updateTimeTextTimer->isActive()) {
		_updateTimeTextTimer->stop();
	}
	if(_updatePositionTimer->isActive()) {
		_updatePositionTimer->stop();
	}
	delete _updatePositionTimer;
	delete _updatePositionTimer;
	delete _displayTitle;
	delete _timeText;
}

void MariaUITask::setTitlePretext(string pretext) {
	_displayTitle->setText(QString::fromStdString(pretext)+QString::fromStdString(_taskReference->getTitle()));
}

bool MariaUITask::updatePosition() {
	if(abs(_position.x()-_destination.x())>VALUE_THRESHOLD||
		abs(_position.y()-_destination.y())>VALUE_THRESHOLD) {
		_position.setX(_position.x()+(_destination.x()-_position.x())*FLOW_FACTOR);
		_position.setY(_position.y()+(_destination.y()-_position.y())*FLOW_FACTOR);
		_displayTitle->setGeometry(QRect(_position.x(),_position.y(),_width,TASK_HEIGHT));
		_timeText->setGeometry(QRect(_position.x()+TIMESTAMP_X_OFFSET,_position.y(),_width,TASK_HEIGHT));
		return true;
	} else {
		if(_updatePositionTimer->isActive()) {
			_updatePositionTimer->stop();
		}
		return false;
	}
}

void MariaUITask::updateTimeText() {

	string timeFormatted = _taskReference->getTimeFromNow();

	if(_taskReference->getType() == MariaTask::DEADLINE) {
		if(timeFormatted.empty()){
			timeFormatted = MESSAGE_DEADLINETASK_OVERDUE;
		}else{
			timeFormatted = MESSAGE_DEADLINETASK_DUE + timeFormatted;
		}
		_timeText->setText(QString::fromStdString(timeFormatted));

	}else if(_taskReference->getType() == MariaTask::TIMED){
		if(timeFormatted.empty()){
			timeFormatted = MESSAGE_TIMEDTASK_AFTER;
		}else{
			timeFormatted = MESSAGE_TIMEDTASK_BEFORE + timeFormatted;
		}
	}
	_timeText->setText(QString::fromStdString(timeFormatted));
	
}

void MariaUITask::setPosition(QPointF position) {
	_position=position;
	if(!_updatePositionTimer->isActive()) {
		_updatePositionTimer->start(1);
	}
}

QPointF MariaUITask::getPosition() {
	return _position;
}

void MariaUITask::setDestination(QPointF destination) {
	_destination=destination;
	if(!_updatePositionTimer->isActive()) {
		_updatePositionTimer->start(1);
	}
}

QPointF MariaUITask::getDestination() {
	return _destination;
}

void MariaUITask::show() {
	_displayTitle->show();
	_timeText->show();
}

void MariaUITask::hide() {
	_displayTitle->hide();
	_timeText->hide();
}

MariaTask * MariaUITask::getMariaTask() {
	return _taskReference;
}