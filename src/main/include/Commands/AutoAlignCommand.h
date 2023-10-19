#pragma once



#include "COMETS3357/Subsystems/Chassis/SwerveSubsystem.h"
#include "COMETS3357/Subsystems/Vision/LimelightSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "COMETS3357/GyroSubsystem.h"

class AutoAlignCommand : public frc2::CommandHelper<frc2::CommandBase, AutoAlignCommand>
{
public:
    AutoAlignCommand(COMETS3357::SwerveSubsystem *driveSub, COMETS3357::LimelightSubsystem *limelightSub, EndEffectorSubsystem *endEffectorSub, COMETS3357::GyroSubsystem * gyroSub);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End(bool interrupted) override;

private:

    COMETS3357::SwerveSubsystem *swerve;
    COMETS3357::LimelightSubsystem *limelight;
    EndEffectorSubsystem *endEffector;
    COMETS3357::GyroSubsystem * gyro;
    
    double angleX = 0;



};