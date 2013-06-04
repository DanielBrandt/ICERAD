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
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XVCrystalPlanarAnalytical::~XVCrystalPlanarAnalytical(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalPlanarAnalytical::SetNumberOfPlanes(G4int vNumberOfPlanes){
    fNumberOfPlanes = vNumberOfPlanes;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4int XVCrystalPlanarAnalytical::GetNumberOfPlanes(){
    return fNumberOfPlanes;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XVCrystalPlanarAnalytical::ComputeValue(G4ThreeVector vPositionVector,XPhysicalLattice* vLattice){
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    
    G4double vInterplanarDistance = GetXPhysicalLattice(vVolume)->ComputeInterplanarPeriod();
    
    G4double vPosition = ComputePositionInUnitCell(vPositionVector,vLattice).x();
    
    G4double vValue = 0.;
    for(int i=-int(GetNumberOfPlanes()/2);i<=+int(GetNumberOfPlanes()/2);i++){
        vValue += ComputeValueForSinglePlane( ( vPosition + G4double(i) ) * vInterplanarDistance , vLattice );
    }
    
    return G4ThreeVector(vValue,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XVCrystalPlanarAnalytical::ComputePositionInUnitCell(G4ThreeVector vPositionVector, XPhysicalLattice* vLattice){
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    
    G4double vInterplanarDistance = GetXPhysicalLattice(vVolume)->ComputeInterplanarPeriod();
    
    G4double vPosition = vPositionVector.x();
    
    if (vPosition < 0.0) {
        vPosition += (fabs(int( vPosition / vInterplanarDistance ) ) + 1.0 ) * vInterplanarDistance;
    }
    else if ( vPosition > vInterplanarDistance ){
        vPosition -= fabs( int( vPosition / vInterplanarDistance ) * vInterplanarDistance );
    }
    return G4ThreeVector(vPosition/vInterplanarDistance,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XVCrystalPlanarAnalytical::GetMaximum(XPhysicalLattice* vLattice){
    unsigned int vPrecision = 1024;
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    G4double vStep = GetXPhysicalLattice(vVolume)->ComputeInterplanarPeriod() / vPrecision;
    
    G4double vMaximum = -DBL_MAX;
    G4double vValue;
    
    for(unsigned int i=0;i<vPrecision;i++){
        if( (vValue = ComputeValue(G4ThreeVector(vStep * i,0.,0.),vLattice).x() )>vMaximum) vMaximum = vValue;
    }
    return G4ThreeVector(vMaximum,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XVCrystalPlanarAnalytical::GetMinimum(XPhysicalLattice* vLattice){
    unsigned int vPrecision = 1024;
    G4VPhysicalVolume* vVolume = vLattice->GetVolume();
    G4double vStep = GetXPhysicalLattice(vVolume)->ComputeInterplanarPeriod() / vPrecision;
    
    G4double vMinimum = +DBL_MAX;
    G4double vValue;
    
    for(unsigned int i=0;i<vPrecision;i++){
        if( (vValue = ComputeValue(G4ThreeVector(vStep * i,0.,0.),vLattice).x() )<vMinimum) vMinimum = vValue;
    }
    return G4ThreeVector(vMinimum,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
