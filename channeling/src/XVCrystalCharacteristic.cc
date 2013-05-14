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

#include "XVCrystalCharacteristic.hh"

XVCrystalCharacteristic::XVCrystalCharacteristic(){
    fLatticeManager = XLatticeManager3::GetXLatticeManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XVCrystalCharacteristic::~XVCrystalCharacteristic(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XPhysicalLattice* XVCrystalCharacteristic::GetPhysicalLattice(G4VPhysicalVolume* vVolume)
{
    return fLatticeManager->GetXPhysicalLattice(vVolume);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XUnitCell* XVCrystalCharacteristic::GetUnitCell(G4VPhysicalVolume* vVolume)
{
    return GetPhysicalLattice(vVolume)->GetUnitCell();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XLogicalLattice* XVCrystalCharacteristic::GetLogicalLattice(G4VPhysicalVolume* vVolume)
{
    return GetPhysicalLattice(vVolume)->GetLogicalLattice();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalCharacteristic::ComputePositionInPeriodicUnit(G4double vX, G4double &vPeriod){
    if (vX < 0.0) vX += (fabs(int( vX / vPeriod ) ) + 1.0 ) * vPeriod;
    else if ( vX > vPeriod ) vX -= fabs( int( vX / vPeriod ) * vPeriod );
    return vX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
