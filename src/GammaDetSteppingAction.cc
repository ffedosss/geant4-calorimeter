

#include "GammaDetSteppingAction.hh"
#include "GammaDetDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "Analysis.hh"

#include "G4SystemOfUnits.hh"

#include "G4VPhysicalVolume.hh"

#include "G4PhysicalConstants.hh"
#include "G4Gamma.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetSteppingAction::GammaDetSteppingAction()
: G4UserSteppingAction()
{ 
  fScintillationCounter = 0;
  fCerenkovCounter      = 0;
  fEventNumber = -1;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetSteppingAction::~GammaDetSteppingAction()
{ ; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetSteppingAction::UserSteppingAction(const G4Step* step)


	{	
		G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
		G4int eventNumber = G4RunManager::GetRunManager()->
                                              GetCurrentEvent()->GetEventID(); 
	if (eventNumber != fEventNumber) {
     fEventNumber = eventNumber;
	 fScintillationCounter = 0;
     fCerenkovCounter = 0;
	}

	static const double terahertz = 1.e+12*hertz;
	G4double Egamma;
	
	

  G4Track* track = step->GetTrack();

	const G4StepPoint* prePoint = step->GetPreStepPoint();
	const G4StepPoint* postPoint = step->GetPreStepPoint();
		G4ThreeVector pospre = prePoint->GetPosition();
		//G4ThreeVector pospost = postPoint->GetPosition();


  const G4DynamicParticle* dynParticle = track->GetDynamicParticle();
  const G4ParticleDefinition* particle = dynParticle->GetParticleDefinition();
  G4VPhysicalVolume* preVol = prePoint->GetPhysicalVolume();
  G4VPhysicalVolume* postVol = step->GetPostStepPoint()->GetPhysicalVolume();


   G4String ParticleName = track->GetDynamicParticle()->
                                 GetParticleDefinition()->GetParticleName();


  const std::vector<const G4Track*>* secondaries =
                                            step->GetSecondaryInCurrentStep();


 

  if (particle != G4Gamma::Gamma()) {
		  G4double Egamma;
		 
        Egamma = step->GetTrack()->GetKineticEnergy();
       		
		analysisManager->FillH1(1, Egamma / MeV);
		 G4double energdep;
			energdep = step->GetTotalEnergyDeposit();
							    		
		analysisManager->FillH1(2, energdep / eV);
		//analysisManager->FillNtupleDColumn(0, energdep / eV);
		//analysisManager->AddNtupleRow();
  }
 /* G4ThreeVector v3_rearposition = postPoint->GetPosition();
        float x_pos = v3_rearposition.x();
  if (x_pos > 1.*cm && particle == G4Gamma::Gamma() && prePoint->GetStepStatus() == fGeomBoundary && preVol != postVol){
	  if (preVol->GetName() =="vacuum")
		{
			
		
	  }}*/

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

