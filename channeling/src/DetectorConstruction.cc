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

DetectorConstruction::DetectorConstruction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::~DetectorConstruction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct(){
    AddWorld();
    AddCrystalTarget();
    AddSiliconStripDetector();
    return fWorldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::AddWorld(){
    G4Material* Vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
    
    fWorldSizeX = 1.4 * m;
    fWorldSizeYZ = 10 * cm;
    
    fWorldSolid = new G4Box("World", fWorldSizeX/2.,fWorldSizeYZ/2.,fWorldSizeYZ/2.);
    fWorldLogic = new G4LogicalVolume(fWorldSolid,Vacuum,"World");
    fWorldPhysical = new G4PVPlacement(0,G4ThreeVector(0,0,0),fWorldLogic,"World",0,false,0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::AddSiliconStripDetector(){
    G4Material* Si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
    
    fSSDSizeYZ = 1.92 * cm;
    fSSDSizeX = 0.6 * mm;
    
    fSSDSolid = new G4Box("SiSD", fSSDSizeX/2.,fSSDSizeYZ/2.,fSSDSizeYZ/2.);
    fSSDLogic = new G4LogicalVolume(fSSDSolid,Si,"SiSD");
    
    for(int j1=0;j1<3;j1++)
    {
        G4double vDetDistX = double(j1 - 1) * 50. * cm + fSSDSizeX/2. - 2. * fXtalSizeX/2.;;
        fSSDPhysical = new G4PVPlacement(0,G4ThreeVector(vDetDistX,0.,0.),fSSDLogic,"SiSD",fWorldLogic,false,j1);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::AddCrystalTarget(){
    G4Material* Si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");

    fXtalSizeX = 2. * mm;
    fXtalSizeYZ = 6. * cm;
    
    fXtalSolid = new G4Box("Target", fXtalSizeX/2.,fXtalSizeYZ/2.,fXtalSizeYZ/2.);
    fXtalLogic = new G4LogicalVolume(fXtalSolid, Si,"Target");
    fXtalPhysical = new G4PVPlacement(0,G4ThreeVector(),fXtalLogic,"Target",fWorldLogic,false,0);
    
    //----------------------------------------
    // Create XLogicalLattice
    //----------------------------------------
    XLogicalLattice* logicalLattice = new XLogicalLattice();
    logicalLattice->SetScatteringConstant(3.67e-41*s*s*s);
    
    //----------------------------------------
    // Create XLogicalBase
    //----------------------------------------
    XLogicalAtomicLatticeDiamond *diamond_lattice = new XLogicalAtomicLatticeDiamond();
    G4Element* element = G4NistManager::Instance()->FindOrBuildElement(14);
    XLogicalBase *base = new XLogicalBase(element,diamond_lattice);

    //----------------------------------------
    // Create XUnitCell
    //----------------------------------------
    XUnitCell* myCell = new XUnitCell();
    myCell->SetSize(G4ThreeVector(5.431 * angstrom, 5.431 * angstrom, 5.431 * angstrom));
    myCell->AddBase(base);
    
    //----------------------------------------
    // Create XPhysicalLattice
    //----------------------------------------
    XPhysicalLattice* physicalLattice = new XPhysicalLattice(fXtalPhysical, logicalLattice);
    physicalLattice->SetUnitCell(myCell);
    physicalLattice->SetMillerOrientation(2,2,0);
    physicalLattice->SetLatticeOrientation(0.,0.);

    //----------------------------------------
    // Register XPhysicalLattice
    //----------------------------------------
    XLatticeManager3::GetXLatticeManager()->RegisterLattice(physicalLattice);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ComputeCrystalCharacteristicForChanneling(){
    
    XPhysicalLattice* vXtalPhysLattice = XLatticeManager3::GetXLatticeManager()->GetXPhysicalLattice(fXtalPhysical);
    
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
    G4double vXpositionConstant = 2. * vXtalPhysLattice->GetXUnitCell()->ComputeDirectPeriod(vXtalPhysLattice->GetMiller(0),vXtalPhysLattice->GetMiller(1),vXtalPhysLattice->GetMiller(2));
    
    for(G4int i = -imax;i<imax;i++){
        vXposition = double(i) / double(imax) * vXpositionConstant;
        //vFileOutPot << vXposition / angstrom << " " << (vPotential->ComputeValue(G4ThreeVector(vXposition,0.,0.),fXtalPhysical)).x() / eV << std::endl;
        vFileOutPot << vXposition / angstrom << " " << (vPotential->ComputeValueForSinglePlane(vXposition,fXtalPhysical)) / eV << std::endl;
        //vFileOutEfx << vXposition / angstrom << " " << (vElectricField->ComputeValue(G4ThreeVector(vXposition,0.,0.),fXtalPhysical)).x() / eV * angstrom << std::endl;
        vFileOutEfx << vXposition / angstrom << " " << (vElectricField->ComputeValueForSinglePlane(vXposition,fXtalPhysical)) / eV * angstrom << std::endl;
        vFileOutNud << vXposition / angstrom << " " << (vNucleiDensity->ComputeValueForSinglePlane(vXposition,fXtalPhysical)) << std::endl;
        vFileOutEld << vXposition / angstrom << " " << (vElectronDensity->ComputeValueForSinglePlane(vXposition,fXtalPhysical)) << std::endl;
    }
    vFileOutPot.close();
    vFileOutEfx.close();
    vFileOutNud.close();
    vFileOutEld.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
