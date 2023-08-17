#include "Subsystems/ElbowSubsystem.h"

ElbowSubsystem::ElbowSubsystem() : COMETS3357::Subsystem<ElbowState>("ElbowSubsystem")
{

}

void ElbowSubsystem::Initialize()
{

}

void ElbowSubsystem::Periodic()
{
    
}

void ElbowSubsystem::SetPercent(double percent)
{
    elbowMotor.SetPower(percent);
}

void ElbowSubsystem::SetPercent(std::string percent)
{
elbowMotor.SetPower(percent);

}










