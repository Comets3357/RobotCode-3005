#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"

#include "COMETS3357/Commands/Command.h"

DECLARE_COMMAND(SetPositionCommand)

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

    bool k = false;

DECLARE_COMMAND_END