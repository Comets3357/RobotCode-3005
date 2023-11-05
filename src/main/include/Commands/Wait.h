#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"

#include <frc2/command/WaitCommand.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "COMETS3357/TimerSubsystem.h"

#include "COMETS3357/Commands/Command.h"


DECLARE_COMMAND(Wait)

    COMETS3357::TimerSubsystem * t;
    units::second_t endTime{0};
    units::second_t duration{0};

    Wait(COMETS3357::TimerSubsystem* timer, units::second_t time);


    units::second_t s;

private:
    
DECLARE_COMMAND_END