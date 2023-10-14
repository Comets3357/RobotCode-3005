#include "commands/PlacementCommand.h"

PlacementCommand::PlacementCommand(EndEffectorSubsystem* endEffector, SetPositionCommand &cubePosition, SetPositionCommand &conePosition, PlacementPosition placementPos) : endEffectorSubsystem{endEffector}, conePositionCommand{conePosition}, cubePositionCommand{cubePosition}, placement{placementPos}
{
    
}

void PlacementCommand::Initialize()
{
    if (endEffectorSubsystem->State()==EndEffectorSubsystemState::CONE)
    {
        conePositionCommand.Schedule();

        if (placement == HIGH_CONE)
        {
            endEffectorSubsystem->placement = HIGH_CONE;
        }
        else if (placement == MID_CONE)
        {
            endEffectorSubsystem->placement = MID_CONE;
        }
        else
        {
            endEffectorSubsystem->placement = NONE;
        }
    }
    else 
    {
        cubePositionCommand.Schedule();

        if (placement == HIGH_CONE)
        {
            endEffectorSubsystem->placement = HIGH_CUBE;
        }
        else if (placement == MID_CONE)
        {
            endEffectorSubsystem->placement = MID_CUBE;
        }
        else
        {
            endEffectorSubsystem->placement = NONE;
        }
    }
}

void PlacementCommand::Execute() 
{

}

bool PlacementCommand::IsFinished()
{
    return true;
}

void PlacementCommand::End(bool interrupted)
{

}
