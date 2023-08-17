#include "Subsystems/WristSubsystem.h"


WristSubsystem::WristSubsystem() : COMETS3357::Subsystem<WristState>("WristSubsystem")
{

}

void WristSubsystem::Initialize()
{

}

void WristSubsystem::Periodic()
{

}

void WristSubsystem::SetPercent(double percent)
{
    wristMotor.SetPower(percent);
}

void WristSubsystem::SetPercent(std::string percent)
{
    wristMotor.SetPower(percent);
}
