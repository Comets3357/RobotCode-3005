#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPosition.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"
#include "COMETS3357/Subsystems/SparkMax/SparkMaxVelocity.h"

enum ExampleSubsystemState
{

};

class ExampleSubsystem : public COMETS3357::Subsystem<ExampleSubsystemState>
{
public:

    ExampleSubsystem();

    void Initialize() override;

    void Periodic() override;

private:

    COMETS3357::SparkMaxPosition SparkMaxPosition{"ExamplePositionMotor"};
    COMETS3357::SparkMaxVelocity SparkMaxVelocity{"ExampleWheelMotor"};
    COMETS3357::SparkMaxPercent SparkMaxPercent{"ExampleRollerMotor"};

};