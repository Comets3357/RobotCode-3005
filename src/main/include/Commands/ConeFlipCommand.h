#pragma once
#include <frc2/command/CommandHelper.h>

#include "Subsystems/WristSubsystem.h"


class ConeFlipCommand : public frc2::CommandHelper<frc2::CommandBase, ConeFlipCommand>
{
public:

    ConeFlipCommand(WristSubsystem * wrist);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

    WristSubsystem * wrist;

};



