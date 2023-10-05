#include "Commands/ConeFlipCommand.h"



ConeFlipCommand::ConeFlipCommand(WristSubsystem* wristSub)
{

    wrist = wristSub;

    AddRequirements({wristSub});
}



void ConeFlipCommand::Initialize()
{
    wrist->SetPosition(135);
    
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