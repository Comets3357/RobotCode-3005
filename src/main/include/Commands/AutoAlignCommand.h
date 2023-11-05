#pragma once



#include "COMETS3357/Subsystems/Chassis/SwerveSubsystem.h"
#include "COMETS3357/Subsystems/Vision/LimelightSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "COMETS3357/GyroSubsystem.h"

#include "COMETS3357/Commands/Command.h"

DECLARE_COMMAND(AutoAlignCommand)

    AutoAlignCommand(COMETS3357::SwerveSubsystem *driveSub, COMETS3357::LimelightSubsystem *limelightSub, EndEffectorSubsystem *endEffectorSub, COMETS3357::GyroSubsystem * gyroSub);

private:

    COMETS3357::SwerveSubsystem *swerve;
    COMETS3357::LimelightSubsystem *limelight;
    EndEffectorSubsystem *endEffector;
    COMETS3357::GyroSubsystem * gyro;
    
    double angleX = 0;

DECLARE_COMMAND_END