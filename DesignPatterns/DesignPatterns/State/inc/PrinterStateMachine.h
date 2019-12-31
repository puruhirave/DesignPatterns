/**********************************************************/
/* File   : PrinterStateMachine.h     				      */
/* Purpose: PrinterStateMachine class header file  		  */
/* Author : Purushottam Hirave(2019)                      */
/**********************************************************/
#pragma once
#include "stdafx.h"
#include "PrinterDef.h"
#include "PrinterStates.h"

//Printer state event CALLBACK.
typedef std::function<void(PrinterStateMachine*, int)> StateEvent;
//PrinterState shared pointer type.
typedef shared_ptr<PrinterState> PrinterStatePtr;

//Keeps State event transition data(handler, next state).
struct StateTransitionEvtData
{
	StateEvent    event_handler;
	PRINTER_STATE next_state;
};

//Shared state pointers array holding each state instance.
struct PrinterStateArray
{
	PrinterStatePtr OffStatePtr{ nullptr };
	PrinterStatePtr OperationStatePtr{ nullptr };
	PrinterStatePtr DownloadStatePtr{nullptr };
	PrinterStatePtr ErrorStatePtr{ nullptr };
};

class PrinterStateMachine
{
public:
	PrinterStateMachine();
	~PrinterStateMachine();
	//Handle printer event received from printer manager.
	void HandleEvent(PrinterEvent evt);
	//Change new_state and old_state, called by each State on transition.
	void ChangeState(PrinterStatePtr new_state);
	//Get current printer state name.
	PRINTER_STATE GetCurrentState();

	//Callback event called from State during transition.
	void ProcessStateEvent(PrinterEvent event);

	//Event Handlers
	void ProcessPowerOnEvent(int evt_data);
	void ProcessPowerOffEvent(int evt_data);
	void ProcessPrintCmdEvent(int evt_data);
	void ProcessPrintProgressEvent(int evt_data);
	void ProcessPrintErrorEvent(int evt_data);
	void ProcessPrintErrorClearEvent(int evt_data);
	void ProcessFwDownloadCmdEvent(int evt_data);
	void ProcessFwDownloadProgressEvent(int evt_data);
	void ProcessFwDownloadErrorEvent(int evt_data);
	void ProcessFwDownloadErrorClearEvent(int evt_data);
	void ProcessPrinterResetEvent(int evt_data);

	//Map of PrinterEvent to StateTransitionEventData
	typedef map<PrinterEvent, StateTransitionEvtData> EventTransitionMap;
	//Map of Printer event to EventTransitionMap 
	typedef map<shared_ptr<PrinterState>, EventTransitionMap> StateMachineMap;
	StateMachineMap m_stateMachieMap;

private:
	PrinterStatePtr m_curr_state;
	PrinterStatePtr m_old_state;
	//Register all state transition events for corrospondig PrinterState into StateMachineMap.
	PrinterStatePtr RegisterStateTransitions(PRINTER_STATE printer_state);
	PrinterStatePtr GetStatePtr(PRINTER_STATE stateName);
	string GetStateEvtStr(PrinterEvent stateEvt);
	string GetStateStr(PRINTER_STATE printer_state);
};