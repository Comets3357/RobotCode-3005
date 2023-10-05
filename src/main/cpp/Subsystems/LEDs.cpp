#include "Subsystems/LEDs.h"


LEDs::LEDs() : COMETS3357::Subsystem<LEDState>("LEDs")
{
    while (!arduinoWorking && (attemptsToConnectToArduino < 10))
    {
        try
        {
            arduino = new frc::SerialPort(9600, frc::SerialPort::Port::kUSB);
            arduinoWorking = true;
        }
        catch(...)
        {
            arduinoWorking = false;
            attemptsToConnectToArduino++;
        }
        
    }
}

void LEDs::Initialize()
{
    
}

void LEDs::SetLEDCode(char code)
{
    char colorCode;
    char value[1];

    colorCode = code;

    try
    {
        arduino->Write(value, 1);
    }
    catch(...)
    {
        failedTransfers++;
    }
}

void LEDs::Periodic()
{

}