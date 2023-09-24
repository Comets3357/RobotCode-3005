#include "Commands/SetPositionCommand.h"

#include <frc/smartdashboard/SmartDashboard.h>


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
    frc::SmartDashboard::PutNumber("wrist", wristSub->wristMotor.config.positions[wristPos]);

    switch (endEffectorMode)
    {
        case END_EFFECTOR_STAGNANT:
        endEffectorSub->SetPercent(0);
        break;
        case END_EFFECTOR_CONE_INPUT:
        endEffectorSub->SetPercent("EndEffectorConeInputPercent");
        frc::SmartDashboard::PutNumber("endEffector", endEffectorSub->endEffectorMotor.config.percents["EndEffectorConeInputPercent"]);
        break;
        case END_EFFECTOR_CUBE_INPUT:
        endEffectorSub->SetPercent("EndEffectorCubeInputPercent");
        frc::SmartDashboard::PutNumber("endEffector", endEffectorSub->endEffectorMotor.config.percents["EndEffectorCubeInputPercent"]);
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
    frc::SmartDashboard::PutNumber("elbow", elbowSub->elbowMotor.config.positions[elbowPos]);

    if (true)//std::abs(elbowSub->GetPosition() - elbowSub->elbowMotor.config.positions[elbowPos]) < 40)
    {
        extenderSub->SetPosition(extenderPos);
        frc::SmartDashboard::PutNumber("extender", extenderSub->extendermotor.config.positions[extenderPos]);
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