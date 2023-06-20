#pragma once

class CErrCounter
{
public:
	CErrCounter():m_errCounter(0){}
	bool SetErr(bool err);
	
private:
	unsigned m_errCounter;
};
