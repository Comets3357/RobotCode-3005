#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"

class ConeIntakeCommand : public frc2::CommandHelper<frc2::CommandBase, ConeIntakeCommand>
{
public:

    ConeIntakeCommand(ElbowSubsystem* elbowSubsystem, ExtenderSubsystem* extenderSubsystem, WristSubsystem* wristSubsystem, EndEffectorSubsystem* endEffectorSubsystem, std::string elbowPosition, std::string extenderPosition, std::string wristPosition, std::string endEffectorPosition);

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
    std::string endEffectorPos;

};