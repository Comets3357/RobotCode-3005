#include "COMETS3357/Subsystems/SparkMax/SparkMaxPWM.h"

using namespace COMETS3357;

SparkMaxPWM::SparkMaxPWM(std::string configName) : config{ConfigFiles::getInstance().GetConfigFiles().sparkMaxPWMConfigs[configName]}, motor{config.ID}
{
    config.motor = &motor;
    SubsystemManager::GetInstance().AddInit([this]{RobotInit();});
}

void SparkMaxPWM::RobotInit()
{
    if (motor.GetInverted() != config.inverted)
    {
        motor.SetInverted(config.inverted);
    }
}

void SparkMaxPWM::SetPower(double power)
{
    motor.Set(power);
}