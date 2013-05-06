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

#include "XVCrystalElectricalCharacteristicsMoliere.hh"

XVCrystalElectricalCharacteristicsMoliere::XVCrystalElectricalCharacteristicsMoliere(){
    InitializeXVCrystalElectricalCharacteristicsMoliere();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XVCrystalElectricalCharacteristicsMoliere::~XVCrystalElectricalCharacteristicsMoliere(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XVCrystalElectricalCharacteristicsMoliere::InitializeXVCrystalElectricalCharacteristicsMoliere(){
    
    fAlfa[0] = 0.1;
    fAlfa[1] = 0.55;
    fAlfa[2] = 0.35;
    
    fBeta[0] = 6.0;
    fBeta[1] = 1.2;
    fBeta[2] = 0.3;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalElectricalCharacteristicsMoliere::GetPotentialSinglePlane(G4double vXposition){
    G4double vPotentialSinglePlane = 0.;
    
    for(unsigned int i=0;i<3;i++){
        vPotentialSinglePlane += ( fAlfa[i]/fBeta[i] * exp( - fabs(vXposition)) * fBeta[i] * EvaluateInverseThomasFermiRadius( GetUnitCell()->GetBase(0)->GetElement() ));
    }
    
    //vPotentialSinglePlane *= 2. * M_PI * GetUnitCell()->EvaluateDirectPeriod(GetPhysicalLattice()->GetMillerOrientation(0),GetPhysicalLattice()->GetMillerOrientation(1),GetPhysicalLattice()->GetMillerOrientation(2));
    
    
    return vPotentialSinglePlane;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalElectricalCharacteristicsMoliere::GetNormalizedElectronDensity(G4ThreeVector vPositionVector){
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalElectricalCharacteristicsMoliere::GetNormalizedNucleiDensity(G4ThreeVector vPositionVector){
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XVCrystalElectricalCharacteristicsMoliere::GetPotential(G4ThreeVector vPositionVector){
    G4double vPotential = GetPotentialSinglePlane(vPositionVector.x());
   return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XVCrystalElectricalCharacteristicsMoliere::GetElectricalField(G4ThreeVector vPositionVector){
    return G4ThreeVector(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
