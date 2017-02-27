#include "EXPTB.h"

void EXPTB::inputing(){
		start = SC_LOGIC_0;
		wait(10, SC_NS);
		start = SC_LOGIC_1;
		x = "11111111";
		wait(60, SC_NS);
		start = SC_LOGIC_0;
		wait(2400, SC_NS);
		start = SC_LOGIC_1;
		x = "10000000";
		wait(100, SC_NS);
		start = SC_LOGIC_0;
		wait(2400, SC_NS);
		start = SC_LOGIC_1;
		x = "00000000";
		wait(100, SC_NS);
		start = SC_LOGIC_0;
		wait(2400, SC_NS);
		start = SC_LOGIC_1;
		x = "00000001";
		wait(100, SC_NS);
		start = SC_LOGIC_0;
}

void EXPTB::clocking(){
	int i; 
	clk = sc_logic('1'); 
	for (i=0; i <=50; i++)   
	{
		clk = sc_logic('0');
		wait (50, SC_NS); 
		clk = sc_logic('1');
		wait (50, SC_NS); 
	}
}
void EXPTB::reseting(){
	rst = (sc_logic)'0';  
	wait (5, SC_NS);
	rst = (sc_logic)'1';
	wait (5, SC_NS);
	rst = (sc_logic)'0'; 
};

void EXPTB::displaying(){

	cout << " x = " << x.read() << "  result = " << result.read() <<endl; 
}