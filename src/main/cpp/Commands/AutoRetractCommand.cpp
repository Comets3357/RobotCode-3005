#include "Commands/AutoRetractCommand.h"

AutoRetractCommand::AutoRetractCommand(SetPositionCommand &targetPosition, SetPositionCommand &homePosition, EndEffectorSubsystem* endEffector, double amps) : targetPositionCommand{targetPosition}, homePositionCommand{homePosition}, endEffectorSubsystem{endEffector}, ampLimit{amps}
{

}

void AutoRetractCommand::Initialize()
{
    targetPositionCommand.Schedule();
}

void AutoRetractCommand::Execute()
{
    // if (endEffectorSubsystem->GetOutputCurrent() > 50)
    // {
    //     homePositionCommand.Schedule();

        
    // }
}

bool AutoRetractCommand::IsFinished()
{
    return true;
}

void AutoRetractCommand::End(bool interrupted)
{

}
