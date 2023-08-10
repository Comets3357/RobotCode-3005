#include "Subsystems/ArmSubsystem.h"


ArmSubsystem::ArmSubsystem() : COMETS3357::Subsystem<ArmState>("ArmSubsystem")
{

}

void ArmSubsystem::Initialize()
{

}

void ArmSubsystem::Periodic()
{

}

void ArmSubsystem::SetPosition(double position)
{
    motor.SetPosition(position);
}