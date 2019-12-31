## State
* Category: Behavioral
* Intent:  State is a behavioral design pattern that lets an object alter its behavior when its internal state changes.
 
The state pattern solves following state specific problems:

An object should change its behavior when its internal state changes.
State-specific behavior should be defined independently by adding new states and it should not affect the behavior of existing states.
![StatePattern](https://user-images.githubusercontent.com/6056609/71622284-ae0b0e80-2bfa-11ea-9ef4-acaabdad4279.png)

The Client interacts with Context object which keeps reference to current state. The Context object delegates to current State for state-specific behavior change. State defines an interface for performing state-specific behavior of Context object.

Following real-life example shows Printer state machine,

## Printer State Machine
The Printer device runs its own state machine with different states. The client sends different commands like print request, firmware update to Printer. On receiving commands from client the Printer's State Machine delegates to specific 'PrinterState' to handle state-specific behavior and State transition.
![PrinterStates2](https://user-images.githubusercontent.com/6056609/71623008-941ffa80-2bff-11ea-9a37-f39aeb91343e.png)

**Printer States:**
* **OFF:** Initially the Printer is in OFF state so the initial state of StateMachine is OFF.
* **OPERATION:** When Printer is powered on the PowerON event is handled by State Machine to Printer make operational from OFF state to OPERATION state.
The Printer is operational to receive printer commands like Print Cmd, Firmware Download Cmd.
The State Machine processes Print request with different events like PrintRequest, PrintStarted, PrintComplete events. The State transition for all Print events is OPERATION State itself.
* **FW_DOWNLOAD:** During 'OPERATION' state if Printer receives Firmware Download command, then State Machine delegates to OPERATION state for State transition to FW_DOWNLOAD state. After completing Firmware download successfully, 'Reset Printer' event resumes Printer from FW_DOWNLOAD state to OPERATION state.
* **ERROR:** During Print Cmd or Firmware Download Cmd if any error occurs then Printer goes to ERROR state. After Error clear event or FwDownloadError clear event the State resumes to previous State like OPERATION or FW_DOWNLOAD.

## Printer State Machine Design:
![PrinterStateMachClasses](https://user-images.githubusercontent.com/6056609/71623438-9cc60000-2c02-11ea-91cb-4db9cfe4f698.png)

Printer State Machine classes and its source code described below,
* **PrinterManager:** The PrinterManager creates PrinterStateMachine object. It receives client request and posts corrosponding events to PrinterStateMachine instance.
* **PrinterStateMachine:** This class acts as Context object to handle printer events. It delegates to PrinterState object to handle state-specific behaviour. This class implements _HandleEvent(PrinterEvent evt)_ method called by client to handle printer event.

To handle State transition events it create 2 different Maps,
```C++
//Keeps State event transition data.
struct StateTransitionEvtData
{
	StateEvent    event_handler;
	PRINTER_STATE next_state;
};

//Map of PrinterEvent to StateTransitionEventData
typedef map<PrinterEvent, StateTransitionEvtData> EventTransitionMap;
//Map of Printer event to EventTransitionMap 
typedef map<shared_ptr<PrinterState>, EventTransitionMap> StateMachineMap;
StateMachineMap m_stateMachieMap;
```

* **PrinterState:** The PrinterState is abstract class to handle Printer states. Following derived States implements its PrinterState functionality.\
_PrinterOffState_,
_PrinterOperationState_,
_PrinterFwDownloadState_,
_PrinterErrorState_

Each state implements _StateTransition(Context*)_ method which is called by PrinterStateMachine during HandleEvent() to handle State transition. It calls the Callback method _ProcessStateEvent(Context*, PrinetEvent evt)_ to process registered event handler and chages current state depending on event.

* Execution view of PrinterStateMachine demo
![ExecuteStateMach](https://user-images.githubusercontent.com/6056609/71624040-891c9880-2c06-11ea-9e6f-bed5d405aea3.png)

* Link to source code: https://github.com/puruhirave/DesignPatterns/tree/master/DesignPatterns/DesignPatterns
