#include "detectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* Cu = nist->FindOrBuildMaterial("G4_Cu");

	G4double worldX = 10*m;
	G4double worldY = 10*m;
	G4double worldZ = 10*m;
	G4Box* solidWorld = new G4Box("World",worldX,worldY,worldZ);

	G4LogicalVolume* logicWorld = 
		new G4LogicalVolume(solidWorld,vacuum,"World");

	G4VPhysicalVolume* physWorld = 
		new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0,true);

	//G4double thickness = 0.0025*cm;
	//G4double thickness = 0.005*cm;
	//G4double thickness = 0.0075*cm;
	//G4double thickness = 0.01*cm;
	//G4double thickness = 0.0125*cm;
	//G4double thickness = 0.015*cm;

	//G4double thickness = 1.25*cm;
	G4double thickness = 2.0*cm;
	//G4double thickness = 2.5*cm;
	//G4double thickness = 3.0*cm;
	//G4double thickness = 4.0*cm;
	//G4double thickness = 5.0*cm;
	//G4double thickness = 6.0*cm;
	//G4double thickness = 8.0*cm;
	//G4double thickness = 10.0*cm;
	//G4double thickness = 12.0*cm;
	//G4double thickness = 14.0*cm;
	//G4double thickness = 16.0*cm;
	//G4double thickness = 18.0*cm;
	//G4double thickness = 20.0*cm;

	G4double boxX = thickness/2.0;
	G4double boxY = 10.0*m;
	G4double boxZ = 10.0*m;
	G4Box* solidBox = new G4Box("Box",boxX,boxY,boxZ);

	G4LogicalVolume* logicBox = 
		new G4LogicalVolume(solidBox,Cu,"Box");

	G4VPhysicalVolume* physBox = 
		new G4PVPlacement(0,G4ThreeVector(),logicBox,"Box",logicWorld,false,0,true);

	return physWorld;
}














	
