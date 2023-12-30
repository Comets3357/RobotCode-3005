#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPosition.h"

#define PI 3.1415926535897932384626


class ElbowSubsystem : public COMETS3357::Subsystem
{
public:

    ElbowSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPercent(double percent);

    void SetPosition(double position);

    void SetPosition(std::string position);

    double GetPosition();



    COMETS3357::SparkMaxPosition elbowMotor{"ElbowMotor", true};
    COMETS3357::SparkMaxPosition elbowFollow{"ElbowMotorFollow", true};
};










