#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "Commands/SetPositionCommand.h"

#include "COMETS3357/Commands/Command.h"

DECLARE_COMMAND(PlacementCommand)

    PlacementCommand(EndEffectorSubsystem* endEffector, SetPositionCommand &cubePosition, SetPositionCommand &conePosition, PlacementPosition placement);

private:

EndEffectorSubsystem* endEffectorSubsystem;
SetPositionCommand &cubePositionCommand;
SetPositionCommand &conePositionCommand;
PlacementPosition placement;

DECLARE_COMMAND_END