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

    void SetPercent(double percent);
    
    void SetPercent(std::string percent);

private:

    COMETS3357::SparkMaxPercent endEffectorMotor{"EndEffectorMotor"};

};