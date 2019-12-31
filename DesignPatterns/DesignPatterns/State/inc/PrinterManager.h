/**********************************************************/
/* File   : PrinterManager.h     				          */
/* Purpose: PrinterManager class header file           	  */
/* Author : Purushottam Hirave(2019)                      */
/**********************************************************/
#pragma once
#include "stdafx.h"
#include "PrinterDef.h"
#include "PrinterStateMachine.h"

class PrinterManager {
public:
	PrinterManager();
	PrinterManager(PRINTER_STATE initState);
	~PrinterManager();
	void PostEvent(PrinterEvent evt);
	
private:
	PRINTER_STATE m_curr_state;
	PrinterStateMachine m_PrinterStateMachine;
	PRINTER_STATE GetCurrentState();
};