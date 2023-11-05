#pragma once

#include "COMETS3357/Commands/Command.h"

#include "Subsystems/WristSubsystem.h"


DECLARE_COMMAND(ConeFlipCommand)

    ConeFlipCommand(WristSubsystem * wrist);

private:

    WristSubsystem * wrist;

DECLARE_COMMAND_END



