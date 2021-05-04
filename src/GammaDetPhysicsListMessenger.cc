
#include "GammaDetPhysicsListMessenger.hh"

#include "GammaDetPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetPhysicsListMessenger::
  GammaDetPhysicsListMessenger(GammaDetPhysicsList* pPhys) 
  : G4UImessenger(),
    fPhysicsList(pPhys)
{
  fGammaDetDir = new G4UIdirectory("/GammaDet/");
  fGammaDetDir->SetGuidance("UI commands of this example");

  fPhysDir = new G4UIdirectory("/GammaDet/phys/");
  fPhysDir->SetGuidance("PhysicsList control");
 
  fVerboseCmd = new G4UIcmdWithAnInteger("/GammaDet/phys/verbose",this);
  fVerboseCmd->SetGuidance("set verbose for physics processes");
  fVerboseCmd->SetParameterName("verbose",true);
  fVerboseCmd->SetDefaultValue(1);
  fVerboseCmd->SetRange("verbose>=0");
  fVerboseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  fCerenkovCmd =
           new G4UIcmdWithAnInteger("/GammaDet/phys/cerenkovMaxPhotons",this);
  fCerenkovCmd->SetGuidance("set max nb of photons per step");
  fCerenkovCmd->SetParameterName("MaxNumber",false);
  fCerenkovCmd->SetRange("MaxNumber>=0");
  fCerenkovCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetPhysicsListMessenger::~GammaDetPhysicsListMessenger()
{
  delete fVerboseCmd;
  delete fCerenkovCmd;
  delete fPhysDir;
  delete fGammaDetDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetPhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue)
{
  if( command == fVerboseCmd )
   {fPhysicsList->SetVerbose(fVerboseCmd->GetNewIntValue(newValue));}

  if( command == fCerenkovCmd )
   {fPhysicsList->
              SetNbOfPhotonsCerenkov(fCerenkovCmd->GetNewIntValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
