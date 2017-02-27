// systemC
#ifndef DE_H
#define DE_H

#include <systemc.h>
#include "partsLibrary.h"
#include "Register.h"
#include "Adder.h"
#include "Mult.h"

SC_MODULE(datapath){
	
	// Port Declaration
	sc_in <sc_logic> clk, rst, rwbar, memSel, selTableData;
	sc_in <sc_logic> loadExponent, rstExponent;
	sc_in <sc_logic> loadTerm, initTerm, rstTerm;
	sc_in <sc_logic> rstResultReg, initResultReg, loadResultReg;
	sc_in <sc_logic> enCounter, rstCounter, initCounter;
	sc_in <sc_lv<8>> x;
	sc_out <sc_logic> co; 
	sc_out < sc_lv<10>> result; 
	
	// Signal Declaration
	sc_signal <sc_lv<8>> exponent, exponentInput;
	sc_signal <sc_lv<8>> term, termInput;
	sc_signal <sc_lv<10>> resultInput;
	sc_signal <sc_lv<10>> addUpperInput;
	sc_signal <sc_lv<10>> addResult;
	sc_signal <sc_lv<8>> multUpperInput;
	sc_signal <sc_lv<16>> multResult;
	sc_signal <sc_lv<8>> tableData;
	sc_signal <sc_lv<8> > memDatabus;
	sc_signal <sc_lv<4> > countValue, initialCount;
	sc_signal <sc_logic > enableExponent, enableTermReg, enableResultReg;
	
	// Instantiation 
	dRegisterRaE* expReg;
	dRegisterRaE* termReg;
	Dregister<10>* resultReg;
	Adder <10>* Add;
	Mult<8>* Mult1;
    octalMux2to1* M1;
	Memory<4,8>* fractionsMemory;
	uCounterRaEL* indexCounter;
	
	SC_CTOR(datapath){
		
		initialCount = sc_lv<4>("0001");
		
		expReg = new dRegisterRaE("exponent_Register");  
			expReg->clk(clk);
			expReg->rst(rst);
			expReg->cen(enableExponent);
			expReg->regin(exponentInput);
			expReg->regout(exponent);
		

		termReg = new dRegisterRaE ("Term_Register");
			termReg->clk(clk); 
			termReg->rst(rst); 
			termReg->cen(enableTermReg); 
			termReg->regin(termInput);
			termReg->regout(term); // dorost shod

		M1 = new octalMux2to1("Multiplexer");
		(*M1) (selTableData, tableData, exponent, multUpperInput);

		resultReg = new Dregister<10>("Result_Register");
			resultReg->clk(clk); 
			resultReg->rst(rst);
			resultReg->cen(enableResultReg);
			resultReg->regin(resultInput); 
			resultReg->regout(result);

		indexCounter = new uCounterRaEL ("index_counter");
			indexCounter->rst(rstCounter); 
			indexCounter->clk(clk); 
			indexCounter->cen (enCounter); 
			indexCounter->pld(initCounter);
			indexCounter->parin(initialCount); 
			indexCounter->cntout(countValue);

		fractionsMemory = new Memory <4,8> ("fractionsMemory");
			fractionsMemory->addr(countValue);
			fractionsMemory->datain(memDatabus);
			fractionsMemory->dataout(tableData); 
			fractionsMemory->cs(memSel);
			fractionsMemory->rwbar(rwbar) ;

		Mult1 = new Mult<8> ("Multiplier");
			Mult1-> in1(term);
			Mult1->in2(multUpperInput); 
			Mult1->out(multResult);

		Add = new Adder<10>("adder");
			Add->in1(addUpperInput);
			Add->in2(result);
			
			Add->out(addResult);
			
		//--Process Declaration--
		SC_METHOD(datapath_assign);
		sensitive << loadExponent << rstExponent 
				  << loadTerm << initTerm << rstTerm << term 
				  << loadResultReg << initResultReg << rstResultReg
				  << multResult << addResult
				  << countValue; 
	}

	// Function declaration
	void datapath_assign(){
		
		enableExponent = (loadExponent.read() | rstExponent.read());
		exponentInput =	(loadExponent.read() == '1') ? x.read() :
					(rstExponent.read() == '1') ? "00000000" : "XXXXXXXX";

		if ( sc_uint<4> (countValue.read()) < 8)
			co = SC_LOGIC_0; 
		else
			co = SC_LOGIC_1;
		
		sc_lv<8> temp;
		temp = (multResult.read().range(15, 8));
		termInput = ((loadTerm.read() == '1') ? temp :
					(initTerm.read() == '1') ? "11111111" :
					(rstTerm.read() =='1')? "00000000" : "XXXXXXXX");
		enableTermReg = (loadTerm.read() | initTerm.read()  | rstTerm.read() );

		//
		addUpperInput = (sc_lv<2>("00"), term.read());
		
		//
		resultInput = (	(loadResultReg.read() == '1')? addResult.read() :
					(initResultReg.read() == '1')? "0100000000" :
					(rstResultReg.read() == '1') ? "0000000000" : "XXXXXXXXXX");
		
		enableResultReg = (loadResultReg.read() | initResultReg.read() | rstResultReg.read());
	}
};

#endif


