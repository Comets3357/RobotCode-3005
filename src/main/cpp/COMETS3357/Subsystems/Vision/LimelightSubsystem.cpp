#include "COMETS3357/Subsystems/Vision/LimelightSubsystem.h"

using namespace COMETS3357;

LimelightSubsystem::LimelightSubsystem(COMETS3357::GyroSubsystem * gyro) : Subsystem<LimelightState>("LimelightSubsystem"), gyroSubsystem{gyro} {
    // Retrieve the Limelight network table instance
    nt::NetworkTableInstance inst = nt::NetworkTableInstance::GetDefault();
    table = inst.GetTable("limelight");
}

frc::Pose2d LimelightSubsystem::GetPose()
{
    try 
    {
        llresults = LimelightHelpers::getLatestResults(); 
        limelightOdometry = frc::DriverStation::Alliance::kBlue ? llresults.targetingResults.botPose_wpiblue : llresults.targetingResults.botPose_wpired;

    }
    catch (...)
    {
        
    }
    return frc::Pose2d{frc::Translation2d{units::meter_t{limelightOdometry.at(0)}, units::meter_t{limelightOdometry.at(1)}}, frc::Rotation2d{units::radian_t{ gyroSubsystem->GetSubsystemData("Gyro")->GetEntry("angle").GetDouble(0)}}};
}

double LimelightSubsystem::getX() {
    // Get the horizontal offset from the Limelight
    return table->GetNumber("tx", 0.0);
}

double LimelightSubsystem::getY() {
    // Get the vertical offset from the Limelight
    return table->GetNumber("ty", 0.0);
}

double LimelightSubsystem::getArea() {
    // Get the target area from the Limelight
    return table->GetNumber("ta", 0.0);
}

bool LimelightSubsystem::hasTarget() {
    // Check if the Limelight has a valid target
    return table->GetNumber("tv", 0.0) == 1.0;
}

double LimelightSubsystem::getPipeline() {
    // Get the currently selected pipeline index
    return table->GetNumber("getpipe", 0.0);
}

void LimelightSubsystem::setPipeline(double pipelineIndex) {
    // Set the pipeline index to select a specific pipeline
    table->PutNumber("pipeline", pipelineIndex);
}

double LimelightSubsystem::getLEDMode() {
    // Get the currently selected LED mode
    return table->GetNumber("ledMode", 0.0);
}

void LimelightSubsystem::setLEDMode(double mode) {
    // Set the LED mode to control the Limelight's LEDs
    table->PutNumber("ledMode", mode);
}

double LimelightSubsystem::getCameraMode() {
    // Get the currently selected camera mode
    return table->GetNumber("camMode", 0.0);
}

void LimelightSubsystem::setCameraMode(double mode) {
    // Set the camera mode to control the Limelight's operation
    table->PutNumber("camMode", mode);
}

double LimelightSubsystem::getPipelineLatency() {
    // Get the pipeline's latency contribution in milliseconds
    return table->GetNumber("tl", 0.0);
}

double LimelightSubsystem::getFirmwareVersion() {
    // Get the Limelight's firmware version
    return table->GetNumber("getpipe", 0.0);
}

double LimelightSubsystem::getTargetHorizontalLength() {
    // Get the length of the longer side of the fitted bounding box
    return table->GetNumber("thor", 0.0);
}

double LimelightSubsystem::getTargetVerticalLength() {
    // Get the length of the shorter side of the fitted bounding box
    return table->GetNumber("tvert", 0.0);
}

double LimelightSubsystem::getTargetSkew() {
    // Get the skew or rotation (-90 degrees to 0 degrees)
    return table->GetNumber("ts", 0.0);
}

double LimelightSubsystem::getTargetShort() {
    // Get the "short" side of the rough bounding box
    return table->GetNumber("tshort", 0.0);
}

double LimelightSubsystem::getTargetLong() {
    // Get the "long" side of the rough bounding box
    return table->GetNumber("tlong", 0.0);
}

std::vector<double> LimelightSubsystem::getRawTargetVertices() {
    // Get the raw target vertices (x1, y1, x2, y2, x3, y3, x4, y4)
    std::vector<double> vertices;
    vertices.resize(8);
    table->GetNumberArray("tcornx", std::span<double>(vertices.begin(), vertices.end()));
    return vertices;
}