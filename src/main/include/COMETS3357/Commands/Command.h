#pragma once

#include <frc2/command/CommandHelper.h>

#define DECLARE_COMMAND(idk) \
class idk : public frc2::CommandHelper<frc2::CommandBase, idk> \
{ \
    public: \
    void Initialize() override; \
    void Execute() override; \
    bool IsFinished() override; \
    void End(bool interrupted) override; \

#define DECLARE_COMMAND_END \
};