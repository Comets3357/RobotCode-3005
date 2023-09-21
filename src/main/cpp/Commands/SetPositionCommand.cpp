#include "Commands/SetPositionCommand.h"


SetPositionCommand::SetPositionCommand(
    ElbowSubsystem* elbowSubsystem, 
    ExtenderSubsystem* extenderSubsystem, 
    WristSubsystem* wristSubsystem, 
    EndEffectorSubsystem* endEffectorSubsystem,
    std::string elbowPosition, 
    std::string extenderPosition, 
    std::string wristPosition,
    EndEffectorMode mode
    ) : 
    elbowSub{elbowSubsystem}, 
    extenderSub{extenderSubsystem},
    wristSub{wristSubsystem},
    endEffectorSub{endEffectorSubsystem},
    elbowPos{elbowPosition},
    extenderPos{extenderPosition},
    wristPos{wristPosition},
    endEffectorMode{mode}
{
    AddRequirements({elbowSubsystem, extenderSubsystem, wristSubsystem, endEffectorSubsystem});
}

void SetPositionCommand::Initialize()
{

    wristSub->SetPosition(wristPos);

    switch (endEffectorMode)
    {
        case END_EFFECTOR_STAGNANT:
        endEffectorSub->SetPercent(0);
        break;
        case END_EFFECTOR_CONE_INPUT:
        endEffectorSub->SetPercent("EndEffectorConeInputPercent");
        break;
        case END_EFFECTOR_CUBE_INPUT:
        endEffectorSub->SetPercent("EndEffectorCubeInputPercent");
        break;
        case END_EFFECTOR_CONE_HOLD:
        endEffectorSub->SetPercent("EndEffectorConeHoldPercent");
        break;
        case END_EFFECTOR_CUBE_HOLD:
        endEffectorSub->SetPercent("EndEffectorCubeHoldPercent");
        break;
    }
    
}

void SetPositionCommand::Execute()
{
    elbowSub->SetPosition(elbowPos);

    if (std::abs(elbowSub->GetPosition() - elbowSub->elbowMotor.config.positions[elbowPos]) < 40)
    {
        extenderSub->SetPosition(extenderPos);
    }
    else
    {
        extenderSub->SetPosition(0.5);
    }
}

bool SetPositionCommand::IsFinished()
{
    return std::abs(elbowSub->GetPosition() - elbowSub->elbowMotor.config.positions[elbowPos]) < 2;
}

void SetPositionCommand::End(bool interrupted)
{

}