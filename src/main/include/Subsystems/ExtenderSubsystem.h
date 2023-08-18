#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/Sparkmax/SparkMaxPercent.h"

enum ExtenderState
{

};

class ExtenderSubsystem : public COMETS3357::Subsystem<ExtenderState>
{
public:

    ExtenderSubsystem();

    void Initialize() override;
    
    void Periodic() override;

    void SetPercent(double percent);
    
    void SetPercent(std::string percent);

private:

    COMETS3357::SparkMaxPercent extendermotor{"ExtenderMotor"};

};