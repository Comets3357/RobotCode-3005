#include "Commands/Wait.h"



    Wait::Wait(COMETS3357::TimerSubsystem* timer, units::second_t time)
    {
        t = timer;
        duration = time;
    }

    void Wait::Initialize()
    {
        endTime = duration + t->timeSinceEnabled;
    }

    void Wait::Execute()
    {
        frc::SmartDashboard::PutNumber("TIMERJSAHD", (double)endTime);
        frc::SmartDashboard::PutNumber("TIMERJSAHD2", (double)t->timeSinceEnabled);
    }

    bool Wait::IsFinished()
    {
        return t->timeSinceEnabled > endTime;
    }

    void Wait::End(bool interrupted)
    {

    }
