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

#include "XCrystalPlanarMolierePotential.hh"

XCrystalPlanarMolierePotential::XCrystalPlanarMolierePotential(){
    fAlfa[0] = 0.1;
    fAlfa[1] = 0.55;
    fAlfa[2] = 0.35;
    
    fBeta[0] = 6.0;
    fBeta[1] = 1.2;
    fBeta[2] = 0.3;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XCrystalPlanarMolierePotential::~XCrystalPlanarMolierePotential(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalPlanarMolierePotential::ComputeValueForSinglePlane(G4double vXposition,XPhysicalLattice* vLattice){
    
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    G4Element* vElement = GetXUnitCell(vVolume)->GetBase(0)->GetElement();
    G4double aTF = ComputeTFScreeningRadius(vLattice);

    G4double vValueForSinglePlane = 0.;
    
    for(unsigned int i=0;i<3;i++){
        vValueForSinglePlane += ( fAlfa[i]/fBeta[i] * exp( - fabs(vXposition) * fBeta[i] / aTF ) );
    }
    
    vValueForSinglePlane *= 2. * M_PI * GetXUnitCell(vVolume)->ComputeDirectPeriod(GetXPhysicalLattice(vVolume)->GetMiller(0),GetXPhysicalLattice(vVolume)->GetMiller(1),GetXPhysicalLattice(vVolume)->GetMiller(2));
    
    vValueForSinglePlane *= aTF;

    vValueForSinglePlane *= (elm_coupling);

    vValueForSinglePlane *= (GetXUnitCell(vVolume)->ComputeAtomVolumeDensity());

    return vValueForSinglePlane;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalPlanarMolierePotential::GetMaximum(XPhysicalLattice* vLattice){
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    G4double vInterplanarDistance = GetXUnitCell(vVolume)->ComputeDirectPeriod(GetXPhysicalLattice(vVolume)->GetMiller(0),GetXPhysicalLattice(vVolume)->GetMiller(1),GetXPhysicalLattice(vVolume)->GetMiller(2));

    G4double vMaximum = ComputeValue(G4ThreeVector(0.,0.,0.),vLattice).y();
    
    return vMaximum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalPlanarMolierePotential::GetMinimum(XPhysicalLattice* vLattice){
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    G4double vInterplanarDistance = GetXUnitCell(vVolume)->ComputeDirectPeriod(GetXPhysicalLattice(vVolume)->GetMiller(0),GetXPhysicalLattice(vVolume)->GetMiller(1),GetXPhysicalLattice(vVolume)->GetMiller(2));
    
    G4double vMinimum = ComputeValue(G4ThreeVector(0.,vInterplanarDistance/2.,0.),vLattice).y();
    
    return vMinimum;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
