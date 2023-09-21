#include "Subsystems/WristSubsystem.h"


WristSubsystem::WristSubsystem() : COMETS3357::Subsystem<WristState>("WristSubsystem")
{
    wristMotor.SetFeedForward([](double){
        return 0;
    })
}

void WristSubsystem::Initialize()
{

}

void WristSubsystem::Periodic()
{

}

void WristSubsystem::SetPosition(double position)
{
    wristMotor.SetPosition(position * 0.05);
}

void WristSubsystem::SetPosition(std::string position)
{
    wristMotor.SetPosition(position);
}

void WristSubsystem::SetPercent(double percent)
{
    wristMotor.SetPower(percent);
}

double WristSubsystem::GetPosition()
{
    return wristMotor.GetPosition();
}