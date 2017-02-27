#include "controller_exp.h"

	void controller::comb_O_function()
	{
		loadExponent = SC_LOGIC_0;
		rstExponent = SC_LOGIC_0;
		loadTerm = SC_LOGIC_0;
		initTerm = SC_LOGIC_0;
		rstTerm = SC_LOGIC_0;
		selTableData = SC_LOGIC_0;
		rstResultReg = SC_LOGIC_0;
		initResultReg = SC_LOGIC_0;
		loadResultReg = SC_LOGIC_0;
		enCounter = SC_LOGIC_0;
		rstCounter = SC_LOGIC_0;
		initCounter = SC_LOGIC_0;
		busy = SC_LOGIC_0;
		done = SC_LOGIC_0;
		rwbar = SC_LOGIC_0;
		memSel = SC_LOGIC_0;
		
		switch( p_state ){
			case INITIALIZE:
				rstExponent = SC_LOGIC_1; rstTerm  = SC_LOGIC_1;
				rstResultReg = SC_LOGIC_1; rstCounter = SC_LOGIC_1;
				break;
			case WAIT_ON_START: 
				loadExponent = SC_LOGIC_1;
				initResultReg = SC_LOGIC_1;
				initTerm = SC_LOGIC_1;
				initCounter = SC_LOGIC_1;
				enCounter = SC_LOGIC_1;
				break;
			case CALC_NEXT_TERM_1: 
				busy = SC_LOGIC_1;
				selTableData = SC_LOGIC_1;
				loadTerm = SC_LOGIC_1;
				break;
			case CALC_NEXT_TERM_2: 
				rwbar = SC_LOGIC_1;
				memSel = SC_LOGIC_1;
				selTableData = SC_LOGIC_0;
				busy = SC_LOGIC_1;
				loadTerm = SC_LOGIC_1;
				enCounter = SC_LOGIC_1;
				break;
			
			case ADD_NEW_TERM: 
				loadResultReg = SC_LOGIC_1;
				busy = SC_LOGIC_1;
				break;
			
			case CALC_COMPLETE: 
				done = SC_LOGIC_1;
				busy = SC_LOGIC_0;
				break; 
			default: 
				loadExponent = SC_LOGIC_0;
				rstExponent = SC_LOGIC_0;
				loadTerm = SC_LOGIC_0;
				rstTerm = SC_LOGIC_0;
				initTerm = SC_LOGIC_0;
				selTableData = SC_LOGIC_0;
				rstResultReg = SC_LOGIC_0;
				initResultReg = SC_LOGIC_0;
				loadResultReg = SC_LOGIC_0;
				initResultReg = SC_LOGIC_0;
				enCounter = SC_LOGIC_0;
				rstCounter = SC_LOGIC_0;
				initCounter = SC_LOGIC_0;
				busy = SC_LOGIC_0;
				done = SC_LOGIC_0;
				rwbar = SC_LOGIC_0; 
				memSel = SC_LOGIC_0;
				break;
		}
	}
	void controller::comb_S_function(){
		n_state = INITIALIZE;
		switch( p_state ){
			case INITIALIZE:
				if (start == '0')
					n_state = INITIALIZE;
				else
					n_state = WAIT_ON_START;
				
				break;
			case WAIT_ON_START: 
				if( start == '0') 
					n_state = CALC_NEXT_TERM_1;
				else
					n_state = WAIT_ON_START;
				break;
			case CALC_NEXT_TERM_1: 
				n_state = CALC_NEXT_TERM_2;
				break;
			case CALC_NEXT_TERM_2: 
				n_state = ADD_NEW_TERM;
				break;
			case ADD_NEW_TERM: 
				if( co =='0' )
					n_state = CALC_NEXT_TERM_1;
				else
					n_state = CALC_COMPLETE;
				break;
			case CALC_COMPLETE: 
				if ( start == '0')
					n_state = INITIALIZE;
				else
					n_state = WAIT_ON_START;
				break; 
			default: 
				n_state = INITIALIZE;
				break;
		}

	}

void controller::seq_function(){
	while (1){
		if (rst == '1')
			p_state = INITIALIZE;
		else if (clk.event() &&(clk =='1'))
			p_state = n_state;
		wait();
	}
}

