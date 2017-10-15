#include "G4UserRunAction.hh"
#include "globals.hh"

class SteppingAction;

class RunAction : public G4UserRunAction
{
public:
	RunAction(SteppingAction* steppingAction);
	virtual ~RunAction();

public:
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

private:
	SteppingAction* fSteppingAction;
};
