// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "COMETS3357/CometsRobot/CometsRobot.h"

#include <stdint.h>

#include <cstdio>
#include <utility>

#include <hal/DriverStation.h>
#include <hal/FRCUsageReporting.h>
#include <hal/Notifier.h>

#include "frc/Errors.h"
#include "frc/Timer.h"

using namespace COMETS3357;

void CometsRobot::StartCompetition() {
  RobotInit();

  if constexpr (IsSimulation()) {
    SimulationInit();
  }

  // Tell the DS that the robot is ready to be enabled
  std::puts("\n********** COMETS Robot program startup complete **********");
  HAL_ObserveUserProgramStarting();

  // Loop forever, calling the appropriate mode-dependent function
  while (true) {
    // We don't have to check there's an element in the queue first because
    // there's always at least one (the constructor adds one). It's reenqueued
    // at the end of the loop.
    auto callback = m_callbacks.pop();

    int32_t status = 0;
    HAL_UpdateNotifierAlarm(
        m_notifier, static_cast<uint64_t>(callback.expirationTime * 1e6),
        &status);
    FRC_CheckErrorStatus(status, "UpdateNotifierAlarm");

    uint64_t curTime = HAL_WaitForNotifierAlarm(m_notifier, &status);
    if (curTime == 0 || status != 0) {
      break;
    }

    callback.func();

    callback.expirationTime += callback.period;
    m_callbacks.push(std::move(callback));

    // Process all other callbacks that are ready to run
    while (static_cast<uint64_t>(m_callbacks.top().expirationTime * 1e6) <=
           curTime) {
      callback = m_callbacks.pop();

      callback.func();

      callback.expirationTime += callback.period;
      m_callbacks.push(std::move(callback));
    }
  }
}

void CometsRobot::EndCompetition() {
  int32_t status = 0;
  HAL_StopNotifier(m_notifier, &status);
}

CometsRobot::CometsRobot(units::second_t period) : IterativeRobotBase(period) {
  m_startTime = frc::Timer::GetFPGATimestamp();
  AddPeriodic([=, this] { LoopFunc(); }, period);

  int32_t status = 0;
  m_notifier = HAL_InitializeNotifier(&status);
  FRC_CheckErrorStatus(status, "InitializeNotifier");
  HAL_SetNotifierName(m_notifier, "CometsRobot", &status);

  HAL_Report(HALUsageReporting::kResourceType_Framework,
             HALUsageReporting::kFramework_Timed);
}

CometsRobot::~CometsRobot() {
  int32_t status = 0;

  HAL_StopNotifier(m_notifier, &status);
  FRC_ReportError(status, "StopNotifier");

  HAL_CleanNotifier(m_notifier, &status);
}

void CometsRobot::AddPeriodic(std::function<void()> callback,
                             units::second_t period, units::second_t offset) {
  m_callbacks.emplace(callback, m_startTime, period, offset);
}