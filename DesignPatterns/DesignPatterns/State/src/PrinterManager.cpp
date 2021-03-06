/*************************************************************************/
/* File   : PrinterManager.cpp     				         */
/* Purpose: PrinterManager class posts printer events received from      */
/*	    printer to State Machine for handling printer state.         */
/*          transition.                                                  */
/* Author : Purushottam Hirave(2019)                                     */
/*************************************************************************/
#pragma once
#include "stdafx.h"
#include "PrinterManager.h"

PrinterManager::PrinterManager() 
    : m_curr_state(PRINTER_STATE::OFF)
{
    cout << "Printer Initial state = OFF " << endl;
}

PrinterManager::PrinterManager(PRINTER_STATE initState)
    : m_curr_state(initState)
{
}

PrinterManager::~PrinterManager() 
{
}

//Post printe event to state machine
void PrinterManager::PostEvent(PrinterEvent evt)
{
    cout << "PrinterManager::PostEvent => " << (int)evt << endl;
    m_PrinterStateMachine.HandleEvent(evt);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
}

PRINTER_STATE PrinterManager::GetCurrentState()
{
    return m_curr_state;
}
