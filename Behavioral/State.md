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
