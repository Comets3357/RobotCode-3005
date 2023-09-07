#include "Subsystems/ExtenderSubsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"

ExtenderSubsystem::ExtenderSubsystem() : COMETS3357::Subsystem<ExtenderState>("ExtenderSubsystem")
{

}

void ExtenderSubsystem::Initialize()
{

}

void ExtenderSubsystem::Periodic()
{

}

void ExtenderSubsystem::SetPercent(double percent)
{
    extendermotor.SetPower(percent * 0.5);
    frc::SmartDashboard::PutNumber("ERK", percent);
}

void ExtenderSubsystem::SetPosition(double position)
{
    extendermotor.SetPosition(position);
}

void ExtenderSubsystem::SetPosition(std::string position)
{
    extendermotor.SetPosition(position);
}