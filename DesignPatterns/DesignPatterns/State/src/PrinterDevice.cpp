// PrinterDevice.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "PrinterManager.h"

int main()
{
    cout << "...Printer Device started..." << endl;
    PrinterManager printerMgr(PRINTER_STATE::OFF);
    printerMgr.PostEvent(PrinterEvent::PowerOn);
    printerMgr.PostEvent(PrinterEvent::PrintCmd);
    printerMgr.PostEvent(PrinterEvent::PrintStarted);
    printerMgr.PostEvent(PrinterEvent::PrintComplete);
    printerMgr.PostEvent(PrinterEvent::PrinterFWDownloadCmd);
    printerMgr.PostEvent(PrinterEvent::PrinterFWDownloadComplete);
    printerMgr.PostEvent(PrinterEvent::PrinterReset);
    printerMgr.PostEvent(PrinterEvent::PowerOff);
    return 0;
}
