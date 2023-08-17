#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"

#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"

enum WristState
{

};

class WristSubsystem : public COMETS3357::Subsystem<WristState>
{
public:

    WristSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPercent(double percent);
    
    void SetPercent(std::string percent);

private:

    COMETS3357::SparkMaxPercent wristMotor{"WristMotor"};

};


