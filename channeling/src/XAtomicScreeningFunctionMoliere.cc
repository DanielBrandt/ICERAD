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

#include "XAtomicScreeningFunctionMoliere.hh"

XAtomicScreeningFunctionMoliere::XAtomicScreeningFunctionMoliere(){
    fAlfa[0] = 0.1;
    fAlfa[1] = 0.55;
    fAlfa[2] = 0.35;
    
    fBeta[0] = 6.0;
    fBeta[1] = 1.2;
    fBeta[2] = 0.3;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XAtomicScreeningFunctionMoliere::~XAtomicScreeningFunctionMoliere(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XAtomicScreeningFunctionMoliere::SetThomasFermiScreeningFunction(XThomasFermiScreeningRadius *vThomasFermiScreeningRadius){
    fThomasFermiScreeningRadius = vThomasFermiScreeningRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XThomasFermiScreeningRadius* XAtomicScreeningFunctionMoliere::GetThomasFermiScreeningFunction(){
    return fThomasFermiScreeningRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunctionMoliere::ComputeScreeningFunction(G4double& vXdistance, G4Element *vElement, G4ParticleDefinition *vParticle){
    G4double vScreeningValue = 0.;
    G4double aTF = fThomasFermiScreeningRadius->ComputeScreeningRadius(vElement);
    for(G4int i=0;i<3;i++){
        vScreeningValue += ( fAlfa[i]/fBeta[i] * exp( - fabs(vXdistance) * fBeta[i] / aTF ) );
    }
    return vScreeningValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunctionMoliere::ComputeScreeningFunction(G4double& vXdistance, G4Element *vElement){
    G4double vScreeningValue = 0.;
    G4double aTF = fThomasFermiScreeningRadius->ComputeScreeningRadius(vElement);
    for(G4int i=0;i<3;i++){
        vScreeningValue += ( fAlfa[i]/fBeta[i] * exp( - (fabs(vXdistance) * fBeta[i] / aTF) ) );
    }
    return vScreeningValue;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
