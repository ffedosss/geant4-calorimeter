

#ifndef GammaDetSteppingAction_h
#define GammaDetSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

/// Stepping action class
/// 

class GammaDetSteppingAction : public G4UserSteppingAction
{
  public:
    GammaDetSteppingAction();
    virtual ~GammaDetSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    G4int fScintillationCounter;
    G4int fCerenkovCounter;
    G4int fEventNumber;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
