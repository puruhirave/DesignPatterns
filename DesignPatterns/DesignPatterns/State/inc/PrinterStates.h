#pragma once

class PrinterStateMachine;
typedef int StateEVT;

enum class PRINTER_STATE : int
{
	OFF = 0,
	OPERATION,
	FW_DOWNLOAD,
	ERROR
};

class PrinterState
{
public:
	PrinterState();
	~PrinterState();
	virtual void StateTransition(PrinterStateMachine *context, int state_evt) = 0;
	void SetPrinterState(PRINTER_STATE printer_state);
	PRINTER_STATE GetPrinterState() const;
private:
	PRINTER_STATE m_printer_state;
};

class PrinterOffState : public PrinterState
{
public:
	PrinterOffState();
	~PrinterOffState();
	void StateTransition(PrinterStateMachine *context, int state_evt);
};

class PrinterOperationState : public PrinterState
{
public:
	PrinterOperationState();
	~PrinterOperationState();
	void StateTransition(PrinterStateMachine *context, int state_evt);
};

class PrinterFwDownloadState : public PrinterState
{
public:
	PrinterFwDownloadState();
	~PrinterFwDownloadState();
	void StateTransition(PrinterStateMachine *context, int state_evt);
};

class PrinterErrorState : public PrinterState
{
public:
	PrinterErrorState();
	~PrinterErrorState();
	void StateTransition(PrinterStateMachine *context, int state_evt);
};
