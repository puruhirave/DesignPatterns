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
* **OPERATION:** When Printer is powered on the PowerON event is handled by State Machine to turn Printer OFF state to OPERATION state.
The Printer is operational to receive printer commands like Print Cmd, Firmware Download Cmd.
The Printer processes Print request with different events like PrintRequest, PrintStarted, PrintComplete events. The current state for Print events is OPERATION itself.
* **FW_DOWNLOAD:** During 'OPERATION' state the if Printer receives Firmware Download command, then State Machine delegates to OPERATION state for State transition to FW_DOWNLOAD state. After completing Firmware download successfully, Rest Printer event resume Printer to OPERATION state.
* **ERROR:** During Print Cmd or Firmware Download Cmd if any error occurs then Printer goes to ERROR state. After Error clear event or FwDownloadError clear event the State resumes to previous State like OPERATION or FW_DOWNLOAD.

## Printer State Machine Design:
