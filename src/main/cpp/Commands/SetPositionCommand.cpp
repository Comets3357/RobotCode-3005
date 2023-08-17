#include "Commands/SetPositionCommand.h"


SetPositionCommand::SetPositionCommand(
    ElbowSubsystem* elbowSubsystem, 
    ExtenderSubsystem* extenderSubsystem, 
    WristSubsystem* wristSubsystem, 
    std::string elbowPosition, 
    std::string extenderPosition, 
    std::string wristPosition
    ) : 
    elbowSub{elbowSubsystem}, 
    extenderSub{extenderSubsystem},
    wristSub{wristSubsystem},
    elbowPos{elbowPosition},
    extenderPos{extenderPosition},
    wristPos{wristPosition}
{
    
}

void SetPositionCommand::Initialize()
{
    elbowSub->SetPosition(elbowPos);
    extenderSub->SetPosition(extenderPos);
    wristSub->SetPosition(wristPos);
    
}

void SetPositionCommand::Execute()
{

}

bool SetPositionCommand::IsFinished()
{
    return true;
}

void SetPositionCommand::End(bool interrupted)
{

}