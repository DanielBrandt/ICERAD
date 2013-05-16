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

#include "XVCrystalPlanarAnalytical.hh"

XVCrystalPlanarAnalytical::XVCrystalPlanarAnalytical(){
    fNumberOfPlanes = 4;
    fThermalVibrationAmplitude = 1. * angstrom;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XVCrystalPlanarAnalytical::~XVCrystalPlanarAnalytical(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalPlanarAnalytical::SetNumberOfPlanes(G4int vNumberOfPlanes){
    fNumberOfPlanes = vNumberOfPlanes;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalPlanarAnalytical::SetTFSR(XThomasFermiScreeningRadius *vThomasFermiScreeningRadius){
    fThomasFermiScreeningRadius = vThomasFermiScreeningRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalPlanarAnalytical::SetThermalVibrationAmplitude(G4double vThermalVibrationAmplitude){
    fThermalVibrationAmplitude = vThermalVibrationAmplitude;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4int XVCrystalPlanarAnalytical::GetNumberOfPlanes(){
    return fNumberOfPlanes;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XThomasFermiScreeningRadius* XVCrystalPlanarAnalytical::GetTFSR(){
    return fThomasFermiScreeningRadius;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalPlanarAnalytical::GetThermalVibrationAmplitude(){
    return fThermalVibrationAmplitude;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XVCrystalPlanarAnalytical::ComputeValue(G4ThreeVector vPositionVector,const G4Track& aTrack){
    G4VPhysicalVolume* vVolume = aTrack.GetVolume();
    
    G4double vInterplanarDistance = GetXUnitCell(vVolume)->ComputeDirectPeriod(GetXPhysicalLattice(vVolume)->GetMiller(0),GetXPhysicalLattice(vVolume)->GetMiller(1),GetXPhysicalLattice(vVolume)->GetMiller(2));
    
    G4double vX = ComputePositionInPeriodicUnit(vPositionVector.y(),vInterplanarDistance);
    
    G4double vValue = 0.;
    for(G4int i=-int(GetNumberOfPlanes()/2);i<=+int(GetNumberOfPlanes()/2);i++){
        vValue += ComputeValueForSinglePlane(vX + vInterplanarDistance * i,aTrack);
    }
    
    return G4ThreeVector(0.,vValue,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
