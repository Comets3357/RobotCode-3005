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
    EndEffectorMode mode,
    EndEffectorSubsystemState gamePiece
    ) : 
    elbowSub{elbowSubsystem}, 
    extenderSub{extenderSubsystem},
    wristSub{wristSubsystem},
    endEffectorSub{endEffectorSubsystem},
    elbowPos{elbowPosition},
    extenderPos{extenderPosition},
    wristPos{wristPosition},
    endEffectorMode{mode},
    piece{gamePiece}
{
    AddRequirements({elbowSubsystem, extenderSubsystem, wristSubsystem, endEffectorSubsystem});
}

void SetPositionCommand::Initialize()
{

    if (elbowSub->GetPosition() < 20)
    {
        isFromHome = true;
    }
    else
    {
        isFromHome = false;
    }

    if (piece != NONE)
    {
        endEffectorSub->SetState(piece);
    }
    

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
        case END_EFFECTOR_GAME_PIECE:
            switch (endEffectorSub->State())
            {
            case CUBE:
                endEffectorSub->SetPercent(-.05);
                break;
            case CONE:
                endEffectorSub->SetPercent(.05);
                break;
            
            default:
                break;
            }
        break;
    }
    
}

void SetPositionCommand::Execute()
{
    if (isFromHome)
    {
        elbowSub->SetPosition(60);
        if (elbowSub->GetPosition() > 40)
        {
            isFromHome = false;
        }
    }
    else
    {
        if (elbowSub->elbowMotor.config.positions[elbowPos] < 20)
        {
            wristSub->SetPosition(wristPos);
            extenderSub->SetPosition(extenderPos);
            
            if (extenderSub->GetPosition() < 1 && std::abs(wristSub->GetPosition() - wristSub->wristMotor.config.positions[elbowPos]) < 10)
            {
                elbowSub->SetPosition(elbowPos);
            }
            else
            {
                elbowSub->SetPosition(50);
            }
        }
        else
        {
            wristSub->SetPosition(wristPos);
            elbowSub->SetPosition(elbowPos);

            if (std::abs(elbowSub->GetPosition() - elbowSub->elbowMotor.config.positions[elbowPos]) < 60)
            {
                extenderSub->SetPosition(extenderPos);
                frc::SmartDashboard::PutNumber("extender", extenderSub->extendermotor.config.positions[extenderPos]);
            }
            else
            {
                extenderSub->SetPosition(0.5);
            }
        }
        
    }

    frc::SmartDashboard::PutNumber("elbow", elbowSub->elbowMotor.config.positions[elbowPos]);
}

bool SetPositionCommand::IsFinished()
{
    return std::abs(elbowSub->GetPosition() - elbowSub->elbowMotor.config.positions[elbowPos]) < 5;
}

void SetPositionCommand::End(bool interrupted)
{

}