#pragma once

#include "COMETS3357/Subsystems/SparkMax/SparkMaxPosition.h"
#include "COMETS3357/Subsystems/Subsystem.h"

enum ArmState
{

};

class ArmSubsystem : public COMETS3357::Subsystem<ArmState>
{
public:

    ArmSubsystem();

    void Initialize() override;

    void Periodic() override;

    void SetPosition(double position);

private:

    COMETS3357::SparkMaxPosition motor{"Elbow"};

};