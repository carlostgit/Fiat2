#pragma once
#include <iostream>
#include <memory>

class CB;

class CA
{
public:
	CA() {};
	~CA();
	void PrintSomething() {
		std::cout << "something from CA" << std::endl;
	}

private:

	std::unique_ptr<CB> m_upCB;

};