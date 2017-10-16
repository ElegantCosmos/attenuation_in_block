#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

  const G4ParticleGun* GetParticleGun() const {return particleGun;}

private:
  G4ParticleGun* particleGun;
};
