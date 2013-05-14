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

#include "XLatticeManager3.hh"

#include "XLogicalAtomicLattice.hh"
#include "XLogicalAtomicLatticeDiamond.hh"
#include "XLogicalBase.hh"
#include "XUnitCell.hh"

#include "XAtomicScreeningFunctionMoliere.hh"
#include "XCrystalPlanarAnalyticalPotential.hh"
#include "XCrystalPlanarAnalyticalElectricField.hh"
#include "XCrystalPlanarAnalyticalNucleiDensity.hh"
#include "XThomasFermiScreeningRadius.hh"
#include "XCrystalPlanarAnalyticalElectronDensity.hh"

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
 
    G4NistManager* NISTman = G4NistManager::Instance();

    G4Material* Si = NISTman->FindOrBuildMaterial("G4_Si");
    
    G4Material* Vacuum =
    new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                   kStateGas, 2.73*kelvin, 3.e-18*pascal);
    
    G4double worldSize = 40*cm;
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
    
    G4double targetSizeX = 1.*cm;
    G4double targetSizeYZ = 1.*cm;
    G4Box* SolidTarget;
    G4LogicalVolume* LogicalTarget;
    G4VPhysicalVolume* PhysicalTarget;
    
    SolidTarget = new G4Box("Target", targetSizeX/2,targetSizeYZ/2,targetSizeYZ/2);
    LogicalTarget = new G4LogicalVolume(SolidTarget,          //shape
                                        Si,                    //material
                                        "Target");              //name
    
    PhysicalTarget = new G4PVPlacement(0,
                                       G4ThreeVector(0.*cm,0.*cm,0),   //no rotation
                                       LogicalTarget,           //shape and material
                                       "Target",                //name
                                       LogicalWorld,           //pointer to mother volume
                                       false,                  //no boolean operation
                                       0);                     //copy number

    
    G4double detectorSizeYZ = 5.*cm;
    G4double detectorSizeX = 50.E-3*mm;
    G4double detectorDistanceX = 10.*cm + detectorSizeX/2. + targetSizeX/2.;
    G4Box* SolidDetector;
    G4LogicalVolume* LogicalDetector;
    G4VPhysicalVolume* PhysicalDetector;
    
    SolidDetector = new G4Box("Detector", detectorSizeX/2,detectorSizeYZ/2,detectorSizeYZ/2);
    LogicalDetector = new G4LogicalVolume(SolidDetector,          //shape
                                        Si,                    //material
                                        "Detector");              //name
    
    PhysicalDetector = new G4PVPlacement(0,
                                       G4ThreeVector(detectorDistanceX,0.*cm,0.*cm),   //no rotation
                                       LogicalDetector,           //shape and material
                                       "Detector",                //name
                                       LogicalWorld,           //pointer to mother volume
                                       false,                  //no boolean operation
                                       0);                     //copy number

    //----------------------------------------
    // Si detector construction
    //----------------------------------------
    ExN04TrackerSD* myTracker = new ExN04TrackerSD("myTracker");
    G4SDManager::GetSDMpointer()->AddNewDetector(myTracker);
    //logicLayer->SetSensitiveDetector(myTracker);

    
    
    //----------------------------------------
    // Obtain pointer to lattice manager
    //----------------------------------------
    XLogicalLattice* logicalLattice = new XLogicalLattice();
    XPhysicalLattice* physicalLattice = new XPhysicalLattice(PhysicalTarget, logicalLattice);
    XLatticeManager3* myLatticeManager = XLatticeManager3::GetXLatticeManager();
    myLatticeManager->RegisterLattice(physicalLattice);
    
    logicalLattice->SetScatteringConstant(3.67e-41*s*s*s);
    physicalLattice->SetMillerOrientation(2,2,0);
    
    //----------------------------------------
    // Create XUnitCell object for Si
    //----------------------------------------
    XLogicalAtomicLatticeDiamond *diamond_lattice = new XLogicalAtomicLatticeDiamond();
    
    G4Element* element = NISTman->FindOrBuildElement(14);
    
    XLogicalBase *base = new XLogicalBase();
    base->SetElement(element);
    base->SetLattice(diamond_lattice);
    XUnitCell* myCell = new XUnitCell();
    myCell->SetSize(G4ThreeVector( 5.43 * angstrom, 5.43 * angstrom, 5.43 * angstrom));
    physicalLattice->SetUnitCell(myCell);
    myCell->AddBase(base);
    
    XThomasFermiScreeningRadius* vTF = new XThomasFermiScreeningRadius();
    XAtomicScreeningFunctionMoliere* vScreening = new XAtomicScreeningFunctionMoliere();
    vScreening->SetTFSR(vTF);
    
    XCrystalPlanarAnalyticalPotential *vPotential = new XCrystalPlanarAnalyticalPotential();
    vPotential->SetTFSR(vTF);
    vPotential->SetScreeningFunction(vScreening);
    
    XCrystalPlanarAnalyticalElectricField *vElectricField = new XCrystalPlanarAnalyticalElectricField();
    vElectricField->SetTFSR(vTF);
    vElectricField->SetScreeningFunction(vScreening);

    XCrystalPlanarAnalyticalNucleiDensity *vNucleiDensity = new XCrystalPlanarAnalyticalNucleiDensity();
    vNucleiDensity->SetTFSR(vTF);
    vNucleiDensity->SetScreeningFunction(vScreening);
    vNucleiDensity->SetThermalVibrationAmplitude(0.075*angstrom);

    XCrystalPlanarAnalyticalElectronDensity *vElectronDensity = new XCrystalPlanarAnalyticalElectronDensity();
    vElectronDensity->SetTFSR(vTF);
    vElectronDensity->SetScreeningFunction(vScreening);

    std::ofstream vFileOutPot;
    std::ofstream vFileOutEfx;
    std::ofstream vFileOutNud;
    std::ofstream vFileOutEld;

    vFileOutPot.open("pot.txt");
    vFileOutEfx.open("efx.txt");
    vFileOutNud.open("nud.txt");
    vFileOutEld.open("eld.txt");

    G4int imax = 8192;
    G4double vXposition = 0.;
    for(G4int i = -imax;i<imax;i++){
        vXposition = double(i)/double(imax)*8.*myCell->ComputeDirectPeriod(physicalLattice->GetMiller(0),physicalLattice->GetMiller(1),physicalLattice->GetMiller(2));
        //vFileOutPot << vXposition / angstrom << " " << (vPotential->ComputeValue(G4ThreeVector(vXposition,0.,0.),PhysicalTarget)).x() / eV << std::endl;
        vFileOutPot << vXposition / angstrom << " " << (vPotential->ComputeValueForSinglePlane(vXposition,PhysicalTarget)) / eV << std::endl;
        //vFileOutEfx << vXposition / angstrom << " " << (vElectricField->ComputeValue(G4ThreeVector(vXposition,0.,0.),PhysicalTarget)).x() / eV * angstrom << std::endl;
        vFileOutEfx << vXposition / angstrom << " " << (vElectricField->ComputeValueForSinglePlane(vXposition,PhysicalTarget)) / eV * angstrom << std::endl;
        vFileOutNud << vXposition / angstrom << " " << (vNucleiDensity->ComputeValueForSinglePlane(vXposition,PhysicalTarget)) << std::endl;
        vFileOutEld << vXposition / angstrom << " " << (vElectronDensity->ComputeValueForSinglePlane(vXposition,PhysicalTarget)) << std::endl;
    }
    vFileOutPot.close();
    vFileOutEfx.close();
    vFileOutNud.close();
    vFileOutEld.close();

    
    
    return PhysicalWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
