#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"



class SetPositionCommand : public frc2::CommandHelper<frc2::CommandBase, SetPositionCommand>
{
public:

    enum EndEffectorMode
    {
        END_EFFECTOR_STAGNANT,
        END_EFFECTOR_CONE_INPUT,
        END_EFFECTOR_CUBE_INPUT,
        END_EFFECTOR_CONE_HOLD,
        END_EFFECTOR_CUBE_HOLD,
        END_EFFECTOR_GAME_PIECE
    };

    SetPositionCommand(ElbowSubsystem* elbowSubsystem, ExtenderSubsystem* extenderSubsystem, WristSubsystem* wristSubsystem, EndEffectorSubsystem* endEffectorSubsystem, std::string elbowPosition, std::string extenderPosition, std::string wristPosition, EndEffectorMode mode, EndEffectorSubsystemState gamePiece);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

    ElbowSubsystem* elbowSub;
    ExtenderSubsystem* extenderSub;
    WristSubsystem* wristSub;
    EndEffectorSubsystem* endEffectorSub;
    std::string elbowPos;
    std::string extenderPos;
    std::string wristPos;
    EndEffectorSubsystemState piece;

    EndEffectorMode endEffectorMode = END_EFFECTOR_STAGNANT;

    bool isFromHome = false;
};