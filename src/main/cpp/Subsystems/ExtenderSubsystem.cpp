#include "Subsystems/ExtenderSubsystem.h"

ExtenderSubsystem::ExtenderSubsystem() : COMETS3357::Subsystem<ExtenderState>("ExtenderSubsystem")
{

}

void ExtenderSubsystem::Initialize()
{

}

void ExtenderSubsystem::Periodic()
{

}

void ExtenderSubsystem::SetPercent(double Percent)
{
    extendermotor.SetPower(Percent);
}

void ExtenderSubsystem::SetPosition(double position)
{
    extendermotor.SetPosition(position);
}

void ExtenderSubsystem::SetPosition(std::string position)
{
    extendermotor.SetPosition(position);
}