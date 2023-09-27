#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"

enum EndEffectorSubsystemState
{
NONE,
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

    double GetOutputCurrent();

    double GetPosition();



    COMETS3357::SparkMaxPercent endEffectorMotor{"EndEffectorMotor"};

};