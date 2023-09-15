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
    if (endEffectorSubsystem->GetOutputCurrent() > ampLimit)
    {
        homePositionCommand.Schedule();
    }
}

bool AutoRetractCommand::IsFinished()
{
    return homePositionCommand.IsScheduled();
}

void AutoRetractCommand::End(bool interrupted)
{

}
