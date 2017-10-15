#include "runAction.hh"
#include "g4root.hh"
#include "G4SystemOfUnits.hh"
#include "steppingAction.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"

RunAction::RunAction(SteppingAction* steppingAction) : G4UserRunAction(),fSteppingAction(steppingAction)
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager* analysis = G4AnalysisManager::Instance();

	analysis->OpenFile("copperBlock");

	analysis->SetFirstHistoId(1);

	analysis->CreateH1("gamma","Energy of gamma",30,0.,3.0*MeV);
	analysis->CreateH1("electron","Energy of electrons",30,0.,3.0*MeV);
}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager* analysis = G4AnalysisManager::Instance();

	G4cout << "\n" << "Number of gamma above threshold (2.5 MeV): " << fSteppingAction->GetCounter() << "\n";

	analysis->Write();
	analysis->CloseFile();

	delete G4AnalysisManager::Instance(); 
}
