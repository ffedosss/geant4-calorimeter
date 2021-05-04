

#include "GammaDetPrimaryGeneratorAction.hh"
#include "GammaDetPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetPrimaryGeneratorAction::GammaDetPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   fParticleGun(0) /*, fParticleGun1(0)*/
{
  G4int n_particle = 1;
 // fParticleGun = new G4ParticleGun(n_particle);

  //create a messenger for this class
  fGunMessenger = new GammaDetPrimaryGeneratorMessenger(this);
  //
  
  //default kinematic
  //
 /* G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e+");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleTime(0.0*ns);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0*cm,0.0*cm,0.0*cm));
  fParticleGun->SetParticlePosition(G4ThreeVector(-0.9*cm,0.0*cm,0.0*cm));
  fParticleGun->SetParticleEnergy(2.0*GeV);


  fParticleGun1 = new G4ParticleGun(n_particle);
  fParticleGun1->SetParticleDefinition(particle);
  fParticleGun1->SetParticleTime(0.02*ns);
  fParticleGun1->SetParticleMomentumDirection(G4ThreeVector(1.0*cm,0.0*cm,0.0*cm));
  fParticleGun1->SetParticlePosition(G4ThreeVector(0.1*cm,0.0*cm,0.0*cm));
  fParticleGun1->SetParticleEnergy(2.0*GeV);*/

   fParticleGun = new G4GeneralParticleSource();
    
    fParticleGun->SetParticleDefinition(G4ParticleTable::
                        GetParticleTable()->FindParticle("gamma"));
    
    /*// Position distribution
    G4SPSPosDistribution *vPosDist =
        fParticleGun->GetCurrentSource()->GetPosDist();
    vPosDist->SetPosDisType("Volume");
    vPosDist->SetPosDisShape("Sphere");
    vPosDist->SetCentreCoords(G4ThreeVector(-2.49*cm,0.0*cm,0.0*cm));
    vPosDist->SetBeamSigmaInR(.05 * mm);
    
    // Angular distribution
    G4SPSAngDistribution *vAngDist =
        fParticleGun->GetCurrentSource()->GetAngDist();
    vAngDist->DefineAngRefAxes("angref1",G4ThreeVector(1.,0.,0));
    vAngDist->DefineAngRefAxes("angref2",G4ThreeVector(1.,0.,0.));
    vAngDist->SetAngDistType("iso");
   vAngDist->SetBeamSigmaInAngX(0.001 * rad);
   vAngDist->SetBeamSigmaInAngY(0.001 * rad);
   */
	fParticleGun->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
    // Energy distribution
    G4SPSEneDistribution *vEneDist = fParticleGun->GetCurrentSource()->GetEneDist();
    //vEneDist->SetEnergyDisType("Mono");
    vEneDist->SetMonoEnergy(0.001 * GeV);
  



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetPrimaryGeneratorAction::~GammaDetPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fParticleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
  G4double y0 = 1*cm, z0= 1*cm, sigma = 3*cm;
    y0 =  G4RandGauss::shoot( y0, sigma);;
    z0 =  G4RandGauss::shoot( z0, sigma);; 
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0*cm,0.0*cm,0.0*cm));
    //fParticleGun->SetParticlePosition(G4ThreeVector(-9.0*cm,y0,z0));
 // fParticleGun->SetParticlePosition(G4ThreeVector(1.0*cm,0.0*cm,0.0*cm));
	fParticleGun->GeneratePrimaryVertex(anEvent);
	//fParticleGun1->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 fParticleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
