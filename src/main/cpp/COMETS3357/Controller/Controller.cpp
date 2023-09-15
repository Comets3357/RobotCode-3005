#include "COMETS3357/Configs/ControllerMap.h"

using namespace COMETS3357;

Controller::Controller(int controllerSlot, std::unordered_map<std::string, std::shared_ptr<frc2::Command>> &buttonActions, std::unordered_map<std::string, std::tuple<std::function<void(double, double, double, double)>, frc2::Subsystem*, JoystickCommandMode>>& joystickActions) : slot{controllerSlot}, controller{controllerSlot}, buttonActionMap{buttonActions}, joystickActionMap{joystickActions}, controllerConnectionTrigger{[this]() {return frc::DriverStation::IsJoystickConnected(slot);}}
{

}

void Controller::SetButton(frc2::Trigger trigger, std::string button, std::pair<const std::string, picojson::value>& mode)
{
    if (mode.second.get(button).get<std::string>() != "NONE")
    {
        if (buttonActionMap.contains(mode.second.get(button).get<std::string>()))
        {
            (trigger && modeTriggers[mode.first]).WhileTrue(buttonActionMap[mode.second.get(button).get<std::string>()].get());
        }
        else if (modeTriggers.contains(mode.second.get(button).get<std::string>()))
        {
            (trigger && modeTriggers[mode.first]).WhileTrue(new frc2::RunCommand{[this, mode, button] {currentMode = mode.second.get(button).get<std::string>();}, {}});
        }
    }

    if (mode.second.get(button + "Pressed").get<std::string>() != "NONE")
    {
        if (buttonActionMap.contains(mode.second.get(button + "Pressed").get<std::string>()))
        {
            (trigger && modeTriggers[mode.first]).OnTrue(buttonActionMap.at(mode.second.get(button + "Pressed").get<std::string>()).get());
        }
        else if (modeTriggers.contains(mode.second.get(button + "Pressed").get<std::string>()))
        {
            (trigger && modeTriggers[mode.first]).OnTrue(new frc2::InstantCommand{[this, mode, button] {currentMode = mode.second.get(button + "Pressed").get<std::string>();}, {}});
        }
    }
    if (mode.second.get(button + "Released").get<std::string>() != "NONE")
    {
        if (buttonActionMap.contains(mode.second.get(button + "Pressed").get<std::string>()))
        {
            (trigger && modeTriggers[mode.first]).OnFalse(buttonActionMap.at(mode.second.get(button + "Released").get<std::string>()).get());
        }
        else if (modeTriggers.contains(mode.second.get(button + "Released").get<std::string>()))
        {
            (trigger && modeTriggers[mode.first]).OnFalse(new frc2::InstantCommand{[this, mode, button] {currentMode = mode.second.get(button + "Released").get<std::string>();}, {}});
        }
    }
}

void Controller::SetJoystickTrigger(frc2::Trigger trigger, std::string joystick, std::pair<const std::string, picojson::value>& mode, std::map<std::string, frc2::Trigger>& joystickTriggers)
{
    if (mode.second.get(joystick).get<std::string>() != "NONE")
    {
        if (joystickActionMap.contains(mode.second.get(joystick).get<std::string>()))
        {
            if (joystickTriggers.contains(mode.second.get(joystick).get<std::string>()))
            {
                joystickTriggers[mode.second.get(joystick).get<std::string>()] = (joystickTriggers[mode.second.get(joystick).get<std::string>()] || trigger);
            }
            else
            {
                joystickTriggers[mode.second.get(joystick).get<std::string>()] = trigger;
            }
        }
    }
}

void Controller::SetJoysticks(std::map<std::string, frc2::Trigger>& joystickTriggers, std::pair<const std::string, picojson::value>& mode)
{
    for (auto& joystickTrigger : joystickTriggers)
    {
        if (std::get<2>(joystickActionMap[joystickTrigger.first]) == JoystickCommandMode::JOYSTICK_DEADZONE_COMMAND)
        {
            frc2::Subsystem* sub = std::get<1>(joystickActionMap[joystickTrigger.first]);
            std::function<void(double, double, double, double)> function = std::get<0>(joystickActionMap[joystickTrigger.first]);
            (joystickTrigger.second && modeTriggers[mode.first]).WhileTrue(new frc2::RunCommand{[this, sub, function]{function(controller.GetLeftX(),controller.GetLeftY(),controller.GetRightX(),controller.GetRightY());},{sub}});
            (joystickTrigger.second && modeTriggers[mode.first]).OnFalse(new frc2::RunCommand{[this, sub, function]{function(0,0,0,0);}, {sub}});
        }
    }

    for (auto& defaultCommand : joystickActionMap)
    {
        if (std::get<2>(defaultCommand.second) == JoystickCommandMode::JOYSTICK_DEFAULT_COMMAND)
        {
            frc2::Subsystem* sub = std::get<1>(defaultCommand.second);
            std::function<void(double, double, double, double)> function = std::get<0>(defaultCommand.second);
            modeTriggers[mode.first].OnTrue(new frc2::InstantCommand{[this, sub, function]{sub->SetDefaultCommand(frc2::RunCommand{[this, function]{function(controller.GetLeftX(), controller.GetLeftY(), controller.GetRightX(), controller.GetRightY());},{sub}});},{}});
            sub->SetDefaultCommand(frc2::RunCommand{[this, function]{function(controller.GetLeftX(), controller.GetLeftY(), controller.GetRightX(), controller.GetRightY());},{sub}});
        }
    }
}

void Controller::InitController(std::string xboxDefaultMode, std::string taranusDefaultMode)
{
    if (frc::DriverStation::GetJoystickName(slot) == "FrSky Taranis Joystick")
    {
        currentMode = taranusDefaultMode;
    }
    else
    {
        currentMode = xboxDefaultMode;
    }
}

void Controller::InitController(picojson::value &controllers)
{
    if (frc::DriverStation::GetJoystickName(slot) == "FrSky Taranis Joystick")
    {
        currentMode = controllers.get<picojson::object>().at("Taranus").get("DefaultMode").get<std::string>();
    }
    else
    {
        currentMode = controllers.get<picojson::object>().at("XBOX").get("DefaultMode").get<std::string>();
    }

}

void Controller::LoadConfig(picojson::value &controllers)
{
    controllerConnectionTrigger.OnTrue(frc2::InstantCommand{[this,controllers]{InitController(controllers.get<picojson::object>().at("XBOX").get("DefaultMode").get<std::string>(), controllers.get<picojson::object>().at("Taranus").get("DefaultMode").get<std::string>());},{}}.IgnoringDisable(true));
    LoadControls(controllers);

}

bool Controller::LoadControls(picojson::value &controllers)
{
    
    if (true)//controller.IsConnected())
    {
        for (auto& controllerType : controllers.get<picojson::object>())
        {
            for (auto& mode : controllerType.second.get<picojson::object>())//controller.GetName()])
            {
                if (mode.first != "DefaultMode")
                {

                    modeTriggers[mode.first] = frc2::Trigger{[this, mode]{return currentMode == mode.first;}};
                }
            }

            for (auto& mode : controllerType.second.get<picojson::object>())//controller.GetName()])
            {
                //if (mode.first == "Taranus" && frc::DriverStation::GetJoystickName(slot) != "FrSky Taranis Joystick") break;
                if (mode.first != "DefaultMode")
                {

                    if (controllerType.first == "Taranus")
                    {
                        
                    }
                    else if (controllerType.first == "XBOX")
                    {
                        SetButton(frc2::Trigger{[this]{return controller.GetPOV() == 0;}}, "D-padUp", mode);
                        SetButton(frc2::Trigger{[this]{return controller.GetPOV() == 90;}}, "D-padRight", mode);
                        SetButton(frc2::Trigger{[this]{return controller.GetPOV() == 180;}}, "D-padDown", mode);
                        SetButton(frc2::Trigger{[this]{return controller.GetPOV() == 270;}}, "D-padLeft", mode);
                        SetButton(controller.RightStick(), "RightStickButton", mode);
                        SetButton(controller.LeftStick(), "LeftStickButton", mode);
                        SetButton(controller.A(), "AButton", mode);
                        SetButton(controller.B(), "BButton", mode);
                        SetButton(controller.X(), "XButton", mode);
                        SetButton(controller.Y(), "YButton", mode);
                        SetButton(controller.LeftTrigger(), "LeftTrigger", mode);
                        SetButton(controller.RightTrigger(), "RightTrigger", mode);
                        SetButton(controller.LeftBumper(), "LeftBumper", mode);
                        SetButton(controller.RightBumper(), "RightBumper", mode);
                        SetButton(controller.Start(), "StartButton", mode);
                        SetButton(controller.Back(), "BackButton", mode);

                        std::map<std::string, frc2::Trigger> joystickTriggers;

                        SetJoystickTrigger(frc2::Trigger{[this]{return frc::ApplyDeadband(controller.GetLeftY(), 0.08) != 0;}}, "LeftStickY", mode, joystickTriggers);
                        SetJoystickTrigger(frc2::Trigger{[this]{return frc::ApplyDeadband(controller.GetLeftX(), 0.08) != 0;}}, "LeftStickX", mode, joystickTriggers);
                        SetJoystickTrigger(frc2::Trigger{[this]{return frc::ApplyDeadband(controller.GetRightY(), 0.08) != 0;}}, "RightStickY", mode, joystickTriggers);
                        SetJoystickTrigger(frc2::Trigger{[this]{return frc::ApplyDeadband(controller.GetRightX(), 0.08) != 0;}}, "RightStickX", mode, joystickTriggers);

                        SetJoysticks(joystickTriggers, mode);
                    }
                }
            }
        }
        
    }
    else
    {
        return false;
    }
    return true;
}
