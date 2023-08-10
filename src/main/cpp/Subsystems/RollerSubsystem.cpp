#include "Subsystems/RollerSubsystem.h"

RollerSubsystem::RollerSubsystem() : COMETS3357::Subsystem<RollerSubsystemState>("RollerSubsystem")
{

}

void RollerSubsystem::Initialize()
{

}

void RollerSubsystem::Periodic()
{
    
}

void RollerSubsystem::SetPower(double power)
{
    roller.SetPower(power);
}