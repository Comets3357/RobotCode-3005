#include "Commands/AutoAlignCommand.h"
#include "frc/smartdashboard/SmartDashboard.h"

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
    angleX = gyro->GetSubsystemData("GyroSubsystem")->GetEntry("angle").GetDouble(0) - (limelight->getX() * 3.14159 / 180);
    frc::SmartDashboard::PutNumber("ANGLE", limelight->getX() * 3.14159 / 180);
}

void AutoAlignCommand::Execute()
{
    //swerve->Drive(units::velocity::meters_per_second_t{limelight->getX()}, units::velocity::meters_per_second_t{0}, 0, -1, true, false);
    swerve->Drive(units::velocity::meters_per_second_t{0}, units::velocity::meters_per_second_t{0}, sin(angleX ), cos(angleX), true, false);
    frc::SmartDashboard::PutNumber("X", sin(angleX ));
    frc::SmartDashboard::PutNumber("Y", cos(angleX));
}

bool AutoAlignCommand::IsFinished()
{
    if (abs(limelight->getX()) < 0.1)
    {
        swerve->Drive(units::velocity::meters_per_second_t{0}, units::velocity::meters_per_second_t{0}, units::radians_per_second_t{0}, true, false);
        return true;
    }
    return false;
}

void AutoAlignCommand::End(bool interrupted)
{

}
