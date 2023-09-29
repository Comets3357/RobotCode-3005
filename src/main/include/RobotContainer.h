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
#include "Commands/AutoRetractCommand.h"
#include "Commands/EjectCommand.h"

#include <frc2/command/SequentialCommandGroup.h>
#include "Commands/ConeFlipCommand.h"

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
  SetPositionCommand highCubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowHighCubePosition", "ExtenderHighCubePosition", "WristHighCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD, CUBE};
  SetPositionCommand highConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowHighConePosition", "ExtenderHighConePosition", "WristHighConePosition", SetPositionCommand::END_EFFECTOR_CONE_HOLD, CONE};
  SetPositionCommand midConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowMidConePosition", "ExtenderMidConePosition", "WristMidConePosition", SetPositionCommand::END_EFFECTOR_CONE_HOLD, CONE};
  SetPositionCommand midCubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowMidCubePosition", "ExtenderMidCubePosition", "WristMidCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD, CUBE};
  SetPositionCommand lowCubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowLowCubePosition", "ExtenderLowCubePosition", "WristLowCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD, CUBE};
  SetPositionCommand lowConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowLowConePosition", "ExtenderLowConePosition", "WristLowConePosition", SetPositionCommand::END_EFFECTOR_CONE_HOLD, CONE};
  SetPositionCommand upRightConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowUpRightConePosition", "ExtenderUpRightConePosition", "WristUpRightConePosition", SetPositionCommand::END_EFFECTOR_CONE_INPUT, CONE};
  SetPositionCommand sideConePosition{&elbow, &extender, &wrist, &endEffector, "ElbowSideConePosition", "ExtenderSideConePosition", "WristSideConePosition", SetPositionCommand::END_EFFECTOR_CONE_INPUT, CONE};
  SetPositionCommand cubePosition{&elbow, &extender, &wrist, &endEffector, "ElbowCubePosition", "ExtenderCubePosition", "WristCubePosition", SetPositionCommand::END_EFFECTOR_CUBE_INPUT, CUBE};
  SetPositionCommand singleSubPosition{&elbow, &extender, &wrist, &endEffector, "ElbowSingleSubPosition", "ExtenderSingleSubPosition", "WristSingleSubPosition", SetPositionCommand::END_EFFECTOR_CUBE_INPUT, NONE};
  SetPositionCommand doubleSubPosition{&elbow, &extender, &wrist, &endEffector, "ElbowDoubleSubPosition", "ExtenderDoubleSubPosition", "WristDoubleSubPosition", SetPositionCommand::END_EFFECTOR_CUBE_HOLD, NONE};
  SetPositionCommand homePosition{&elbow, &extender, &wrist, &endEffector, "ElbowHomePosition", "ExtenderHomePosition", "WristHomePosition", SetPositionCommand::END_EFFECTOR_GAME_PIECE, NONE};

  frc2::SequentialCommandGroup HighConePlaceAutonCommand{highConePosition, frc2::WaitCommand(1_s), EjectCommand(&endEffector, true), frc2::WaitCommand(1_s), EjectCommand(&endEffector, false), homePosition};
  frc2::SequentialCommandGroup CubePickupAutonCommand{cubePosition, frc2::WaitCommand(2_s), homePosition};
  frc2::SequentialCommandGroup HighCubePlaceAutonCommand{highCubePosition, frc2::WaitCommand(1_s), EjectCommand(&endEffector, true), frc2::WaitCommand(1_s), EjectCommand(&endEffector, false), homePosition};
  frc2::SequentialCommandGroup MidCubePlaceAutonCommand{midCubePosition, frc2::WaitCommand(1_s), EjectCommand(&endEffector, true), frc2::WaitCommand(1_s), EjectCommand(&endEffector, false), homePosition};


  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> buttonActionMap 
  {
    {"HomePosition", std::make_shared<SetPositionCommand>(homePosition)},
    {"HighPosition", std::make_shared<PlacementCommand>(&endEffector, highCubePosition, highConePosition)},
    {"MidPosition", std::make_shared<PlacementCommand>(&endEffector, midCubePosition, midConePosition)},
    {"LowPosition", std::make_shared<PlacementCommand>(&endEffector, lowCubePosition, lowConePosition)},
    {"UpRightConePosition", std::make_shared<AutoRetractCommand>(upRightConePosition, homePosition, &endEffector, 0)},
    {"SideConePosition", std::make_shared<AutoRetractCommand>(sideConePosition, homePosition, &endEffector, 0)},
    {"CubePosition", std::make_shared<AutoRetractCommand>(cubePosition, homePosition, &endEffector, 0)},
    {"SingleSubPosition", std::make_shared<AutoRetractCommand>(singleSubPosition, homePosition, &endEffector, 0)},
    {"DoubleSubPosition", std::make_shared<AutoRetractCommand>(doubleSubPosition, homePosition, &endEffector, 0)},
    {"EjectOnPress", std::make_shared<EjectCommand>(&endEffector, true)},
    {"EjectOnRelease", std::make_shared<EjectCommand>(&endEffector, false)},
    {"ConeFlip", std::make_shared<ConeFlipCommand>(&wrist)}
  };


  std::unordered_map<std::string, std::tuple<std::function<void(double, double, double, double)>, frc2::Subsystem*, COMETS3357::Controller::JoystickCommandMode>> joystickActionMap
  {
   {"SwerveDefaultCommand", {[this](auto leftX, auto leftY, auto rightX, auto rightY){swerve.Drive(-units::meters_per_second_t{leftY}, -units::meters_per_second_t{leftX}, -units::radians_per_second_t{rightX}, true, true);}, &swerve, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualEndEffector", {[this](auto leftX, auto leftY, auto rightX, auto rightY){endEffector.SetPercent(leftY);}, &endEffector, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualExtender", {[this](auto leftX, auto leftY, auto rightX, auto rightY){extender.SetPercent(rightY);}, &extender, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualElbow", {[this](auto leftX, auto leftY, auto rightX, auto rightY){elbow.SetPercent(rightY);}, &elbow, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"ManualWrist", {[this](auto leftX, auto leftY, auto rightX, auto rightY){wrist.SetPercent(leftY);}, &wrist, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND}},
   {"SemiAutoArmMove", {[this](auto leftX, auto leftY, auto rightX, auto rightY){elbow.SetPosition(elbow.GetPosition() + 3 * leftY);}, &elbow, COMETS3357::Controller::JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND }}
  };

  COMETS3357::ControllerMap controllerMap{buttonActionMap, joystickActionMap, "CompControllerMap", };
  COMETS3357::Autons autos{&swerve, buttonActionMap};

  void ConfigureBindings();
};
