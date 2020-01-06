/******************************************************************/
/* File   : PrinterStates.cpp     			        	          */
/* Purpose: PrinterState abstract class definition and concrete   */
/*          states implementation derived from PrinterState.      */
/* Author : Purushottam Hirave(2019)                              */
/******************************************************************/
#pragma once
#include "stdafx.h"
#include "PrinterStates.h"
#include "PrinterStateMachine.h"

PrinterState::PrinterState() : m_printer_state(PRINTER_STATE::OFF)
{
}
PrinterState::~PrinterState()
{
}
void PrinterState::SetPrinterState(PRINTER_STATE printer_state)
{
    m_printer_state = printer_state;
}
PRINTER_STATE PrinterState::GetPrinterState() const
{
    return m_printer_state;
}

//OFF state
PrinterOffState::PrinterOffState()
{
    SetPrinterState(PRINTER_STATE::OFF);
}
PrinterOffState::~PrinterOffState()
{
}
void PrinterOffState::StateTransition(PrinterStateMachine *context, int state_evt)
{
    cout << "		PrinterOffState::StateTransition : state_event = " << state_evt << endl;
    context->ProcessStateEvent((PrinterEvent)state_evt);
}

//OPERATION state
PrinterOperationState::PrinterOperationState()
{
    SetPrinterState(PRINTER_STATE::OPERATION);
}
PrinterOperationState::~PrinterOperationState()
{
}
void PrinterOperationState::StateTransition(PrinterStateMachine *context, int state_evt)
{
    cout << "		PrinterOperationState::StateTransition : state_event = " << state_evt << endl;
    context->ProcessStateEvent((PrinterEvent)state_evt);
}

//FW_DOWNLOAD state
PrinterFwDownloadState::PrinterFwDownloadState()
{
    SetPrinterState(PRINTER_STATE::FW_DOWNLOAD);
}
PrinterFwDownloadState::~PrinterFwDownloadState()
{
}
void PrinterFwDownloadState::StateTransition(PrinterStateMachine *context, int state_evt)
{
    cout << "		PrinterFwDownloadState::StateTransition : state_event = " << state_evt << endl;
    context->ProcessStateEvent((PrinterEvent)state_evt);
}

//ERROR state
PrinterErrorState::PrinterErrorState()
{
    SetPrinterState(PRINTER_STATE::ERROR);
}
PrinterErrorState::~PrinterErrorState()
{
}
void PrinterErrorState::StateTransition(PrinterStateMachine *context, int state_evt)
{
    cout << "		PrinterErrorState::StateTransition : state_event = " << state_evt << endl;
    context->ProcessStateEvent((PrinterEvent)state_evt);
}
