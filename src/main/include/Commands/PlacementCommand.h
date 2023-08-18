#pragma once

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/WristSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "Commands/SetPositionCommand.h"


class PlacementCommand : public frc2::CommandHelper<frc2::CommandBase, PlacementCommand>
{
public: 
    PlacementCommand(EndEffectorSubsystem* endEffector, SetPositionCommand &cubePosition, SetPositionCommand &conePosition);

    void Initialize() override;
  
    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override; 


private:

EndEffectorSubsystem* endEffectorSubsystem;
SetPositionCommand &cubePositionCommand;
SetPositionCommand &conePositionCommand;


};