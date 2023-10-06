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
#include "COMETS3357/Subsystems/Vision/LimelightSubsystem.h"

#include "Subsystems/ElbowSubsystem.h"
#include "Subsystems/EndEffectorSubsystem.h"
#include "Subsystems/ExtenderSubsystem.h"
#include "Subsystems/WristSubsystem.h"

#include "Subsystems/LEDs.h"

#include "Commands/SetPositionCommand.h"
#include "Commands/PlacementCommand.h"
#include "Commands/AutoRetractCommand.h"
#include "Commands/EjectCommand.h"

#include <frc2/command/SequentialCommandGroup.h>
#include "Commands/ConeFlipCommand.h"
#include "Commands/Wait.h"

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
  COMETS3357::LimelightSubsystem limelight{};
  COMETS3357::SwerveSubsystem swerve{"Swerve"};
  
  ElbowSubsystem elbow{};
  EndEffectorSubsystem endEffector{};
  ExtenderSubsystem extender{};
  WristSubsystem wrist{};
  LEDs LED{};

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
  EjectCommand ejectPress{&endEffector, true};
  EjectCommand ejectRelease{&endEffector, false};

  frc2::InstantCommand homePos{[this](){homePosition.Schedule();}, {}};
  frc2::InstantCommand eject{[this](){ejectPress.Schedule();}, {}};
  frc2::InstantCommand stopEject{[this](){ejectRelease.Schedule();}, {}};
  frc2::InstantCommand highPlace{[this](){highConePosition.Schedule();}, {}};
  frc2::InstantCommand lowerElbowWithRequire{[this](){elbow.SetPosition(230);}, {&elbow}};
  frc2::InstantCommand lowerElbow{[this](){lowerElbowWithRequire.Schedule();}, {}};
  frc2::InstantCommand coneFlash{[this](){LED.SetLEDCode('g');}, {&LED}};
  frc2::InstantCommand cubeFlash{[this](){LED.SetLEDCode('e');}, {&LED}};
  frc2::InstantCommand stopFlash{[this](){LED.SetLEDCode('n');}, {&LED}};

  Wait w1{&timer,1.75_s};
  Wait w2{&timer,0.4_s};
  Wait w3{&timer,0.1_s};
  Wait w4{&timer,0.5_s};

  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> buttonActionMap 
  {
    {"HomePosition", std::make_shared<frc2::InstantCommand>(homePos)},
    {"HighPosition", std::make_shared<PlacementCommand>(&endEffector, highCubePosition, highConePosition)},
    {"MidPosition", std::make_shared<PlacementCommand>(&endEffector, midCubePosition, midConePosition)},
    {"LowPosition", std::make_shared<PlacementCommand>(&endEffector, lowCubePosition, lowConePosition)},
    {"UpRightConePosition", std::make_shared<AutoRetractCommand>(upRightConePosition, homePosition, &endEffector, 0)},
    {"SideConePosition", std::make_shared<AutoRetractCommand>(sideConePosition, homePosition, &endEffector, 0)},
    {"CubePosition", std::make_shared<AutoRetractCommand>(cubePosition, homePosition, &endEffector, 0)},
    {"SingleSubPosition", std::make_shared<AutoRetractCommand>(singleSubPosition, homePosition, &endEffector, 0)},
    {"DoubleSubPosition", std::make_shared<AutoRetractCommand>(doubleSubPosition, homePosition, &endEffector, 0)},
    {"EjectOnPress", std::make_shared<frc2::InstantCommand>(eject)},
    {"EjectOnRelease", std::make_shared<frc2::InstantCommand>(stopEject)},
    {"ConeFlip", std::make_shared<ConeFlipCommand>(&wrist)},
    {"HighConePlacement", std::make_shared<frc2::InstantCommand>(highPlace)},
    {"AutonConePlaceCommand", std::make_shared<frc2::SequentialCommandGroup>(highPlace, w1, lowerElbow, w2, eject, w3, homePos)},
    {"AutonEnd", std::make_shared<frc2::SequentialCommandGroup>(w4, homePos)},
    {"ConeFlash", std::make_shared<frc2::InstantCommand>(coneFlash)},
    {"CubeFlash", std::make_shared<frc2::InstantCommand>(cubeFlash)},
    {"StopFlash", std::make_shared<frc2::InstantCommand>(stopFlash)}
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

  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> autonActionMap
  {
    {"HighConePlace", std::make_shared<frc2::SequentialCommandGroup>(highConePosition,  homePosition)},
    {"CubePickup", std::make_shared<frc2::SequentialCommandGroup>(cubePosition, frc2::WaitCommand(2_s), homePosition)},
    {"HighCubePlace", std::make_shared<frc2::SequentialCommandGroup>(highCubePosition, frc2::WaitCommand(1_s), EjectCommand(&endEffector, true), frc2::WaitCommand(1_s), EjectCommand(&endEffector, false), homePosition)},
    {"MidCubePlace", std::make_shared<frc2::SequentialCommandGroup>(midCubePosition, frc2::WaitCommand(1_s), EjectCommand(&endEffector, true), frc2::WaitCommand(1_s), EjectCommand(&endEffector, false), homePosition)}
  };

  COMETS3357::ControllerMap controllerMap{buttonActionMap, joystickActionMap, "CompControllerMap", };
  COMETS3357::Autons autos{&swerve, buttonActionMap};

  void ConfigureBindings();
};
