

#include "GammaDetStackingAction.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetStackingAction::GammaDetStackingAction()
  : G4UserStackingAction(),
    fScintillationCounter(0), fCerenkovCounter(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetStackingAction::~GammaDetStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
GammaDetStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        fScintillationCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
        fCerenkovCounter++;
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetStackingAction::NewStage()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetStackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
