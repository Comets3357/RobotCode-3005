#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPosition.h"

enum EndEffectorSubsystemState
{

};

class EndEffectorSubsystem : public COMETS3357::Subsystem<EndEffectorSubsystemState>
{
public:

    EndEffectorSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPosition(double position);
    void SetPosition(std::string position);

private:

    COMETS3357::SparkMaxPosition endeffectormotor{"endeffectormotor"};

};