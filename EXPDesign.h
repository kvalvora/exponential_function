#include "datapath_exp_new.h"
#include "controller_exp.h"


SC_MODULE(EXP){

	sc_in <sc_logic> clk, rst, start; 
	sc_in <sc_lv<8> > x;
	sc_out < sc_lv<10>>  result; 
	sc_out <sc_logic> busy, done;

	sc_signal <sc_logic> loadExponent, rstExponent;
	sc_signal <sc_logic> loadTerm, initTerm, rstTerm;
	sc_signal <sc_logic> selTableData;
	sc_signal <sc_logic> rstResultReg, initResultReg, loadResultReg;
	sc_signal <sc_logic> enCounter, rstCounter, initCounter;
	sc_signal <sc_logic> co, memSel, rwbar;
	
	datapath* DP; 
	controller* CNTRL; 
	 

	SC_CTOR(EXP){
		DP = new datapath("Datapath"); 
			DP->x(x);
			DP->clk(clk);
			DP->rst(rst);
			DP->loadExponent(loadExponent); 
			DP->rstExponent(rstExponent); 
			DP->loadTerm(loadTerm); 
			DP->initTerm(initTerm);
			DP->rstTerm(rstTerm);
			DP->selTableData(selTableData); 
			DP->rstResultReg(rstResultReg); 
			DP->initResultReg(initResultReg);
			DP->loadResultReg(loadResultReg); 
			DP->enCounter(enCounter); 
			DP->rstCounter(rstCounter); 
			DP->initCounter(initCounter); 
			DP->result(result); 
			DP->co(co);
			DP->rwbar(rwbar);
			DP->memSel(memSel); 

		CNTRL = new controller ("Controller"); 
			CNTRL->clk(clk);
			CNTRL->rst(rst);
			CNTRL->start(start);
			CNTRL->co(co); 
			CNTRL->loadExponent(loadExponent);
			CNTRL->rstExponent(rstExponent);
			CNTRL->loadTerm(loadTerm);
			CNTRL->initTerm(initTerm);
			CNTRL->rstTerm(rstTerm);
			CNTRL->selTableData(selTableData);
			CNTRL->rstResultReg(rstResultReg);
			CNTRL->initResultReg(initResultReg);
			CNTRL->loadResultReg(loadResultReg);
			CNTRL->enCounter(enCounter);
			CNTRL->rstCounter(rstCounter);
			CNTRL->initCounter(initCounter);
			CNTRL->busy(busy);
			CNTRL->done(done);
			CNTRL->rwbar(rwbar); 
			CNTRL->memSel(memSel); 
		}
};