

#ifndef GammaDetPrimaryGeneratorMessenger_h
#define GammaDetPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class GammaDetPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GammaDetPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    GammaDetPrimaryGeneratorMessenger(GammaDetPrimaryGeneratorAction* );
    virtual ~GammaDetPrimaryGeneratorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
    GammaDetPrimaryGeneratorAction* fGammaDetAction;
    G4UIdirectory*                  fGunDir;
    G4UIcmdWithADoubleAndUnit*      fPolarCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
