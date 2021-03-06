#ifndef EventAction_h
#define EventAction_h 1

#include "globals.hh"

#include "G4UserEventAction.hh"

/// Event action class
///

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);

private:
  G4int fEventNo;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
