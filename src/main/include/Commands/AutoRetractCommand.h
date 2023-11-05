#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "Commands/SetPositionCommand.h"

#include "COMETS3357/Commands/Command.h"


DECLARE_COMMAND(AutoRetractCommand)

    AutoRetractCommand(SetPositionCommand &targetPosition, SetPositionCommand &homePosition, EndEffectorSubsystem* endEffector, double amps);

private:

    SetPositionCommand &targetPositionCommand;
    SetPositionCommand &homePositionCommand;
    EndEffectorSubsystem* endEffectorSubsystem;

    double ampLimit;

DECLARE_COMMAND_END