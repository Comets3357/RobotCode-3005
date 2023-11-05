#pragma once
#include "COMETS3357/Commands/Command.h"
#include "Subsystems/EndEffectorSubsystem.h"



DECLARE_COMMAND(EjectCommand)

    EjectCommand(EndEffectorSubsystem* endEffectorState, bool on);


private:

    EndEffectorSubsystem* endEffectorSubsystem;

    bool enabled = false;

DECLARE_COMMAND_END


