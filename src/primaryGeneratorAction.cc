#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "statisticsLogger.hh"
#include "primaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():
  G4VUserPrimaryGeneratorAction(),
  particleGun(0)
{
  G4int nPrimaries = 1;
  particleGun = new G4ParticleGun(nPrimaries);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

  StatisticsLogger* logger = StatisticsLogger::GetInstance();
  logger->SetPrimaryPDGEncoding(particle->GetPDGEncoding());

  G4ThreeVector position = G4ThreeVector(-10.0*m, 0, 0);
  G4ThreeVector momentumDirection = G4ThreeVector(1.0, 0, 0);
  G4double energy = 2.615*MeV;
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticlePosition(position);
  particleGun->SetParticleMomentumDirection(momentumDirection);
  particleGun->SetParticleEnergy(energy);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
}
