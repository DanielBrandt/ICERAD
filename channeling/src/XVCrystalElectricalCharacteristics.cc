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

#include "XVCrystalElectricalCharacteristics.hh"

XVCrystalElectricalCharacteristics::XVCrystalElectricalCharacteristics(){
    InitializeXVCrystalElectricalCharacteristics();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XVCrystalElectricalCharacteristics::~XVCrystalElectricalCharacteristics(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalElectricalCharacteristics::InitializeXVCrystalElectricalCharacteristics(){
    G4NistManager* fNistManager = G4NistManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalElectricalCharacteristics::EvaluateInverseThomasFermiRadius(G4Element *vElement) // see G4IonCoulombCrossSection::SetScreenRSquare(G4int)
{
    G4double inverse_a_TF = electron_mass_c2 / 0.88534 * fNistManager->GetZ13(vElement->GetZ());
    //for proton Thomas-Fermi screening length
    return inverse_a_TF;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XPhysicalLattice* XVCrystalElectricalCharacteristics::GetPhysicalLattice()
{
    return fLatticeManager->GetXPhysicalLattice(fVolume);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XUnitCell* XVCrystalElectricalCharacteristics::GetUnitCell()
{
    return GetPhysicalLattice()->GetUnitCell();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XLogicalLattice* XVCrystalElectricalCharacteristics::GetLogicalLattice()
{
    return GetPhysicalLattice()->GetLogicalLattice();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* XVCrystalElectricalCharacteristics::GetPhysicalVolume()
{
    return GetPhysicalLattice()->GetVolume();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalElectricalCharacteristics::SetVolume(G4VPhysicalVolume* vVolume)
{
    fVolume = vVolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
