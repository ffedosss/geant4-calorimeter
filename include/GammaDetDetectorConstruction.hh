
#ifndef GammaDetDetectorConstruction_h
#define GammaDetDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4LogicalVolume;
class GammaDetDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    GammaDetDetectorConstruction();
    virtual ~GammaDetDetectorConstruction();
	G4LogicalVolume* sipm_log;
	G4LogicalVolume* GetSipm() { return sipm_log; };
  public:
    virtual G4VPhysicalVolume* Construct();
	void ConstructSDandField() override;

  private:
    G4double fExpHall_x;
    G4double fExpHall_y;
    G4double fExpHall_z;

    G4double fPlate_x;
    G4double fPlate_y;
    G4double fPlate_z;

	G4double fvacuum_x;
	G4double fvacuum_y;
	G4double fvacuum_z;

	G4double fPlateA_x;
	G4double fPlateA_z;
	G4double fPlateA_y;
    
	G4double fPlateB_x;
	G4double fPlateB_z;
	G4double fPlateB_y;

	G4double fCryst_x;
	G4double fCryst_z;
	G4double fCryst_y;
	G4double fCutCryst_x;
	G4double fcovera_x;
	G4double fcovera_y;
	G4double fcovera_z;
	G4double fcoverb_x;
	G4double fcoverb_y;
	G4double fcoverb_z;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*GammaDetDetectorConstruction_h*/
