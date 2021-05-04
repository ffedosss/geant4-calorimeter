

#ifndef GammaDetPhysicsListMessenger_h
#define GammaDetPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GammaDetPhysicsList;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GammaDetPhysicsListMessenger: public G4UImessenger
{
  public:
    GammaDetPhysicsListMessenger(GammaDetPhysicsList* );
    virtual ~GammaDetPhysicsListMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
    GammaDetPhysicsList*  fPhysicsList;
 
    G4UIdirectory*        fGammaDetDir;
    G4UIdirectory*        fPhysDir;
    G4UIcmdWithAnInteger* fVerboseCmd;
    G4UIcmdWithAnInteger* fCerenkovCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
