#include "EXPDesign.h"

SC_MODULE(EXPTB){
	sc_signal <sc_logic> clk, rst, start; 
	sc_signal <sc_lv<8> > x;
	sc_signal < sc_lv<10>> result; 
	sc_signal <sc_logic> busy;
	sc_signal <sc_logic> done;
	
	EXP* Exp1; 

	SC_CTOR (EXPTB){
		Exp1= new EXP ("Exponential_1"); 
		Exp1->clk(clk); 
		Exp1->rst(rst); 
		Exp1->start(start); 
		Exp1->x(x); 
		Exp1->result(result); 
		Exp1->busy(busy); 
		Exp1->done(done);
		//
		SC_THREAD(inputing); 
		SC_THREAD(reseting); 
		SC_THREAD(clocking); 
		SC_METHOD(displaying);
		sensitive <<done.posedge_event();
	}
	void inputing(); 
	void reseting(); 
	void clocking(); 
	void displaying(); 
	
}; 
