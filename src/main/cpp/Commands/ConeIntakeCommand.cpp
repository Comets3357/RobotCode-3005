#include "Commands/ConeIntakeCommand.h"


ConeIntakeCommand::ConeIntakeCommand(
    ElbowSubsystem* elbowSubsystem, 
    ExtenderSubsystem* extenderSubsystem, 
    WristSubsystem* wristSubsystem,
    EndEffectorSubsystem* endEffectorSubsystem,
    std::string elbowPosition, 
    std::string extenderPosition, 
    std::string wristPosition,
    std::string endEffectorPosition
    ) : 
    elbowSub{elbowSubsystem}, 
    extenderSub{extenderSubsystem},
    wristSub{wristSubsystem},
    endEffectorSub{endEffectorSubsystem},
    elbowPos{elbowPosition},
    extenderPos{extenderPosition},
    wristPos{wristPosition},
    endEffectorPos{endEffectorPosition}
{
    
}

void ConeIntakeCommand::Initialize()
{
    elbowSub->SetPosition(elbowPos);
    extenderSub->SetPosition(extenderPos);
    wristSub->SetPosition(wristPos);
    endEffectorSub->SetPercent(endEffectorPos);
    
}

void ConeIntakeCommand::Execute()
{

}

bool ConeIntakeCommand::IsFinished()
{
    return true;
}

void ConeIntakeCommand::End(bool interrupted)
{

}