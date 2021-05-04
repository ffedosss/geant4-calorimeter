
#include "GammaDetDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"

#include "G4Box.hh"
#include "G4Trap.hh"
#include "G4Tubs.hh"
#include "G4GenericTrap.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4UserLimits.hh"

#include <G4SDManager.hh>
#include <G4PSEnergyDeposit.hh>
#include "EnergyTimeSD.hh"
#include <G4GlobalMagFieldMessenger.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetDetectorConstruction::GammaDetDetectorConstruction()
 : G4VUserDetectorConstruction()
{
  fExpHall_x = 100.0*mm;
  fExpHall_y = 100.0*mm;
  fExpHall_z = 100.0*mm;

  fvacuum_x  = 2.5 * cm;
  fvacuum_z  = 22*mm;
  fvacuum_y  = 16*mm;

  fPlate_x   = 3*mm;
  fPlate_z   = 22*mm; 
  fPlate_y   = 16*mm;
  
  fPlateA_x   = 0.5*cm;
  fPlateA_z   = 11.25*cm; 
  fPlateA_y   = 7.5*cm;
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaDetDetectorConstruction::~GammaDetDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GammaDetDetectorConstruction::Construct()
{
	G4NistManager* nist = G4NistManager::Instance();
	// ------------- Materials -------------
	
	G4double a, z, density, temperature, pressure;
	G4int nelements;

	G4Element* N = new G4Element("Nitrogen", "N", z = 7, a = 14.01*g/mole);
	G4Element* O = new G4Element("Oxygen", "O", z = 8, a = 16.00*g / mole);
	G4Element* Si = new G4Element("Silicon", "Si" , z= 14., a= 28.09*g/mole);
	G4Element* H = new G4Element("Hydrogen", "H", z = 1, a = 1.01*g/mole);
	G4Element* Na = new G4Element( "Na", "Na" , z = 11,  a = 23.0*g/mole);
	G4Element* Ba = new G4Element("Barium","Ba",z=56, a= 137.327*g/mole);
	G4Element* K = new G4Element("Potassium","K",z=19, a=39.098*g/mole);
	G4Element* B = new G4Element("Boron", "B",z=5, a=10.81*g/mole);
	G4Element* As = new G4Element("Arsen",  "As", z=33, a= 74.92160*g/mole);
	G4Element* C = new G4Element("Carbon", "C", z = 6, a = 12.0116 *g/mole);
	G4Element* Pb = new G4Element("Lead", "Pb", z = 82, a = 207.19*g / mole);
	G4Element* F = new G4Element("Fluorine", "F", z = 9, a = 19.00*g / mole);
	G4Element* Li = new G4Element( "Lithium"   , "Li" ,  z = 3,  a =  7.0 *g/mole );
	// Air
	//
	
	G4Material* air = new G4Material("Air", density = 1.29*mg / cm3, nelements = 2);
	air->AddElement(N, 70.*perCent);
	air->AddElement(O, 30.*perCent);
	

	G4Material* Sil = new G4Material("Sil", density = 2.3290*g/cm3, nelements = 1);
	Sil->AddElement(Si, 100.*perCent);
	

	// Aluminium
	//  
	G4Material* Al = new G4Material("Aluminum", z = 13., a = 26.98*g / mole, density = 2.7*g / cm3);
	
	//
	// vacuum
	G4Material*Galactic = new G4Material("Galactic", z = 1., a = 1.01*g / mole, density = 1.e-25*g / cm3, kStateGas,
		temperature = 0.1*kelvin, pressure = 1.e-19*pascal);

	//Template for Si + Li mixture

	G4Material* SiO2 = new G4Material("SiO2", density = 2.196 *g / cm3, nelements = 2);
	SiO2->AddElement(Si, 1);
	SiO2->AddElement(O, 2);



	//Positions
	G4double vacuumX = -fvacuum_x/2;
	G4double plateX = vacuumX + fPlate_x/2 + fvacuum_x/2;


	// ------------- Volumes --------------

					// The experimental Hall
	//
	G4Box* expHall_box = new G4Box("World", fExpHall_x/2, fExpHall_y/2, fExpHall_z/2);

	G4LogicalVolume* expHall_log
		= new G4LogicalVolume(expHall_box, air, "World", 0, 0, 0);

	G4VPhysicalVolume* expHall_phys
		= new G4PVPlacement(0, G4ThreeVector(), expHall_log, "World", 0, false, 0);

	// invisible world
	//expHall_log->SetVisAttributes(G4VisAttributes::Invisible);

		
						// The Vacuum

  G4Box* vacuum_box = new G4Box("vacuum",fvacuum_x/2,fvacuum_y/2,fvacuum_z/2);

  G4LogicalVolume* vacuum_log
    = new G4LogicalVolume(vacuum_box, Galactic,"vacuum",0,0,0);

G4VPhysicalVolume* vacuum_phys =
     new G4PVPlacement(0,G4ThreeVector(vacuumX,0,0),vacuum_log,"vacuum",

                       expHall_log,false,0);





						// The Si Plate
	//
	G4Box* Plate_box = new G4Box("Plate", fPlate_x/2, fPlate_y/2, fPlate_z/2);

	G4LogicalVolume* Plate_log
		= new G4LogicalVolume(Plate_box, Sil, "Plate", 0, 0, 0);

	G4VPhysicalVolume* Plate_phys
		= new G4PVPlacement(0, G4ThreeVector(plateX, 0, 0), Plate_log, "Plate",
			expHall_log, false, 0);


	G4Region* Plate = new G4Region("Plate");
  Plate->AddRootLogicalVolume(Plate_log);
			
	//color for vis
	G4Colour color1(1, 5, 1);
	G4VisAttributes* PlateVisAtt = new  G4VisAttributes(color1);
	Plate_log->SetVisAttributes(PlateVisAtt);

	/*G4UserLimits *l = new G4UserLimits();
	// Sets a max Step length in the diamond :
	G4double maxStep = 0.0000001*mm;
	l->SetMaxAllowedStep(maxStep);
	Plate_log->SetUserLimits(l);*/
	
  // Sensitive Detectors: Absorber

  /*SensitiveDetector* sd = new SensitiveDetector("AbsorberSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(sd );
  logicAbsorber->SetSensitiveDetector(sd);
  
*/
    EnergyTimeSD* absorberET = new EnergyTimeSD("absorberET");
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(absorberET);
    Plate_log->SetSensitiveDetector(absorberET);
 

	/*
								// The Si + Li Plate
	//
	G4Box* SiLiPlate_box = new G4Box("SiLiPlate", 0.001*mm, fPlateA_y, fPlateA_z);

	G4LogicalVolume* SiLiPlate_log
		= new G4LogicalVolume(SiLiPlate_box, SiLi, "SiLiPlate", 0, 0, 0);

	G4VPhysicalVolume* SiLiPlate_phys
		= new G4PVPlacement(0, G4ThreeVector(13.001*mm, 0, 0), SiLiPlate_log, "SiLiPlate",
			expHall_log, false, 0);
	// color for vis
	G4Colour blue(0, 0, 1);
	G4VisAttributes* SiLiPlateVisAtt = new  G4VisAttributes(blue);
	SiLiPlate_log->SetVisAttributes(G4VisAttributes::Invisible);*/
    //
    G4double refractiveIndex1[] =
              { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
                1.346,  1.3465, 1.347,  1.3475, 1.348,
                1.3485, 1.3492, 1.35,   1.3505, 1.351,
                1.3518, 1.3522, 1.3530, 1.3535, 1.354,
                1.3545, 1.355,  1.3555, 1.356,  1.3568,
                1.3572, 1.358,  1.3585, 1.359,  1.3595,
                1.36,   1.3608};

    assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));
    //
	
	
  return expHall_phys;
}


void GammaDetDetectorConstruction::ConstructSDandField()
{

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
