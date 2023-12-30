#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"

enum EndEffectorSubsystemState
{
GAMEPIECE_NONE,
CONE,   
CUBE
};

enum PlacementPosition
{
    HIGH_CONE,
    MID_CONE,
    HIGH_CUBE,
    MID_CUBE,
    NONE
};

class EndEffectorSubsystem : public COMETS3357::Subsystem
{
public:

    EndEffectorSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPercent(double percent);
    
    void SetPercent(std::string percent);

    double GetOutputCurrent();

    double GetPosition();

    PlacementPosition placement = NONE;
    EndEffectorSubsystemState gamepiece = GAMEPIECE_NONE;

    COMETS3357::SparkMaxPercent endEffectorMotor{"EndEffectorMotor"};

};