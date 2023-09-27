#include "Commands/EjectCommand.h"



EjectCommand::EjectCommand(EndEffectorSubsystem* endEffectorSub, bool on)
{
    enabled = on;
    endEffectorSubsystem = endEffectorSub;

    AddRequirements({endEffectorSub});
}

void EjectCommand::Initialize()
{
    if (enabled)
    {
        switch (endEffectorSubsystem->State())
            {
            case CUBE:
                endEffectorSubsystem->SetPercent(0.2);
                break;
            case CONE:
                endEffectorSubsystem->SetPercent(-0.2);
                break;
            
            default:
                break;
            }
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