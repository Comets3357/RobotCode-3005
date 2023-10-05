#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"

#include <frc2/command/WaitCommand.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "COMETS3357/TimerSubsystem.h"


class Wait : public frc2::CommandHelper<frc2::CommandBase, Wait>
{
public:

    COMETS3357::TimerSubsystem * t;
    units::second_t endTime{0};
    units::second_t duration{0};

    Wait(COMETS3357::TimerSubsystem* timer, units::second_t time);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;
    void End(bool interrupted) override;

    units::second_t s;

private:

    

};