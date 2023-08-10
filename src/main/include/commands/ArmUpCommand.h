#include <frc2/command/CommandHelper.h>

#include "Subsystems/ArmSubsystem.h"

class ArmUpCommand : public frc2::CommandHelper<frc2::CommandBase, ArmUpCommand>
{
public:

    ArmUpCommand(ArmSubsystem* subsystem);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

    ArmSubsystem* armSubsystem;


};