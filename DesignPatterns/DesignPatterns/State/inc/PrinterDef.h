/**********************************************************/
/* File   : PrinterDef.h     				              */
/* Purpose: Printer state machine related constants 	  */
/* Author : Purushottam Hirave(2019)                      */
/**********************************************************/
#pragma once
#include "stdafx.h"

#define REGISTER_STATE_TRANSITION(transitionMap,evt,handler,nextState) \
		transitionMap[evt] = { std::bind(&handler, this, int(nextState)), nextState }; 

enum class PrinterEvent : int
{
	PowerOn = 0,
	PowerOff,
	PrintCmd,
	PrintStarted,
	PrintComplete,
	PrinterError,
	PrinterErrorClear,
	PrinterFWDownloadCmd,
	PrinterFWDownloadStart,
	PrinterFWDownloadComplete,
	PrinterFWDownloadError,
	PrinterFWDownloadErrorClear,
	PrinterReset
};

struct StateEventData
{
	int evt_data;
	int transition_state;
};

