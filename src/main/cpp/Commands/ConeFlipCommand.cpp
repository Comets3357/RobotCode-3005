#include "Commands/ConeFlipCommand.h"



ConeFlipCommand::ConeFlipCommand(WristSubsystem* wristSub)
{

    wrist = wristSub;

    AddRequirements({wrist});
}

void ConeFlipCommand::Initialize()
{
    if (wrist->GetPosition() < 135 || wrist->GetPosition() > 315)
    {
        wrist->SetPosition(225);
    }
    else
    {
        wrist->SetPosition(45);
    }
    
}

void ConeFlipCommand::Execute()
{

}

bool ConeFlipCommand::IsFinished()
{
    return true;
}

void ConeFlipCommand::End(bool interrupted)
{

}