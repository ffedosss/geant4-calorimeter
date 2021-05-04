

class GammaDetSteppingVerbose;

#ifndef GammaDetSteppingVerbose_h
#define GammaDetSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GammaDetSteppingVerbose : public G4SteppingVerbose
{
 public:

   GammaDetSteppingVerbose();
   virtual ~GammaDetSteppingVerbose();

   virtual void StepInfo();
   virtual void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
