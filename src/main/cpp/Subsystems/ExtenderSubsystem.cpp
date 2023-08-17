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

void ExtenderSubsystem::SetPercent(std::string Percent)
{
    extendermotor.SetPower(Percent);
}