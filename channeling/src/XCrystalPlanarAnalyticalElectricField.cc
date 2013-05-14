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

#include "XCrystalPlanarAnalyticalElectricField.hh"

XCrystalPlanarAnalyticalElectricField::XCrystalPlanarAnalyticalElectricField(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XCrystalPlanarAnalyticalElectricField::~XCrystalPlanarAnalyticalElectricField(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalPlanarAnalyticalElectricField::ComputeValueForSinglePlane(G4double vXposition,G4VPhysicalVolume* vVolume){
    
    G4double vValueForSinglePlane = GetScreeningFunction()->ComputeScreeningFunction(vXposition,GetUnitCell(vVolume)->GetBase(0)->GetElement());

    vValueForSinglePlane *= 2. * M_PI * GetUnitCell(vVolume)->ComputeDirectPeriod(GetPhysicalLattice(vVolume)->GetMiller(0),GetPhysicalLattice(vVolume)->GetMiller(1),GetPhysicalLattice(vVolume)->GetMiller(2));
    
    vValueForSinglePlane *= (elm_coupling);
    
    vValueForSinglePlane *= (GetUnitCell(vVolume)->ComputeAtomVolumeDensity());
    
    G4int vSign = -1;
    if(vXposition < 0.) vSign = +1;

    vValueForSinglePlane *= vSign;
    
    return vValueForSinglePlane;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
