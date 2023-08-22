#include "COMETS3357/Subsystems/SparkMax/SparkMaxPercent.h"
#include <COMETS3357/Subsystems/SubsystemManager.h>

using namespace COMETS3357;

SparkMaxPercent::SparkMaxPercent(std::string configName) : config{ConfigFiles::getInstance().GetConfigFiles().sparkMaxPercentConfigs[configName]}, motor{config.ID, rev::CANSparkMax::MotorType::kBrushless}
{
    config.motor = &motor;
    COMETS3357::SubsystemManager::GetInstance().AddInit([this]{RobotInit();});
}

void SparkMaxPercent::SetPower(double power)
{
    motor.Set(power);
}

void SparkMaxPercent::SetPower(std::string power)
{
    motor.Set(config.percents[power]);
}

void SparkMaxPercent::RobotInit()
{

    if (
        motor.GetInverted() != config.invertedRelative || 
        motor.GetIdleMode() != config.idleMode
    )
    {
        motor.RestoreFactoryDefaults();
        motor.SetInverted(config.invertedRelative);
        motor.SetSmartCurrentLimit(config.currentLimit);
        motor.SetIdleMode(config.idleMode);

        if (config.follow != "NONE")
        {
            motor.Follow(*COMETS3357::ConfigFiles::getInstance().GetConfigFiles().sparkMaxPercentConfigs[config.follow].motor);
        }

        motor.BurnFlash();
    }
}