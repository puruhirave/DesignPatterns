/*********************************************************************/
/* File   : PrinterStateMachine.cpp     		             */
/* Purpose: PrinterStateMachine class delegates all printer events   */
/*          to corrosponding Printer State which handles state       */
/*          transition.  		         	    	     */
/* Author : Purushottam Hirave(2019)                                 */
/*********************************************************************/
#pragma once
#include "stdafx.h"
#include "PrinterStates.h"
#include "PrinterStateMachine.h"

static PrinterStateArray SharedStatePtrs;

PrinterStateMachine::PrinterStateMachine()
{
    //Register all printer states to state machine map.
    m_curr_state = RegisterStateTransitions(PRINTER_STATE::OFF);
    RegisterStateTransitions(PRINTER_STATE::OPERATION);
    RegisterStateTransitions(PRINTER_STATE::FW_DOWNLOAD);
    RegisterStateTransitions(PRINTER_STATE::ERROR);
    m_old_state = m_curr_state;
}

PrinterStateMachine::~PrinterStateMachine()
{
    m_stateMachieMap.clear();
}

//Get Shared printer state pointer corrosponding state name
PrinterStatePtr PrinterStateMachine::GetStatePtr(PRINTER_STATE stateName)
{
    PrinterStatePtr state_ptr = nullptr;
    if(stateName == PRINTER_STATE::OFF)	state_ptr = SharedStatePtrs.OffStatePtr; 
    else if(stateName == PRINTER_STATE::OPERATION) state_ptr = SharedStatePtrs.OperationStatePtr;
    else if(stateName == PRINTER_STATE::FW_DOWNLOAD) state_ptr = SharedStatePtrs.DownloadStatePtr;
    else if(stateName == PRINTER_STATE::ERROR) state_ptr = SharedStatePtrs.ErrorStatePtr;

    return state_ptr;
}

//1. Create EventTransitionMap for specific State and register corrosponding <StateEvent,NextState> pair to the Map.
//2. Create Shared StatePtr if already not created.
//3. Add pair <StatePtr, EventTransitionMap> into StateMachineMap.
PrinterStatePtr PrinterStateMachine::RegisterStateTransitions(PRINTER_STATE printer_state)
{
    EventTransitionMap transitionMap;
    PrinterStatePtr statePtr = nullptr;

    switch (printer_state)
    {
        case PRINTER_STATE::OFF : {
            statePtr = (SharedStatePtrs.OffStatePtr) ? SharedStatePtrs.OffStatePtr :
                        SharedStatePtrs.OffStatePtr = make_shared<PrinterOffState>();
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PowerOn, PrinterStateMachine::ProcessPowerOnEvent, PRINTER_STATE::OPERATION)
            m_stateMachieMap[statePtr] = transitionMap;
            break;
        }
        case PRINTER_STATE::OPERATION : {
            statePtr = (SharedStatePtrs.OperationStatePtr) ? SharedStatePtrs.OperationStatePtr :
                        SharedStatePtrs.OperationStatePtr = make_shared<PrinterOperationState>();
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrintCmd,
                                      PrinterStateMachine::ProcessPrintCmdEvent, PRINTER_STATE::OPERATION)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrintStarted,
                                      PrinterStateMachine::ProcessPrintProgressEvent, PRINTER_STATE::OPERATION)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrintComplete,
                                      PrinterStateMachine::ProcessPrintProgressEvent, PRINTER_STATE::OPERATION)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterError,
                                      PrinterStateMachine::ProcessPrintErrorEvent, PRINTER_STATE::ERROR)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterFWDownloadCmd,
                                      PrinterStateMachine::ProcessFwDownloadCmdEvent, PRINTER_STATE::FW_DOWNLOAD)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PowerOff, 
                                      PrinterStateMachine::ProcessPowerOffEvent, PRINTER_STATE::OFF)
            m_stateMachieMap[statePtr] = transitionMap;
            break;
        }
        case PRINTER_STATE::FW_DOWNLOAD : {
            statePtr = (SharedStatePtrs.DownloadStatePtr) ? SharedStatePtrs.DownloadStatePtr :
                        SharedStatePtrs.DownloadStatePtr = make_shared<PrinterFwDownloadState>();

            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterFWDownloadStart, 
                                      PrinterStateMachine::ProcessFwDownloadProgressEvent, PRINTER_STATE::FW_DOWNLOAD)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterFWDownloadComplete, 
                                      PrinterStateMachine::ProcessFwDownloadProgressEvent, PRINTER_STATE::FW_DOWNLOAD)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterReset, 
                                      PrinterStateMachine::ProcessPrinterResetEvent, PRINTER_STATE::OPERATION)
            m_stateMachieMap[statePtr] = transitionMap;
            break;
        }
        case PRINTER_STATE::ERROR : {
            statePtr = (SharedStatePtrs.ErrorStatePtr) ? SharedStatePtrs.ErrorStatePtr :
                        SharedStatePtrs.ErrorStatePtr = make_shared<PrinterErrorState>();
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterErrorClear, 
                                      PrinterStateMachine::ProcessPrintErrorClearEvent, PRINTER_STATE::OPERATION)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PrinterFWDownloadErrorClear,
                                      PrinterStateMachine::ProcessPrintErrorClearEvent, PRINTER_STATE::FW_DOWNLOAD)
            REGISTER_STATE_TRANSITION(transitionMap, PrinterEvent::PowerOff,
                                      PrinterStateMachine::ProcessPowerOffEvent, PRINTER_STATE::OFF)
            m_stateMachieMap[statePtr] = transitionMap;
            break;
        }
        default: {
            break;
        }
    }

    return statePtr;
}

string PrinterStateMachine::GetStateEvtStr(PrinterEvent event)
{
    std::string str_state = "";
    if (PrinterEvent::PowerOff == event)
        str_state = "PowerOff";
    else if (PrinterEvent::PowerOn == event)
        str_state = "PowerOn";
    else if (PrinterEvent::PrintCmd == event)
        str_state = "PrintCmd";
    else if (PrinterEvent::PrintStarted == event)
        str_state = "PrintStarted";
    else if (PrinterEvent::PrintComplete == event)
        str_state = "PrintComplete";
    else if (PrinterEvent::PrinterError == event)
        str_state = "PrinterError";
    else if (PrinterEvent::PrinterFWDownloadCmd == event)
        str_state = "PrinterFWDownloadCmd";
    else if (PrinterEvent::PrinterFWDownloadComplete == event)
        str_state = "PrinterFWDownloadComplete";
    else if (PrinterEvent::PrinterFWDownloadError == event)
        str_state = "PrinterFWDownloadError";
    else if (PrinterEvent::PrinterFWDownloadErrorClear == event)
        str_state = "PrinterFWDownloadErrorClear";
    else if (PrinterEvent::PrinterReset == event)
        str_state = "PrinterReset";
    else
        str_state = "";
    return str_state.c_str();
}

string PrinterStateMachine::GetStateStr(PRINTER_STATE printer_state)
{
    string state_name = "";
    if (printer_state == PRINTER_STATE::OFF)
        state_name = "OFF";
    else if (printer_state == PRINTER_STATE::OPERATION)
        state_name = "OPERATION";
    else if (printer_state == PRINTER_STATE::FW_DOWNLOAD)
        state_name = "FW_DOWNLOAD";
    else if (printer_state == PRINTER_STATE::ERROR)
        state_name = "ERROR";

    return state_name;
}

//Get current printer state name.
PRINTER_STATE PrinterStateMachine::GetCurrentState()
{
    return m_curr_state->GetPrinterState();
}

//Process state event callback called from state instance.
void PrinterStateMachine::ProcessStateEvent(PrinterEvent event)
{
    cout << "		ProcessStateEvent : EVENT = " << (int)event << endl;
    //Find state transition map of current State from StateMachineMap.
    EventTransitionMap transitionMap = m_stateMachieMap[m_curr_state];
    //Find state transition event for corrosponding State pointer from transitionMap.
    EventTransitionMap::const_iterator itr = transitionMap.find(event);
    if (itr != transitionMap.end())
    {
        //Execute State event and change state.
        itr->second.event_handler(this, int(itr->second.next_state));
    }
    else
    {
        cout << "		!!!!! Invalid State Event = " << (int)event << endl;
    }
}

//The HandleEvent() function called from Printer manager.
void PrinterStateMachine::HandleEvent(PrinterEvent evt)
{
    cout << "	PrinterStateMachine::HandleEvent => [" << GetStateEvtStr(evt).c_str() <<"]"<< endl;
    m_curr_state->StateTransition(this, (int)evt);
}

//To change new_state and old_state called from State instance.
void PrinterStateMachine::ChangeState(PrinterStatePtr new_state)
{
    cout << "		PrinterStateMachine::ChangeState() : Old State => " << GetStateStr(m_curr_state->GetPrinterState()).c_str() << endl;
    cout << "						   : New State => " << GetStateStr(new_state->GetPrinterState()).c_str() << endl;
    m_old_state = m_curr_state;
    m_curr_state = new_state;
}

/*********************************************************/
/******* Printer State Event Handlers ********************/
/*********************************************************/
void PrinterStateMachine::ProcessPowerOnEvent(int evt_data)
{
    cout << "		PrinterStateMachine::ProcessPowerOnEvent : Printer Powered ON.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessPrintCmdEvent(int evt_data)
{
    cout << "		PrinterStateMachine::ProcessPrintCmdEvent : Print Command Received.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessPowerOffEvent(int evt_data)
{
    cout << "		PrinterStateMachine::ProcessPowerOffEvent : Printer OFF.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessPrintProgressEvent(int evt_data)
{
    cout << "		PrinterStateMachine::ProcessPrintProgressEvent .." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessPrintErrorEvent(int evt_data)
{
    cout << "		Printer Error.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessPrintErrorClearEvent(int evt_data)
{
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessFwDownloadCmdEvent(int evt_data)
{
    cout << "		Printer Firmware Download Cmd received.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessFwDownloadProgressEvent(int evt_data)
{
    cout << "		Printer Firmware Download Progress event.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessFwDownloadErrorEvent(int evt_data)
{
    cout << "		Printer Firmware Download Error received.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessFwDownloadErrorClearEvent(int evt_data)
{
    cout << "		Printer Firmware Download Err Cleared.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}
void PrinterStateMachine::ProcessPrinterResetEvent(int evt_data)
{
    cout << "		Printer Reset after Firmware Download.." << endl;
    PrinterStatePtr nextState = GetStatePtr((PRINTER_STATE)evt_data);
    ChangeState(nextState);
}

