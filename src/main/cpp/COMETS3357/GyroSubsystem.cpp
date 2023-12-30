#include "COMETS3357/GyroSubsystem.h"
#include <thread>

using namespace COMETS3357;

GyroSubsystem::GyroSubsystem() : COMETS3357::Subsystem("GyroSubsystem") , m_navx{frc::SPI::Port::kMXP}
{
    m_navx.Calibrate();
}

void GyroSubsystem::Periodic()
{
    if (!m_navx.IsCalibrating())
    {
        subsystemData->GetEntry("angle").SetDouble(-m_navx.GetAngle() * 3.14159 / 180);
        subsystemData->GetEntry("angleRate").SetDouble(m_navx.GetRate() * 3.14159 / 180);
    }
  
    m_navx.UpdateDisplacement(0, 9.81, 500, true);
}

void GyroSubsystem::CalculatePositions()
{
    
}