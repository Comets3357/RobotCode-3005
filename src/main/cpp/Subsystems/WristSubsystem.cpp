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

void WristSubsystem::SetPosition(double position)
{
    wristMotor.SetPosition(position);
}

void WristSubsystem::SetPosition(std::string position)
{
    wristMotor.SetPosition(position);
}

void WristSubsystem::SetPercent(double percent)
{
    wristMotor.SetPower(percent);
}