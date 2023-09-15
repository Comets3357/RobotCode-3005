#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "Commands/SetPositionCommand.h"

class AutoRetractCommand : public frc2::CommandHelper<frc2::CommandBase, AutoRetractCommand>
{
public:
    AutoRetractCommand(SetPositionCommand &targetPosition, SetPositionCommand &homePosition, EndEffectorSubsystem* endEffector, double amps);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

    SetPositionCommand &targetPositionCommand;
    SetPositionCommand &homePositionCommand;
    EndEffectorSubsystem* endEffectorSubsystem;

    double ampLimit;

};