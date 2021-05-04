

// Make this appear first!
#include "G4Timer.hh"

#include "GammaDetRunAction.hh"

#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "Analysis.hh"
//#include "G4AnalysisMessenger.hh"



GammaDetRunAction::GammaDetRunAction()
 : G4UserRunAction(),
   fTimer(0)
{
  fTimer = new G4Timer;
  // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
  // Creating histograms
	analysisManager->CreateH1("h1", "Energy spectrum of secondaries (not gamma)", 3000, 0.,1.);
	analysisManager->SetH1XAxisTitle(1, "MeV");
	analysisManager->SetH1YAxisTitle(1, "Entries");
	analysisManager->CreateH1("h2", "Deposited energy of secondaries", 3000, 0.,10000.);
	analysisManager->SetH1XAxisTitle(2, "eV");
	analysisManager->SetH1YAxisTitle(2, "Entries");

	analysisManager->CreateH1("h3", "time", 10000, 0.08, 0.1);
	analysisManager->SetH1XAxisTitle(3, "ns");
	analysisManager->SetH1YAxisTitle(3, "Entries");

	analysisManager->CreateH1("h4", "Energ_depos", 1000, 0.,1000);
	analysisManager->SetH1XAxisTitle(4, "keV");
	analysisManager->SetH1YAxisTitle(4, "Entries");

	
	


	analysisManager->CreateH2("h5", "mm vs time", 900. , 0. ,3. , 900., 0.,1.);
	analysisManager->CreateH2("h6", "y vs z", 900. , -16. ,16. , 900., -22.,22.);
	analysisManager->CreateH2("h7", "y vs z", 900. , 0. ,3. , 900., -11.,11.);
	analysisManager->CreateH2("h8", "t vs en", 1000. , 0. ,20. , 1000., 0.,1000);
	
	analysisManager->CreateNtuple("1", "ETP");
	analysisManager->CreateNtupleDColumn("EnergyDeposit_eV");
	analysisManager->CreateNtupleDColumn("Time_ns");
	analysisManager->CreateNtupleDColumn("X_mm");
	analysisManager->CreateNtupleDColumn("Y_mm");
	analysisManager->CreateNtupleDColumn("Z_mm");
	analysisManager->CreateNtupleDColumn("KinE_MeV");
	analysisManager->CreateNtupleDColumn("AngDistr_rad");
	analysisManager->CreateNtupleDColumn("AngDistr1_rad");
	analysisManager->FinishNtuple();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetRunAction::~GammaDetRunAction()
{
  delete fTimer;
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void GammaDetRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file

  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaDetRunAction::EndOfRunAction(const G4Run* aRun)
{
  fTimer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent()
         << " " << *fTimer << G4endl;
  // Save histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    for (G4int ih = 1; ih<=3; ih++)
  {  
    G4int NbofEvents = aRun->GetNumberOfEvent();
	G4double binWidth = analysisManager->GetH1Width(ih);
	 G4double fac = (1./(NbofEvents));//*binWidth)
	 
	  analysisManager->ScaleH1(ih,fac);
  }



  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
