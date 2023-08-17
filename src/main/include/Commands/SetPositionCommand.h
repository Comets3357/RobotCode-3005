#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"

class SetPositionCommand : public frc2::CommandHelper<frc2::CommandBase, SetPositionCommand>
{
public:

    SetPositionCommand(ElbowSubsystem* elbowSubsystem, ExtenderSubsystem* extenderSubsystem, WristSubsystem* wristSubsystem, std::string elbowPosition, std::string extenderPosition, std::string wristPosition);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

    ElbowSubsystem* elbowSub;
    ExtenderSubsystem* extenderSub;
    WristSubsystem* wristSub;
    std::string elbowPos;
    std::string extenderPos;
    std::string wristPos;

};