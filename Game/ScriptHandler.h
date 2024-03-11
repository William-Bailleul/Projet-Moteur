#pragma once

class ComponentScript;

class ScriptHandler
{
public:

	ScriptHandler(ComponentScript* linkedScript);
	~ScriptHandler();

	void Act();
	void QueueCheck();

private:
	ComponentScript* linkedObjectScript;

	void Init(ComponentScript* linkedScript);
};