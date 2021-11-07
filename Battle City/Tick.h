#pragma once

#include <vector>

using namespace std;

class Tickable
{
public:
	Tickable();
	~Tickable();

	virtual void Tick();

	static vector<Tickable*>* GetAllTicks();
private:
	static vector<Tickable*> allTicks;
};