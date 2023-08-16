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

void EndEffectorSubsystem::SetPosition(double position)
{
    endeffectormotor.SetPosition(position);
}

void EndEffectorSubsystem::SetPosition(std::string position)
{
    endeffectormotor.SetPosition(position);

}

