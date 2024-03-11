#pragma once


class ScriptHandler
{
public:

	ScriptHandler();
	~ScriptHandler();

	void Act();
	void StateCheck();
	void QueueCheck();

private:
	void Init();
};

