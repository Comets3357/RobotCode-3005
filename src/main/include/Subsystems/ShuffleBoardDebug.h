#pragma once

#include "COMETS3357/Subsystems/Subsystem.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <map>
#include <string>

#include "COMETS3357/Configs/ConfigFiles.h"
#include <frc2/command/button/NetworkButton.h>
#include <frc2/command/InstantCommand.h>

enum ShuffleBoardDebugState
{

};

class PositionMotorDebug
{
    public:
    PositionMotorDebug(std::pair<const std::string, COMETS3357::SparkMaxPositionConfig>& config) :
    positionMotorDebugLayout{frc::Shuffleboard::GetTab("DevicesDebugTab").GetLayout(config.first, frc::BuiltInLayouts::kList)
                    .WithPosition(0, 0)
                    .WithSize(2, 4)}
    {
        
    }

    void ShowMenu()
    {
        positionMotorDebugLayout.WithProperties({{"Hidden", nt::Value::MakeBoolean(false)}});
    }

    void HideMenu()
    {
        positionMotorDebugLayout.WithProperties({{"Hidden", nt::Value::MakeBoolean(true)}});
    }

    frc::ShuffleboardLayout& positionMotorDebugLayout;

};

class ShuffleBoardDebug : public COMETS3357::Subsystem<ShuffleBoardDebugState>
{
public:

    ShuffleBoardDebug() : COMETS3357::Subsystem<ShuffleBoardDebugState>("ShuffleBoardDebug"),
    shuffleboard{frc::Shuffleboard::GetTab("DevicesDebugTab")},
    positionMotorList{shuffleboard.GetLayout("PositionMotors", frc::BuiltInLayouts::kList)
                    .WithPosition(0, 0)
                    .WithSize(2, 4)},
    percentMotorList{shuffleboard.GetLayout("PercentMotors", frc::BuiltInLayouts::kList)
                    .WithPosition(2, 0)
                    .WithSize(2, 4)},
    velocityMotorList{shuffleboard.GetLayout("VelocityMotors", frc::BuiltInLayouts::kList)
                    .WithPosition(4, 0)
                    .WithSize(2, 4)},
    pwmMotorList{shuffleboard.GetLayout("pwmMotors", frc::BuiltInLayouts::kList)
                    .WithPosition(6, 0)
                    .WithSize(2, 4)},
    ntinst{ nt::NetworkTableInstance::GetDefault()},
    table{ ntinst.GetTable("Shuffleboard")}
    {
       
    
        
    }

    void Initialize() override
    {
        for (auto& motor : COMETS3357::ConfigFiles::getInstance().GetConfigFiles().sparkMaxPositionConfigs)
        {
        
            positionMotorList.Add(motor.first, false)
                .WithWidget(frc::BuiltInWidgets::kToggleButton)
                .WithPosition(0,0)
                .WithSize(1, 1)
                .GetEntry();

            frc2::NetworkButton("Shuffleboard", "DevicesDebugTab/PositionMotors/" + motor.first).OnTrue(new frc2::InstantCommand([&] {
                if (!positionMotorDebugs.contains(motor.first))
                    positionMotorDebugs.emplace(motor.first, new PositionMotorDebug(motor));

                    positionMotorDebugs[motor.first]->ShowMenu();
            }));

            

            frc2::NetworkButton("Shuffleboard", "DevicesDebugTab/PositionMotors/" + motor.first).OnFalse(new frc2::InstantCommand([&] {

                if (positionMotorDebugs.contains(motor.first))
                    {
                        positionMotorDebugs[motor.first]->HideMenu();
                    }
            }));

            
        }

        for (auto& motor : COMETS3357::ConfigFiles::getInstance().GetConfigFiles().sparkMaxPercentConfigs)
        {
            percentMotorList.Add(motor.first, false)
                .WithWidget(frc::BuiltInWidgets::kToggleButton)
                .WithPosition(0,0)
                .WithSize(1, 1)
                .GetEntry();
        }

        for (auto& motor : COMETS3357::ConfigFiles::getInstance().GetConfigFiles().sparkMaxVelocityConfigs)
        {
            velocityMotorList.Add(motor.first, false)
                .WithWidget(frc::BuiltInWidgets::kToggleButton)
                .WithPosition(0,0)
                .WithSize(1, 1)
                .GetEntry();
        }

        for (auto& motor : COMETS3357::ConfigFiles::getInstance().GetConfigFiles().sparkMaxPWMConfigs)
        {
            pwmMotorList.Add(motor.first, false)
                .WithWidget(frc::BuiltInWidgets::kToggleButton)
                .WithPosition(0,0)
                .WithSize(1, 1)
                .GetEntry();
        }

        frc::Shuffleboard::Update();
    }
    
    void Periodic() override
    {
   

        frc::Shuffleboard::Update();

        // if (table->GetEntry("ButtonList/Button1").GetBoolean(false))
        // {
        //     table->GetEntry("ButtonList/Button1").SetBoolean(false);
        // }
        // else if (table->GetEntry("ButtonList/Button2").GetBoolean(false))
        // {
        //     table->GetEntry("ButtonList/Button2").SetBoolean(false);
        // }

        for (auto& motor : COMETS3357::ConfigFiles::getInstance().GetConfigFiles().sparkMaxPositionConfigs)
        {
            // if (table->GetEntry("PositionMotors/" + motor.first).GetBoolean(false))
            // {
            //     if (!positionMotorDebugs.contains(motor.first))
            //     positionMotorDebugs.emplace(motor.first, new PositionMotorDebug(motor));

            //     positionMotorDebugs[motor.first]->ShowMenu();
            // }
            // else
            // {
            //     if (positionMotorDebugs.contains(motor.first))
            //     {
            //         positionMotorDebugs[motor.first]->HideMenu();
            //     }
            // }
        }


        
    }

private:

    frc::ShuffleboardTab& shuffleboard;

    frc::ShuffleboardLayout& positionMotorList;
    frc::ShuffleboardLayout& percentMotorList;
    frc::ShuffleboardLayout& velocityMotorList;
    frc::ShuffleboardLayout& pwmMotorList;

    nt::NetworkTableInstance ntinst;
    std::shared_ptr<nt::NetworkTable> table;

    std::map<std::string, PositionMotorDebug*> positionMotorDebugs;

    std::vector<nt::GenericEntry> entrys;


    


};

