#pragma once
#include <frc2/command/CommandHelper.h>

#include "Subsystems/EndEffectorSubsystem.h"


class EjectCommand : public frc2::CommandHelper<frc2::CommandBase, EjectCommand>
{
public:

    EjectCommand(EndEffectorSubsystemState* endEffectorState);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

};



