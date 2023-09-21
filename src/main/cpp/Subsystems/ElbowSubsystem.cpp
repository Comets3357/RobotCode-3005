#include "Subsystems/ElbowSubsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"

ElbowSubsystem::ElbowSubsystem() : COMETS3357::Subsystem<ElbowState>("ElbowSubsystem")
{
    elbowMotor.SetFeedForward([](double){
        return 0;
    });
}

void ElbowSubsystem::Initialize()
{
    elbowFollow.motor.Follow(elbowMotor.motor);
    elbowFollow.motor.BurnFlash();
}

void ElbowSubsystem::Periodic()
{
    elbowMotor.Periodic();
    elbowFollow.Periodic();

    frc::SmartDashboard::PutNumber("ERK2", elbowMotor.GetAbsolutePosition());
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
    elbowMotor.SetPower(percent * 0.15);
    
}

double ElbowSubsystem::GetPosition()
{
    return elbowMotor.GetPosition();
}








