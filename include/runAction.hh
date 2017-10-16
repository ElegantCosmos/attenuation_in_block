#include "G4UserRunAction.hh"

class RunAction : public G4UserRunAction {
public:
  RunAction();
  virtual ~RunAction();

public:
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
};
