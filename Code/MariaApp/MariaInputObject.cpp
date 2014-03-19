#include "MariaInputObject.h"

MariaInputObject::MariaInputObject() {
	_commandType = CommandInvalid;
	_addType = AddNone;
	_editType = EditNone;

	_startTime = NULL;
	_endTime = NULL;
}

MariaInputObject::~MariaInputObject() {
	delete _startTime;
	_startTime = NULL;

	delete _endTime;
	_endTime = NULL;
}

void MariaInputObject::setValidity(bool valid) {
	_validInput = valid;
}

void MariaInputObject::setOriginalInput(string originalInput) {
	_originalInput = originalInput;
}

void MariaInputObject::setCommandType(CommandType newCommandType) {
	_commandType = newCommandType;
}

void MariaInputObject::setTitle(string newTitle) {
	_title = newTitle;
}

void MariaInputObject::setEditField(string newEditField) {
	_editField = newEditField;
}

void MariaInputObject::setConflictID(int newConflictID) {
	_conflictID = newConflictID;
}

void MariaInputObject::setStartTime(MariaTime* newStartTime) {
	_startTime = newStartTime;
}

void MariaInputObject::setEndTime(MariaTime* newEndTime) {
	_endTime = newEndTime;
}

void MariaInputObject::setAddType(AddType newAddType) {
	_addType = newAddType;
}

void MariaInputObject::setEditType(EditType newEditType) {
	_editType = newEditType;
}

bool MariaInputObject::isValid() const {
	return _validInput;
}

string MariaInputObject::getOriginalInput() const {
	return _originalInput;
}

MariaInputObject::CommandType MariaInputObject::getCommandType() const {
	return _commandType;
}

string MariaInputObject::getTitle() const {
	return _title;
}

string MariaInputObject::getEditField() const {
	return _editField;
}

int MariaInputObject::getConflictID() const {
	return _conflictID;
}

MariaTime* MariaInputObject::getStartTime() const {
	return _startTime;
}

MariaTime* MariaInputObject::getEndTime() const {
	return _endTime;
}

MariaInputObject::AddType MariaInputObject::getAddType() const {
	return _addType;
}

MariaInputObject::EditType MariaInputObject::getEditType() const {
	return _editType;
}