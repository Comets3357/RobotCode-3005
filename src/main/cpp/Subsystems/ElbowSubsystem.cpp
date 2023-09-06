#include "Subsystems/ElbowSubsystem.h"

ElbowSubsystem::ElbowSubsystem() : COMETS3357::Subsystem<ElbowState>("ElbowSubsystem")
{

}

void ElbowSubsystem::Initialize()
{

}

void ElbowSubsystem::Periodic()
{
    elbowMotor.Periodic();
    elbowFollow.Periodic();
}

void ElbowSubsystem::SetPosition(double position)
{
    elbowMotor.SetPosition(position);
}

void ElbowSubsystem::SetPosition(std::string position)
{
    elbowMotor.SetPosition(position);
}

void ElbowSubsystem::SetPercent(double percent)
{
    elbowMotor.SetPower(percent);
}










