#include "Subsystems/LEDs.h"


LEDs::LEDs() : COMETS3357::Subsystem<LEDState>("LEDs")
{
    
    while (!arduinoWorking && (attemptsToConnectToArduino < 10))
    {
        try
        {
            arduino = new frc::SerialPort(9600, frc::SerialPort::Port::kUSB);
            arduinoWorking = true;

            char value[1];

            value[0] = 'n';



            try
            {
                arduino->Write(value, 1);
            }
            catch(...)
            {
                failedTransfers++;
            }
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
    frc::SmartDashboard::PutNumber("LED", (int)code);

    char value[1];

    value[0] = code;



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