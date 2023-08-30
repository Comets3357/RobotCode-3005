#include "Subsystems/EndEffectorSubsystem.h"

EndEffectorSubsystem::EndEffectorSubsystem() : COMETS3357::Subsystem<EndEffectorSubsystemState>("EndEffectorSubsystem")
{

}

void EndEffectorSubsystem::Initialize()
{

}

void EndEffectorSubsystem::Periodic()
{
    if (endEffectorMotor.GetOutputCurrent() > 0)
        status = WITH_GAMEPIECE;
    else
        status = WITHOUT_GAMEPIECE;
}

void EndEffectorSubsystem::SetPercent(double percent)
{
    endEffectorMotor.SetPower(percent);
}

void EndEffectorSubsystem::SetPercent(std::string percent)
{
    endEffectorMotor.SetPower(percent);
}

