#include "Commands/AutoAlignCommand.h"


AutoAlignCommand::AutoAlignCommand(COMETS3357::SwerveSubsystem *driveSub, COMETS3357::LimelightSubsystem *limelightSub, EndEffectorSubsystem *endEffectorSub, COMETS3357::GyroSubsystem *gyroSub) :
    endEffector{endEffectorSub},
    limelight{limelightSub},
    swerve{driveSub},
    gyro{gyroSub}
{
    AddRequirements(swerve);
}

void AutoAlignCommand::Initialize()
{
}

void AutoAlignCommand::Execute()
{
    //swerve->Drive(units::velocity::meters_per_second_t{limelight->getX()}, units::velocity::meters_per_second_t{0}, 0, -1, true, false);
    swerve->Drive(units::velocity::meters_per_second_t{0}, units::velocity::meters_per_second_t{0}, sin(limelight->getX()), -cos(limelight->getX()), true, false);
}

bool AutoAlignCommand::IsFinished()
{
    if (abs(limelight->getX()) < 0.1)
    {
        swerve->Drive(units::velocity::meters_per_second_t{0}, units::velocity::meters_per_second_t{0}, 0, -1, true, false);
        return true;
    }
    return false;
}

void AutoAlignCommand::End(bool interrupted)
{

}
