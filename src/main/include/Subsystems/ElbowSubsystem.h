#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"

enum ElbowState 
{

};

class ElbowSubsystem : public COMETS3357::Subsystem<ElbowState>
{
public:

    ElbowSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPercent(double percent);

    void SetPercent(std::string percent);

private:

    COMETS3357::SparkMaxPercent elbowMotor{"elbowMotor"};
};










