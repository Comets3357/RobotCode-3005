#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"

#include "COMETS3357/Subsystems/SparkMax/SparkMaxPosition.h"

class WristSubsystem : public COMETS3357::Subsystem
{
public:

    WristSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPosition(double position);
    
    void SetPosition(std::string position);

    void SetPercent(double percent);
    
    void SetPercent(std::string percent);

    double GetPosition();



    COMETS3357::SparkMaxPosition wristMotor{"WristMotor"};

};


