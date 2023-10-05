#pragma once

#include <frc/SerialPort.h>
#include <time.h>

#include "COMETS3357/Subsystems/Subsystem.h"

enum LEDState
{

};

class LEDs : public COMETS3357::Subsystem<LEDState>
{
public:
    LEDs();

    void Initialize() override;

    void Periodic() override;

    void SetLEDCode(char code);

    int failedTransfers = 0;

    bool arduinoWorking = false;
    int attemptsToConnectToArduino = 0;
    int colorCode;

    frc::SerialPort *arduino;
};