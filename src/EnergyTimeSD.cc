#include "EnergyTimeSD.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4Electron.hh"
#include "G4OpticalPhoton.hh"
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include "G4SystemOfUnits.hh"

#include "Analysis.hh"
EnergyTimeSD::EnergyTimeSD(G4String name) :
  G4VSensitiveDetector(name)
{
    collectionName.insert("energy_time");
}


G4bool EnergyTimeSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{
    // Task 4d.1: Get total energy deposit, global time and position from the step
	G4Track* track = aStep->GetTrack();
	G4String ParticleName = track->GetDynamicParticle()->
                                 GetParticleDefinition()->GetParticleName();
	G4double edep = aStep->GetTotalEnergyDeposit();
	
	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector posit = preStepPoint->GetPosition();
	G4double Time = preStepPoint->GetGlobalTime();
	G4int trackID                = track->GetTrackID();			 //ID of the track
	G4int parentID               = track->GetParentID();
	G4ThreeVector mom = track->GetMomentumDirection();
	G4double KinE = track->GetKineticEnergy();
		    		
	 G4AnalysisManager* analysis = G4AnalysisManager::Instance();
   	EnergyTimeHit* hit = new EnergyTimeHit();
    // Task 4d.1: Fill in the hit properties
		
		//hit->SetMoment(mom);
	/*G4double Time = 0;
				G4double posX = preStepPoint->GetPosition().x() / mm;
			for (int i = 1; i < 10000; i++)
						{
							if (posX = 0.1+ 0.00029*i*mm) {Time = i * (preStepPoint->GetGlobalTime() / ns);
							
			*/



	// if (trackID > 1 && ( ParticleName == "e-" || ParticleName == "e+")  /* KinE > 5*eV &&    && track->GetMomentumDirection().x()>0.  */ )
	//{}
			hit->SetTime(Time);
			hit->SetKinEnergy(KinE);
	        hit->SetMoment(mom);
		    hit->SetDeltaEnergy(edep);
		
    	    hit->SetPosition(posit);
   
	fHitsCollection ->insert(hit);
	return true;
}

void EnergyTimeSD::Initialize(G4HCofThisEvent* hcof)
{
    fHitsCollection = new EnergyTimeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);
}
