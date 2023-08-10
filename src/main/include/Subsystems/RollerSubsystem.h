#pragma once

#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"
#include "COMETS3357/Subsystems/Subsystem.h"

enum RollerSubsystemState
{
    ROLLER_STOPPED,
    ROLLER_RUNNING
};

class RollerSubsystem : public COMETS3357::Subsystem<RollerSubsystemState>
{
public:

    RollerSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPower(double power);

private:

    COMETS3357::SparkMaxPercent roller{"Roller"};

};
