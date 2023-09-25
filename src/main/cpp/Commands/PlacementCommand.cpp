#include "commands/PlacementCommand.h"

PlacementCommand::PlacementCommand(EndEffectorSubsystem* endEffector, SetPositionCommand &cubePosition, SetPositionCommand &conePosition) : endEffectorSubsystem{endEffector}, conePositionCommand{conePosition}, cubePositionCommand{cubePosition}
{
    
}

void PlacementCommand::Initialize()
{
    if (endEffectorSubsystem->State()==EndEffectorSubsystemState::CONE)
    {
        conePositionCommand.Schedule();
    }
    else 
    {
        cubePositionCommand.Schedule();
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
