#include "Subsystems/WristSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>


WristSubsystem::WristSubsystem() : COMETS3357::Subsystem("WristSubsystem")
{
    wristMotor.SetFeedForward([](double a){return 0;});
}

void WristSubsystem::Initialize()
{

}

void WristSubsystem::Periodic()
{
    wristMotor.Periodic();

    frc::SmartDashboard::PutNumber("WristAbsolute", wristMotor.GetAbsolutePosition());
    frc::SmartDashboard::PutNumber("WristRelative", wristMotor.GetRelativePosition());
}

void WristSubsystem::SetPosition(double position)
{
    wristMotor.SetPosition(position );
}

void WristSubsystem::SetPosition(std::string position)
{
    wristMotor.SetPosition(position);
}

void WristSubsystem::SetPercent(double percent)
{
    wristMotor.SetPower(percent * 0.05);
}

double WristSubsystem::GetPosition()
{
    return wristMotor.GetPosition();
}