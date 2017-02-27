#include <systemc.h>

SC_MODULE (controller){

	sc_in  <sc_logic> rst, clk, start, co; 
	sc_out <sc_logic> loadExponent;
	sc_out <sc_logic> rstExponent;
	sc_out <sc_logic> loadTerm;
	sc_out <sc_logic> initTerm;
	sc_out <sc_logic> rstTerm;
	sc_out <sc_logic> selTableData;
	sc_out <sc_logic> rstResultReg;
	sc_out <sc_logic> initResultReg;
	sc_out <sc_logic> loadResultReg;
	sc_out <sc_logic> enCounter;
	sc_out <sc_logic> rstCounter;
	sc_out <sc_logic> initCounter;
	sc_out <sc_logic> busy;
	sc_out <sc_logic> done;
	sc_out <sc_logic> memSel;
	sc_out <sc_logic> rwbar;

	
	enum states {INITIALIZE, WAIT_ON_START, CALC_NEXT_TERM_1, CALC_NEXT_TERM_2, ADD_NEW_TERM, CALC_COMPLETE};
				
	sc_signal <states> p_state, n_state; 

	SC_CTOR(controller){
		SC_METHOD (comb_S_function);
		sensitive << start << co << p_state;
		SC_METHOD (comb_O_function);
		sensitive << p_state;
		SC_THREAD (seq_function); 
		sensitive << clk.pos()<< rst;
	};

	void comb_S_function();
	void comb_O_function();
	void seq_function();
};