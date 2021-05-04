

#include "GammaDetActionInitialization.hh"
#include "GammaDetPrimaryGeneratorAction.hh"
#include "GammaDetRunAction.hh"
#include "GammaDetSteppingAction.hh"
#include "GammaDetStackingAction.hh"
#include "GammaDetSteppingVerbose.hh"
#include "EventAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetActionInitialization::GammaDetActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetActionInitialization::~GammaDetActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetActionInitialization::BuildForMaster() const
{
  SetUserAction(new GammaDetRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetActionInitialization::Build() const
{
  SetUserAction(new GammaDetPrimaryGeneratorAction());
  SetUserAction(new GammaDetRunAction());
  SetUserAction(new GammaDetSteppingAction());
  SetUserAction(new GammaDetStackingAction());
  SetUserAction(new EventAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose*
               GammaDetActionInitialization::InitializeSteppingVerbose() const
{
  return new GammaDetSteppingVerbose();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
