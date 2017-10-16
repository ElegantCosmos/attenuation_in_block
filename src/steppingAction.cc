#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Alpha.hh"

#include "statisticsLogger.hh"
#include "steppingAction.hh"

SteppingAction::SteppingAction()
{
  counter_primary = 0;
  counter_primary_aboveROILowerBound = 0;
  counter_gamma = 0;
  counter_gamma_aboveROILowerBound = 0;
  counter_beta = 0;
  counter_beta_aboveROILowerBound = 0;
  counter_alpha = 0;
  counter_alpha_aboveROILowerBound = 0;
  ROI_upperBound = 2.570*MeV;
  ROI_lowerBound = 2.470*MeV;
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();
  const G4StepPoint* preStep = step->GetPreStepPoint();
  assert(preStep);
  const G4StepPoint* postStep = step->GetPostStepPoint();
  assert(postStep);

  if (track->GetParentID() == 0) { // primary
    if (step->IsLastStepInVolume() && // last step of in attenuator
        preStep->GetPhysicalVolume()->GetName() == "Box") {
      const G4ThreeVector& momentumDirection = step->GetTrack()->GetMomentumDirection();
      if (momentumDirection.x() > 0) {
        G4double energy = postStep->GetKineticEnergy();

        counter_primary++;
        if (energy > ROI_lowerBound) counter_primary_aboveROILowerBound++;

        StatisticsLogger* logger = StatisticsLogger::GetInstance();
        logger->FillPrimaryHistogram(energy);
      } else {
        //G4cout << "Primary is going in opposite direction." << G4endl;
      }
    }
  }

  if (track->GetDefinition() == G4Gamma::GammaDefinition()) { // gamma
    if (step->IsLastStepInVolume() && // last step in attenuator
        preStep->GetPhysicalVolume()->GetName() == "Box") {
      const G4ThreeVector& momentumDirection = step->GetTrack()->GetMomentumDirection();
      if (momentumDirection.x() > 0) {
        G4double energy = postStep->GetKineticEnergy();

        counter_gamma++;
        if (energy > ROI_lowerBound) counter_gamma_aboveROILowerBound++;

        StatisticsLogger* logger = StatisticsLogger::GetInstance();
        logger->FillGammaHistogram(energy);
      } else {
        //G4cout << "Gamma is going in opposite direction." << G4endl;
      }
    }
  } else if (track->GetDefinition() == G4Electron::ElectronDefinition()) { // beta
    if (step->IsLastStepInVolume() && // last step in attenuator
        preStep->GetPhysicalVolume()->GetName() == "Box") {
      const G4ThreeVector& momentumDirection = step->GetTrack()->GetMomentumDirection();
      if (momentumDirection.x() > 0) {
        G4double energy = postStep->GetKineticEnergy();

        counter_beta++;
        if (energy > ROI_lowerBound) counter_beta_aboveROILowerBound++;

        StatisticsLogger* logger = StatisticsLogger::GetInstance();
        logger->FillBetaHistogram(energy);
      } else {
        //G4cout << "Beta is going in opposite direction." << G4endl;
      }
    }
  } else if (track->GetDefinition() == G4Alpha::AlphaDefinition()) { // alpha
    if (step->IsLastStepInVolume() && // last step in attenuator
        preStep->GetPhysicalVolume()->GetName() == "Box") {
      const G4ThreeVector& momentumDirection = step->GetTrack()->GetMomentumDirection();
      if (momentumDirection.x() > 0) {
        G4double energy = postStep->GetKineticEnergy();

        counter_alpha++;
        if (energy > ROI_lowerBound) counter_alpha_aboveROILowerBound++;

        StatisticsLogger* logger = StatisticsLogger::GetInstance();
        logger->FillAlphaHistogram(energy);
      } else {
        //G4cout << "Alpha is going in opposite direction." << G4endl;
      }
    }
  }
}
