#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/Sparkmax/SparkMaxPosition.h"


class ExtenderSubsystem : public COMETS3357::Subsystem
{
public:

    ExtenderSubsystem();

    void Initialize() override;
    
    void Periodic() override;

    void SetPosition(double position);

    void SetPosition(std::string position);

    void SetPercent(double percent);

    double GetPosition();



    COMETS3357::SparkMaxPosition extendermotor{"ExtenderMotor"};

};