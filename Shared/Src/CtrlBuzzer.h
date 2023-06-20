//---------------------------------------------------------------------------
#ifndef CtrlBuzzerH
#define CtrlBuzzerH
class CtrlBuzzer:
	public PROControl
{

public:
	CtrlBuzzer(void);
	~CtrlBuzzer(void);
  void Update(char Mode);
};
//---------------------------------------------------------------------------
#endif
