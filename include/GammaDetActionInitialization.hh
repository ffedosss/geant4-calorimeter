
#ifndef GammaDetActionInitialization_h
#define GammaDetActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class B4DetectorConstruction;

/// Action initialization class.
///

class GammaDetActionInitialization : public G4VUserActionInitialization
{
  public:
    GammaDetActionInitialization();
    virtual ~GammaDetActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

    virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};

#endif
