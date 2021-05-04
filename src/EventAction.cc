#include "EventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"

#include "EnergyTimeHit.hh"
#include <fstream>
#include <iostream>
using namespace std;
 
//fout << "collectiontime" << "    " << "edepos"  << endl;

void EventAction::EndOfEventAction(const G4Event* event)
{//ofstream fout("hit.dat", ios::app); 
    
     G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    	G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

   
	G4int fabsorberETId = sdm->GetCollectionID("absorberET/energy_time");

 // Hit collections IDs to be looped over ("Don't Repeat Yourself" principle)
    vector<G4int> hitCollectionIds = {fabsorberETId};
	
    for (G4int collectionId : hitCollectionIds)
    {
		if (collectionId == -1)
   			 {

				 G4cout << "EventAction: scorer ID: " << collectionId << G4endl;
				continue;
    			}
				EnergyTimeHitsCollection* hitCollection = dynamic_cast<EnergyTimeHitsCollection*>(hcofEvent->GetHC(collectionId));

        // Task 4d.3: Uncomment the following block
         if (hitCollection)
        {
            			
				G4double collectiontime; 
				G4double edepos;
			G4double h_E_tmp;
			
           		for (auto hit: *hitCollection->GetVector())
            			{
							
							
				
				
					G4double H_E_tmp = hit->GetDeltaEnergy() / MeV;
				G4double time = 0 ;
			    G4double posX;
				posX = hit->GetPosition().x() / cm;		
				G4double coeff = 0;
				if (posX < 0.28) time = hit->GetTime() / ns;	
				
				G4double Time = 0;

			if (H_E_tmp > 0.0000036 * MeV) 
				{
					 Time = hit->GetTime() / ns;
					

				}
			collectiontime = ((hit->GetPosition().x()/cm)/(0.0023*cm)) ;


							G4ThreeVector v3_unitX(1.0, 0.0, 0.0);
							G4double tetta = acos(((hit->GetMoment())*v3_unitX)/(sqrt((hit->GetMoment())*(hit->GetMoment()))*sqrt(v3_unitX*v3_unitX)));
              			  // Task 4d.3: Fill ntuple columns (one prepared for you already)
               			analysis->FillNtupleDColumn(0, hit->GetDeltaEnergy() / eV);
						analysis->FillNtupleDColumn(1, time);  // (hit->GetPosition().x()/cm)/(0.0023*cm))/ns + (
						analysis->FillNtupleDColumn(2, hit->GetPosition().x() / mm);
						analysis->FillNtupleDColumn(3, hit->GetPosition().y() / mm);
						analysis->FillNtupleDColumn(4, hit->GetPosition().z() / mm);
						analysis->FillNtupleDColumn(5, hit->GetKinEnergy() / MeV);
						analysis->FillNtupleDColumn(6, tetta/ rad);
						analysis->FillNtupleDColumn(7, hit->GetMoment().x());
						analysis->AddNtupleRow();
						analysis->FillH1(3 , Time);

						analysis->FillH2(1 , hit->GetPosition().x() / mm, hit->GetTime() / ns);
						analysis->FillH2(2 , hit->GetPosition().y() / mm, hit->GetPosition().z() / mm);
						analysis->FillH2(3 , hit->GetPosition().x() / mm, hit->GetPosition().z() / mm);

						
						//analysis->FillH1(8,  hit->GetKinEnergy()/ eV);
           if ((hit->GetPosition().x() / mm) < 1.0)  h_E_tmp += hit->GetDeltaEnergy() / keV;
           
    edepos = hit->GetDeltaEnergy() / keV;
	analysis->FillH2(4 , collectiontime/ns, edepos);
	// ofstream ("hit.dat", ios::app);
	//if (collectiontime > 0) 
	//{
		
	//	fout <<  collectiontime << "\t" << edepos  << endl;
	//}
	  }  
		//if (h_E_tmp > 140)  //*4.5e-14
analysis->FillH1(4, h_E_tmp);
	
        }
    }//fout.close();
}
  