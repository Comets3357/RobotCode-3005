#include "Subsystems/EndEffectorSubsystem.h"

EndEffectorSubsystem::EndEffectorSubsystem() : COMETS3357::Subsystem<EndEffectorSubsystemState>("EndEffectorSubsystem")
{

}

void EndEffectorSubsystem::Initialize()
{

}

void EndEffectorSubsystem::Periodic()
{

}

void EndEffectorSubsystem::SetPercent(double percent)
{
    endEffectorMotor.SetPower(percent * 0.5);
}

void EndEffectorSubsystem::SetPercent(std::string percent)
{
    endEffectorMotor.SetPower(percent);
}

double EndEffectorSubsystem::GetOutputCurrent()
{
    return endEffectorMotor.GetOutputCurrent();
}
