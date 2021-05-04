

#ifndef GammaDetRunAction_h
#define GammaDetRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;

class GammaDetRunAction : public G4UserRunAction
{
  public:
    GammaDetRunAction();
    virtual ~GammaDetRunAction();

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);

  private:
    G4Timer* fTimer;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*GammaDetRunAction_h*/
