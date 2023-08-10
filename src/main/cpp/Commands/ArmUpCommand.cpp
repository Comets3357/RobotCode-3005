#include "commands/ArmUpCommand.h"
#include "frc/smartdashboard/SmartDashboard.h"


ArmUpCommand::ArmUpCommand(ArmSubsystem* subsystem) : armSubsystem{subsystem}
{
    AddRequirements(armSubsystem);
}

void ArmUpCommand::Initialize()
{
    armSubsystem->SetPosition(100);
    
}

void ArmUpCommand::Execute()
{

}

bool ArmUpCommand::IsFinished()
{
    return true;
}

void ArmUpCommand::End(bool interrupted)
{

}