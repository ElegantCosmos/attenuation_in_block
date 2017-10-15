#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "detectorConstruction.hh"
//#include "physicsList.hh"
#include "primaryGeneratorAction.hh"
#include "runAction.hh"
#include "steppingAction.hh"
#include "eventAction.hh"
#include "Randomize.hh"

#include "PhysicsList.hh"

int main(int argc, char** argv)
{
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
	G4long seed = time(NULL);
	CLHEP::HepRandom::setTheSeed(seed);

	G4RunManager* runManager = new G4RunManager();

	runManager->SetUserInitialization(new DetectorConstruction());
	//runManager->SetUserInitialization(new PhysicsList());
  PhysicsList *aPhysicsList = new PhysicsList();
  runManager->SetUserInitialization(aPhysicsList);
  aPhysicsList->SelectPhysicsList("Livermore_EM");

	runManager->SetUserAction(new PrimaryGeneratorAction());

	SteppingAction* steppingAction = new SteppingAction;
	runManager->SetUserAction(steppingAction);

	RunAction* runAction = new RunAction(steppingAction);
	runManager->SetUserAction(runAction);

	EventAction* eventAction = new EventAction();
	runManager->SetUserAction(eventAction);

	runManager->Initialize();
	
	//Visualization

	//G4VisManager* visManager = new G4VisExecutive;
	//visManager->Initialize();

	//G4UImanager* UImanager = G4UImanager::GetUIpointer();

	//G4UIExecutive* ui = new G4UIExecutive(argc, argv);

	//UImanager->ApplyCommand("/run/verbose 1");
	//UImanager->ApplyCommand("/event/verbose 1");
	//UImanager->ApplyCommand("/tracking/verbose 1");
	//UImanager->ApplyCommand("/control/execute vis.mac");

	//ui->SessionStart();
	//delete ui;
	
	//delete visManager;

	int numberOfEvents = 100000;
	runManager->BeamOn(numberOfEvents);

	delete runManager;

	return 0;
}
