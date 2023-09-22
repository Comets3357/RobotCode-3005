#include "Commands/EjectCommand.h"



EjectCommand::EjectCommand(EndEffectorSubsystem* endEffectorSub, bool on)
{
    enabled = on;
    endEffectorSubsystem = endEffectorSub;
}

void EjectCommand::Initialize()
{
    if (enabled)
    {
        endEffectorSubsystem->SetPercent(-1);
    }
    else
    {
        endEffectorSubsystem->SetPercent(0);
    }
    
}

void EjectCommand::Execute()
{

}

bool EjectCommand::IsFinished()
{
    return true;
}

void EjectCommand::End(bool interrupted)
{

}