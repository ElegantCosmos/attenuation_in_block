#include "steppingAction.hh"
#include "G4Step.hh"
#include "g4root.hh"
#include "G4VProcess.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	G4Track* track = step->GetTrack();
	
	if (track->GetDefinition() == G4Gamma::GammaDefinition())
	{
		G4StepPoint* postStep = step->GetPostStepPoint();
		assert(postStep);
		//G4VPhysicalVolume* volume = postStep->GetTouchableHandle()->GetVolume();
		//if (!volume)
		//{
		//	G4ThreeVector momentumDirection = step->GetTrack()->GetMomentumDirection();
		//	if (momentumDirection.x() > 0)
		//	{
		//		G4double energy = postStep->GetKineticEnergy();
		//		
		//		if (energy > 2.5){counter++;}

		//		G4AnalysisManager* analysis = G4AnalysisManager::Instance();
		//		analysis->FillH1(1,energy);
		//	}
		//}
		G4StepPoint* preStep = step->GetPreStepPoint();
		assert(preStep);
		//std::cout << std::endl;
		//std::cout << "step->GetTrack()->GetMomentumDirection() " << step->GetTrack()->GetMomentumDirection() << std::endl;
		//std::cout << "preStep->GetMomentumDirection() " << preStep->GetMomentumDirection() << std::endl;
		//std::cout << "postStep->GetMomentumDirection() " << postStep->GetMomentumDirection() << std::endl;
		//std::cout << "postStep - preStep " << (postStep->GetPosition() - preStep->GetPosition())/(postStep->GetPosition() - preStep->GetPosition()).mag() << std::endl;
		const G4int parentID = step->GetTrack()->GetParentID();
		if (parentID == 0 && step->IsLastStepInVolume() && preStep->GetPhysicalVolume()->GetName() == "Box")
		{
			G4ThreeVector momentumDirection = step->GetTrack()->GetMomentumDirection();
			if (momentumDirection.x() > 0)
			{
				G4double energy = postStep->GetKineticEnergy();

				if (energy > 2.5){counter++;}

				G4AnalysisManager* analysis = G4AnalysisManager::Instance();
				std::cout << "analysis->Fill()" << std::endl;
				analysis->FillH1(1,energy);
			}
			else
			{
				std::cout << "oposite direction." << std::endl;
			}
		}
	}

	if (track->GetDefinition() == G4Electron::ElectronDefinition())
	{
		G4StepPoint* postStep = step->GetPostStepPoint();
		G4VPhysicalVolume* volume = postStep->GetTouchableHandle()->GetVolume();
		if (!volume)
		{
			G4ThreeVector momentumDirection = step->GetTrack()->GetMomentumDirection();
			if (momentumDirection.x() > 0)
			{
				G4double energy = postStep->GetKineticEnergy();

				G4AnalysisManager* analysis = G4AnalysisManager::Instance();
				analysis->FillH1(2,energy);
			}
		}
	}
}
