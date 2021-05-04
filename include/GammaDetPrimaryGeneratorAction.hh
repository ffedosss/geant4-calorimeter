

#ifndef GammaDetPrimaryGeneratorAction_h
#define GammaDetPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

//class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;
class GammaDetPrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GammaDetPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GammaDetPrimaryGeneratorAction();
    virtual ~GammaDetPrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);

  private:
    //G4ParticleGun* fParticleGun;
	//G4ParticleGun* fParticleGun1;
	G4GeneralParticleSource* fParticleGun;
    GammaDetPrimaryGeneratorMessenger* fGunMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*GammaDetPrimaryGeneratorAction_h*/
