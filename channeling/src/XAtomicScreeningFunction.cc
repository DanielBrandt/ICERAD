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

#include "XAtomicScreeningFunction.hh"

XAtomicScreeningFunction::XAtomicScreeningFunction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XAtomicScreeningFunction::~XAtomicScreeningFunction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunction::GetDerivativePrecision(){
    return fDerivativePrecision;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XAtomicScreeningFunction::SetDerivativePrecision(G4double vPrecision){
    fDerivativePrecision = vPrecision;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunction::ComputeScreeningFunctionIntegral(G4double vXposition, G4Element *vElement, G4ParticleDefinition *vParticle){
    return 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunction::ComputeScreeningFunction(G4double vXposition, G4Element *vElement, G4ParticleDefinition *vParticle){
    return 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunction::ComputeScreeningFunctionFirstDerivative(G4double vXposition, G4Element *vElement, G4ParticleDefinition *vParticle){
    G4double vDerivative = ComputeScreeningFunction(vXposition+fDerivativePrecision,vElement,vParticle);
    vDerivative -= ComputeScreeningFunction(vXposition-fDerivativePrecision,vElement,vParticle);
    vDerivative /= (2.*fDerivativePrecision);
    return vDerivative;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XAtomicScreeningFunction::ComputeNormalization(G4double vXposition, G4Element *vElement, G4ParticleDefinition *vParticle){
    return 1.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
