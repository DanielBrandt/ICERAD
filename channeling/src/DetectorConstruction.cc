//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::~DetectorConstruction()
{

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  int z;      //atomic number
  G4double a; //atomic weight
  G4double density;

  G4Material* Pb = 
    new G4Material("Lead"     , z=82, a = 207.19*g/mole, density= 11.35*g/cm3);

  G4Material* Vacuum =
    new G4Material("Galactic", z=1, a=1.01*g/mole,density= universe_mean_density,
		   kStateGas, 2.73*kelvin, 3.e-18*pascal);

  G4double worldSize = 0.5*m;
  G4Box* SolidWorld;
  G4LogicalVolume* LogicalWorld;
  G4VPhysicalVolume* PhysicalWorld;

  SolidWorld = new G4Box("World", worldSize/2,worldSize/2,worldSize/2);
  LogicalWorld = new G4LogicalVolume(SolidWorld,            //shape
				     Vacuum,                //material
				     "World");              //name

  PhysicalWorld = new G4PVPlacement(0,
				    G4ThreeVector(0,0,0),   //no rotation
				    LogicalWorld,           //shape and material
				    "World",                //name
				    0,                      //pointer to mother volume
				    false,                  //no boolean operation
				    0);                     //copy number

  G4double targetSize = 15.*cm;
  G4Box* SolidTarget;
  G4LogicalVolume* LogicalTarget;
  G4VPhysicalVolume* PhysicalTarget;

  SolidTarget = new G4Box("Target", targetSize/2,targetSize/2,targetSize/2);
  LogicalTarget = new G4LogicalVolume(SolidTarget,          //shape
				     Pb,                    //material
				     "Target");              //name

  PhysicalTarget = new G4PVPlacement(0,
				    G4ThreeVector(0.*cm,+5.*cm,0),   //no rotation
				    LogicalTarget,           //shape and material
				    "Target",                //name
				    LogicalWorld,           //pointer to mother volume
				    false,                  //no boolean operation
				    0);                     //copy number

  return PhysicalWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
