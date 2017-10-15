#include "primaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction(),
	particleGun(0)
{
	G4int nofParticles = 1;
	particleGun = new G4ParticleGun(nofParticles);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "gamma";
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

	G4ThreeVector position = G4ThreeVector(-10.0*m, 0, 0);
	G4ThreeVector momentumDirection = G4ThreeVector(1.0, 0, 0);
	G4double energy = 2.6*MeV;
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
