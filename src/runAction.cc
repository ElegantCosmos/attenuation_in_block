#include "G4RunManager.hh"

#include "statisticsLogger.hh"
#include "steppingAction.hh"
#include "runAction.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{}

void RunAction::EndOfRunAction(const G4Run*)
{
  StatisticsLogger* logger = StatisticsLogger::GetInstance();
  G4RunManager* runManager = G4RunManager::GetRunManager();
  const SteppingAction* steppingAction = dynamic_cast<const SteppingAction*>(runManager->GetUserSteppingAction());
  logger->SetFinalNPrimaries(steppingAction->GetPrimaryCounter());
  logger->SetFinalNPrimariesAboveROILowerBound(steppingAction->GetPrimaryAboveROILowerBoundCounter());
  logger->SetFinalNGammas(steppingAction->GetGammaCounter());
  logger->SetFinalNGammasAboveROILowerBound(steppingAction->GetGammaAboveROILowerBoundCounter());
  logger->SetFinalNBetas(steppingAction->GetBetaCounter());
  logger->SetFinalNBetasAboveROILowerBound(steppingAction->GetBetaAboveROILowerBoundCounter());
  logger->SetFinalNAlphas(steppingAction->GetAlphaCounter());
  logger->SetFinalNAlphasAboveROILowerBound(steppingAction->GetAlphaAboveROILowerBoundCounter());
  logger->AddNtupleRow();
  logger->WriteAndClose();
}
