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

#include "XCrystalPlanarMoliereTempPotential.hh"

XCrystalPlanarMoliereTempPotential::XCrystalPlanarMoliereTempPotential(){
    fAlfa[0] = 0.1;
    fAlfa[1] = 0.55;
    fAlfa[2] = 0.35;
    
    fBeta[0] = 6.0;
    fBeta[1] = 1.2;
    fBeta[2] = 0.3;
    
    for(unsigned int i=0;i<3;i++) {
        fGamma[i] = fAlfa[i]/fBeta[i];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XCrystalPlanarMoliereTempPotential::~XCrystalPlanarMoliereTempPotential(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalPlanarMoliereTempPotential::ComputeValueForSinglePlane(G4double vX,XPhysicalLattice* vLattice){
    
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();

    G4double aTF = ComputeTFScreeningRadius(vLattice);
    G4double vTVA = GetThermalVibrationAmplitude();
    
    G4double vTau[3];
    for(unsigned int i=0;i<3;i++) vTau[i] = (pow( vTVA / aTF * fBeta[i] , 2. ) / 2.0);

    
    G4double vValueForSinglePlane = 0.;
    
    for(unsigned int i=0;i<3;i++){
        G4double vTemp = 0.;
        vTemp += ( exp(-vX/ aTF * fBeta[i] ) * erfc((vTVA / aTF * fBeta[i] - vX/ vTVA) / pow(2.,0.5)) );
        vTemp += ( exp( vX/ aTF * fBeta[i] ) * erfc((vTVA / aTF * fBeta[i] + vX/ vTVA) / pow(2.,0.5)) );
        vValueForSinglePlane += ( vTemp * fGamma[i] * exp( vTau[i] ) /2.0);
    }
    
    vValueForSinglePlane *= 2. * M_PI * GetXUnitCell(vVolume)->ComputeDirectPeriod(GetXPhysicalLattice(vVolume)->GetMiller(0),GetXPhysicalLattice(vVolume)->GetMiller(1),GetXPhysicalLattice(vVolume)->GetMiller(2));
    
    vValueForSinglePlane *= aTF;

    vValueForSinglePlane *= (elm_coupling);

    vValueForSinglePlane *= (GetXUnitCell(vVolume)->ComputeAtomVolumeDensity());

    return vValueForSinglePlane;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XCrystalPlanarMoliereTempPotential::GetMaximum(XPhysicalLattice* vLattice){
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();

    G4double vMaximum = ComputeValue(G4ThreeVector(0.,0.,0.),vLattice).x();
    
    return G4ThreeVector(vMaximum,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XCrystalPlanarMoliereTempPotential::GetMinimum(XPhysicalLattice* vLattice){
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    G4double vInterplanarDistance = GetXUnitCell(vVolume)->ComputeDirectPeriod(GetXPhysicalLattice(vVolume)->GetMiller(0),GetXPhysicalLattice(vVolume)->GetMiller(1),GetXPhysicalLattice(vVolume)->GetMiller(2));
    
    G4double vMinimum = ComputeValue(G4ThreeVector(0.,vInterplanarDistance/2.,0.),vLattice).y();
    
    return G4ThreeVector(vMinimum,0.,0.);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
