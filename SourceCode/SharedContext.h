#pragma once

#include"window.h"
#include"EventManager.h"

struct SharedContext {

	SharedContext():win(nullptr),evMgr(nullptr){}

	window * win;
	EventManager *evMgr;
};