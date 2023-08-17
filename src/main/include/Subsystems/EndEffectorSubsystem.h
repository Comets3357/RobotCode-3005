#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"

#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"

enum EndEffectorSubsystemState
{
CONE,   
CUBE
};

class EndEffectorSubsystem : public COMETS3357::Subsystem<EndEffectorSubsystemState>
{
public:

    EndEffectorSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPercent(double power);

private:

    COMETS3357::SparkMaxPercent EndEffectorMotor{"EndEffectorMotor"};

};