#pragma once

class BaseAnimationTask {
public:
	virtual ~BaseAnimationTask() {}
	virtual void start() = 0;
	virtual void setIntervalSecs(float secs) = 0;
	virtual void setCallback(void lambda(void)) = 0;
};
