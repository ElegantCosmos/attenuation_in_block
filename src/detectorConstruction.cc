#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"

#include "statisticsLogger.hh"
#include "detectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4String name; // name of material
  G4double density; // density of material
  G4int nComponents, nAtoms; // number of composing atom types, number of atoms composing molecule of material

  G4NistManager* nist = G4NistManager::Instance();

  G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Cu = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* Pb = nist->FindOrBuildMaterial("G4_Pb");
  G4Element* Te = nist->FindOrBuildElement("Te");
  G4Element* O = nist->FindOrBuildElement("O");

  // TeO2
  G4Material* TeO2 = new G4Material(name = "TeO2", density = 6.0*g/cm3, nComponents = 2);
  TeO2->AddElement(Te, nAtoms = 1);
  TeO2->AddElement(O, nAtoms = 2);

  G4double worldX = 10*m;
  G4double worldY = 10*m;
  G4double worldZ = 10*m;
  G4Box* solidWorld = new G4Box("World",worldX,worldY,worldZ);

  G4LogicalVolume* logicWorld = 
    new G4LogicalVolume(solidWorld,vacuum,"World");

  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0,true);

  //const G4double thickness = 0.0025*cm;
  //const G4double thickness = 0.005*cm;
  //const G4double thickness = 0.0075*cm;
  //const G4double thickness = 0.01*cm;
  //const G4double thickness = 0.0125*cm;
  //const G4double thickness = 0.015*cm;

  //const G4double thickness = 1.0*cm;
  //const G4double thickness = 2.0*cm;
  //const G4double thickness = 4.0*cm;
  //const G4double thickness = 6.0*cm;
  //const G4double thickness = 8.0*cm;
  //const G4double thickness = 10.0*cm;
  //const G4double thickness = 12.0*cm;
  //const G4double thickness = 14.0*cm;
  //const G4double thickness = 16.0*cm;
  //const G4double thickness = 18.0*cm;
  const G4double thickness = 20.0*cm;

  StatisticsLogger* logger = StatisticsLogger::GetInstance();
  logger->SetAttenuatorThickness(thickness/cm);

  G4double boxX = 0.5*thickness;
  G4double boxY = 10.0*m;
  G4double boxZ = 10.0*m;
  G4Box* solidBox = new G4Box("Box",boxX,boxY,boxZ);

  //G4LogicalVolume* logicBox_Cu = 
  //	new G4LogicalVolume(solidBox,Cu,"Box");

  //G4LogicalVolume* logicBox_Pb = 
  //	new G4LogicalVolume(solidBox,Pb,"Box");

  G4LogicalVolume* logicBox_TeO2 = 
    new G4LogicalVolume(solidBox,TeO2,"Box");

  G4VPhysicalVolume* physBox = 
    new G4PVPlacement(0,G4ThreeVector(),logicBox_TeO2,"Box",logicWorld,false,0,true);

  return physWorld;
}
