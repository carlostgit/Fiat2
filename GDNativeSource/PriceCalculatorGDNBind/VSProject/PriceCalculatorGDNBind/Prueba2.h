#pragma once
#pragma once
#include <iostream>

class CA;

class CB
{
public:
	CB() {};
	~CB();
	void PrintSomething() {
		std::cout << "something from CB" << std::endl;
	}

private:
	std::unique_ptr<CB> m_upCB;

};