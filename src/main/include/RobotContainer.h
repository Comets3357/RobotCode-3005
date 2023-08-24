// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/Trigger.h>

#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/angle.h>
#include <math.h>

#include "COMETS3357/Subsystems/Chassis/SwerveSubsystem.h"
#include "COMETS3357/Auton/Autons.h"
#include "COMETS3357/Configs/ControllerMap.h"
#include "COMETS3357/TimerSubsystem.h"

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"

#include "Commands/SetPositionCommand.h"
#include "Commands/PlacementCommand.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  void Periodic();


  //Subsystems
  COMETS3357::TimerSubsystem timer{};
  COMETS3357::GyroSubsystem gyro{};
  COMETS3357::SwerveSubsystem swerve{"Swerve"};
  ElbowSubsystem elbow{};
  EndEffectorSubsystem endEffector{};
  ExtenderSubsystem extender{};
  WristSubsystem wrist{};

  //Commands
  SetPositionCommand highCubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowHighCubePosition", "ExtenderHighCubePosition", "WristHighCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD};
  SetPositionCommand highConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowHighConePosition", "ExtenderHighConePosition", "WristHighConePosition", SetPositionCommand::END_EFFECTOR_CONE_HOLD};
  SetPositionCommand midConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowMidConePosition", "ExtenderMidConePosition", "WristMidConePosition", SetPositionCommand::END_EFFECTOR_CONE_HOLD};
  SetPositionCommand midCubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowMidCubePosition", "ExtenderMidCubePosition", "WristMidCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD};
  SetPositionCommand lowCubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowLowCubePosition", "ExtenderLowCubePosition", "WristLowCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD};
  SetPositionCommand lowConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowLowConePosition", "ExtenderLowConePosition", "WristLowConePosition", SetPositionCommand::END_EFFECTOR_CONE_HOLD};

  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> buttonActionMap 
  {
    {"HomePosition", std::make_shared<SetPositionCommand>(&elbow, &extender, &wrist, "ElbowHomePosition", "ExtenderHomePosition", "WristHomePosition")},
    {"HighPosition", std::make_shared<PlacementCommand>(&endEffector, highCubePosition, highConePosition)},
    {"MidPosition", std::make_shared<PlacementCommand>(&endEffector, midCubePosition, midConePosition)},
    {"LowPosition", std::make_shared<PlacementCommand>(&endEffector, lowCubePosition, lowConePosition)},
    {"UpRightConePosition", std::make_shared<SetPositionCommand>(&elbow, &extender, &wrist, "ElbowUpRightConePosition", "ExtenderUpRightConePosition", "WristUpRightConePosition")},
    {"SideConePosition", std::make_shared<SetPositionCommand>(&elbow, &extender, &wrist, "ElbowSideConePosition", "ExtenderSideConePosition", "WristSideConePosition")},
    {"CubePosition", std::make_shared<SetPositionCommand>(&elbow, &extender, &wrist, "ElbowCubePosition", "ExtenderCubePosition", "WristCubePosition")},
    {"SingleSubPosition", std::make_shared<SetPositionCommand>(&elbow, &extender, &wrist, "ElbowSingleSubPosition", "ExtenderSingleSubPosition", "WristSingleSubPosition")},
    {"DoubleSubPosition", std::make_shared<SetPositionCommand>(&elbow, &extender, &wrist, "ElbowDoubleSubPosition", "ExtenderDoubleSubPosition", "WristDoubleSubPosition")},
  };


  std::unordered_map<std::string, std::tuple<std::function<void(double, double, double, double)>, frc2::Subsystem*, COMETS3357::Controller::JoystickCommandMode>> joystickActionMap
  {
   {"SwerveDefaultCommand", {[this](auto leftX, auto leftY, auto rightX, auto rightY){swerve.Drive(-units::meters_per_second_t{leftY}, -units::meters_per_second_t{leftX}, -units::radians_per_second_t{rightX}, true, true);}, &swerve, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualEndEffector", {[this](auto leftX, auto leftY, auto rightX, auto rightY){endEffector.SetPercent(leftY);}, &endEffector, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualExtender", {[this](auto leftX, auto leftY, auto rightX, auto rightY){extender.SetPercent(rightY);}, &extender, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualElbow", {[this](auto leftX, auto leftY, auto rightX, auto rightY){elbow.SetPercent(rightY);}, &elbow, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualWrist", {[this](auto leftX, auto leftY, auto rightX, auto rightY){wrist.SetPercent(leftY);}, &wrist, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}}
  };

  COMETS3357::ControllerMap controllerMap{buttonActionMap, joystickActionMap, "CompControllerMap", };
  COMETS3357::Autons autos{&swerve, buttonActionMap};

  void ConfigureBindings();
};
