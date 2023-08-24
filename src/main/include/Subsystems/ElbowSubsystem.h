#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPosition.h"

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

    void SetPosition(double position);

    void SetPosition(std::string position);

private:

    COMETS3357::SparkMaxPosition elbowMotor{"elbowMotor"};
};










