#include "Subsystems/ExtenderSubsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"

ExtenderSubsystem::ExtenderSubsystem() : COMETS3357::Subsystem<ExtenderState>("ExtenderSubsystem")
{
    extendermotor.SetFeedForward([](double a){return 0;});
}

void ExtenderSubsystem::Initialize()
{

}

void ExtenderSubsystem::Periodic()
{

}

void ExtenderSubsystem::SetPercent(double percent)
{
    extendermotor.SetPower(percent * 0.1);
}

void ExtenderSubsystem::SetPosition(double position)
{
    extendermotor.SetPosition(position);
}

void ExtenderSubsystem::SetPosition(std::string position)
{
    extendermotor.SetPosition(position);
}

double ExtenderSubsystem::GetPosition()
{
    return extendermotor.GetPosition();
}
