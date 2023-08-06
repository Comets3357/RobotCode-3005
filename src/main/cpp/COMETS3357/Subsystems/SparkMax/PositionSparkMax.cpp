#include "COMETS3357/Subsystems/SparkMax/PositionSparkMax.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <COMETS3357/Subsystems/SubsystemManager.h>

using namespace COMETS3357;

PositionSparkMax::PositionSparkMax(std::string configName)
    : config{ConfigFiles::getInstance().GetConfigFiles().positionMotorConfigs[configName]},
     motor{config.ID, rev::CANSparkMax::MotorType::kBrushless},
    PIDController{motor.GetPIDController()},
    relativeEncoder{motor.GetEncoder()},
    absoluteEncoder{motor.GetAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder::Type::kDutyCycle)}
{
    defaultRunMode = config.defaultMode;
    runMode = defaultRunMode;

    changeRunMode(defaultRunMode);
    config.motor = &motor;

   COMETS3357::SubsystemManager::GetInstance().AddInit([this]{RobotInit();});

};

PositionSparkMax::PositionSparkMax(std::string configName, bool setAbsoluteOffset)
    : config{ConfigFiles::getInstance().GetConfigFiles().positionMotorConfigs[configName]},
     motor{config.ID, rev::CANSparkMax::MotorType::kBrushless},
    PIDController{motor.GetPIDController()},
    relativeEncoder{motor.GetEncoder()},
    absoluteEncoder{motor.GetAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder::Type::kDutyCycle)}
{
    defaultRunMode = config.defaultMode;
    runMode = defaultRunMode;

    changeRunMode(defaultRunMode);

    setAbsPos = setAbsoluteOffset;
    config.motor = &motor;

    COMETS3357::SubsystemManager::GetInstance().AddInit([this]{RobotInit();});

};

void PositionSparkMax::RobotInit()
{

    if (
        motor.GetInverted() != config.invertedRelative || 
        motor.GetIdleMode() != config.idleMode || 
        PIDController.GetOutputMin(1) != config.minSpeed ||
        PIDController.GetOutputMax(1) != config.maxSpeed ||
        relativeEncoder.GetPositionConversionFactor() != config.relativePositionConversionFactor ||
        relativeEncoder.GetVelocityConversionFactor() != config.relativeVelocityConversionFactor ||
        absoluteEncoder.GetInverted() != config.invertedAbsolute ||
        absoluteEncoder.GetPositionConversionFactor() != config.absolutePositionConversionFactor ||
        absoluteEncoder.GetVelocityConversionFactor() != config.absoluteVelocityConversionFactor ||
        PIDController.GetPositionPIDWrappingEnabled() != config.positionPIDWrappingEnabled ||
        PIDController.GetPositionPIDWrappingMinInput() != config.turningEncoderPositionPIDMinInput ||
        PIDController.GetPositionPIDWrappingMaxInput() != config.turningEncoderPositionPIDMaxInput
    )
    {
        motor.RestoreFactoryDefaults();
        motor.SetInverted(config.invertedRelative);
        motor.SetSmartCurrentLimit(config.currentLimit);
        motor.SetIdleMode(config.idleMode);
        PIDController.SetOutputRange(config.minSpeed, config.maxSpeed, 1);
        SetVelocityPID(config.velocityPID);
        SetPositionPID(config.positionPID);
        relativeEncoder.SetPositionConversionFactor(config.relativePositionConversionFactor);
        relativeEncoder.SetVelocityConversionFactor(config.relativeVelocityConversionFactor);
        absoluteEncoder.SetInverted(config.invertedAbsolute);
        absoluteEncoder.SetPositionConversionFactor(config.absolutePositionConversionFactor);
        absoluteEncoder.SetVelocityConversionFactor(config.absoluteVelocityConversionFactor);
        if (setAbsPos)
        {
            absoluteEncoder.SetZeroOffset(config.absoluteZeroOffset);
        }

        PIDController.SetPositionPIDWrappingEnabled(config.positionPIDWrappingEnabled);
        PIDController.SetPositionPIDWrappingMinInput(config.turningEncoderPositionPIDMinInput);
        PIDController.SetPositionPIDWrappingMaxInput(config.turningEncoderPositionPIDMaxInput);

        if (config.follow != "NONE")
        {
            motor.Follow(*COMETS3357::ConfigFiles::getInstance().GetConfigFiles().positionMotorConfigs[config.follow].motor);
        }

        motor.BurnFlash();
        
    }


        

}

void PositionSparkMax::ZeroRelativeEncoder()
{
    relativeEncoder.SetPosition(absoluteEncoderPosition);
}

void PositionSparkMax::ChangeFeedBackDevice(PositionSparkMaxRunMode mode)
{
    switch (mode)
    {
    case POSITION_SPARK_MAX_ABSOLUTE:
        PIDController.SetFeedbackDevice(absoluteEncoder);
        break;
    case POSITION_SPARK_MAX_RELATIVE:
        PIDController.SetFeedbackDevice(relativeEncoder);
        break;
    default:
        break;
    }
}

void PositionSparkMax::SetVelocityPID(PID pid)
{
    PIDController.SetP(pid.P, 0);
    PIDController.SetI(pid.I, 0);
    PIDController.SetD(pid.D, 0);
    PIDController.SetFF(pid.FF, 0);

    velocityPID = pid;
}

void PositionSparkMax::SetPositionPID(PID pid)
{
    PIDController.SetP(pid.P, 1);
    PIDController.SetI(pid.I, 1);
    PIDController.SetD(pid.D, 1);
    PIDController.SetFF(pid.FF, 1);

    positionPID = pid;
}


void PositionSparkMax::SetPIDOutputRange(double min, double max, int slot)
{
    PIDController.SetOutputRange(min, max, slot);
}

double PositionSparkMax::GetPosition()
{
    switch (runMode)
    {
    case POSITION_SPARK_MAX_ABSOLUTE:
        return absoluteEncoderPosition;
        break;
    case POSITION_SPARK_MAX_RELATIVE:
        return relativeEncoderPosition;
        break;
    default:
        return 0;
        break;
    }
}

void PositionSparkMax::SetVelocity(double velocity)
{
    PIDController.SetReference(velocity, rev::CANSparkMax::ControlType::kVelocity, 0);
}

void PositionSparkMax::SetPosition(double position)
{
    frc::SmartDashboard::PutNumber("POSITION", position);
    PIDController.SetReference(position, rev::CANSparkMax::ControlType::kPosition, 1);
}

void PositionSparkMax::SetPosition(std::string position)
{
    PIDController.SetReference(config.positions[position], rev::CANSparkMax::ControlType::kPosition, 1);
}

double PositionSparkMax::GetRelativePosition()
{
    return relativeEncoderPosition;
}

double PositionSparkMax::GetAbsolutePosition()
{
    return absoluteEncoderPosition;
}

double PositionSparkMax::GetRelativeVelocity()
{
    return relativeEncoder.GetVelocity();
}

double PositionSparkMax::GetAbsoluteVelocity()
{
    return absoluteEncoder.GetVelocity();
}

void PositionSparkMax::Periodic()
{
    absoluteEncoderPosition = absoluteEncoder.GetPosition();
    relativeEncoderPosition = absoluteEncoder.GetPosition();

    frc::SmartDashboard::PutNumber("abs", absoluteEncoderPosition);
    frc::SmartDashboard::PutNumber("relative", relativeEncoderPosition);

    

    CheckAbsoluteEncoder();
}

void PositionSparkMax::changeRunMode(PositionSparkMaxRunMode mode)
{
    runMode = mode;
    ChangeFeedBackDevice(runMode);
}



void PositionSparkMax::CheckAbsoluteEncoder()
{
    // if (runMode != POSITION_SPARK_MAX_ABSOLUTE) {
    //     return;
    // }


    // if (lastPosition != absoluteEncoderPosition)
    // {
    //     absAttempts++;
    // }
    // else
    // {
    //     absAttempts = 0;
    // }
    // lastPosition = absoluteEncoderPosition;

    // if (absAttempts > 20)
    // {
    //     changeRunMode(POSITION_SPARK_MAX_RELATIVE);
    // }
}