#pragma once

#include"window.h"
#include"EventManager.h"
#include<memory>

struct SharedContext {

	SharedContext():win(nullptr),evMgr(nullptr){}
	window * win;
	EventManager *evMgr;


	static std::shared_ptr<SharedContext> shConptr;

	static std::shared_ptr<SharedContext> getInstance() {
		if (shConptr.get() == nullptr) {
			shConptr = std::make_shared<SharedContext>();
		}
		return shConptr;
	}

};
