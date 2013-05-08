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

#include "XCrystalElectricalCharacteristicsAnalytical.hh"

XCrystalElectricalCharacteristicsAnalytical::XCrystalElectricalCharacteristicsAnalytical(){
    InitializeXCrystalElectricalCharacteristicsAnalytical();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XCrystalElectricalCharacteristicsAnalytical::~XCrystalElectricalCharacteristicsAnalytical(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XCrystalElectricalCharacteristicsAnalytical::InitializeXCrystalElectricalCharacteristicsAnalytical(){
    fNumberOfPlanes = 4;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XCrystalElectricalCharacteristicsAnalytical::SetAtomicScreeningFunction(XAtomicScreeningFunction *vScreeningFunction){
    fScreeningFunction = vScreeningFunction;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XCrystalElectricalCharacteristicsAnalytical::SetThomasFermiScreeningFunction(XThomasFermiScreeningRadius *vThomasFermiScreeningRadius){
    fThomasFermiScreeningRadius = vThomasFermiScreeningRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XAtomicScreeningFunction* XCrystalElectricalCharacteristicsAnalytical::GetAtomicScreeningFunction(){
    return fScreeningFunction;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XThomasFermiScreeningRadius* XCrystalElectricalCharacteristicsAnalytical::GetThomasFermiScreeningFunction(){
    return fThomasFermiScreeningRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalElectricalCharacteristicsAnalytical::GetPotentialSinglePlane(G4double vXposition){
    
    G4double vPotentialSinglePlane = fScreeningFunction->ComputeScreeningFunction(vXposition,GetUnitCell()->GetBase(0)->GetElement());

    vPotentialSinglePlane *= 2. * M_PI * GetUnitCell()->ComputeDirectPeriod(GetPhysicalLattice()->GetMillerOrientation(0),GetPhysicalLattice()->GetMillerOrientation(1),GetPhysicalLattice()->GetMillerOrientation(2));
    
    vPotentialSinglePlane *= (elm_coupling * fThomasFermiScreeningRadius->ComputeScreeningRadius(GetUnitCell()->GetBase(0)->GetElement()));
    
    vPotentialSinglePlane *= (GetUnitCell()->ComputeAtomVolumeDensity());
    
    return vPotentialSinglePlane;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalElectricalCharacteristicsAnalytical::GetNormalizedElectronDensity(G4ThreeVector vPositionVector){
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalElectricalCharacteristicsAnalytical::GetNormalizedNucleiDensity(G4ThreeVector vPositionVector){
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double XCrystalElectricalCharacteristicsAnalytical::GetPotential(G4ThreeVector vPositionVector){
    G4double vInterplanarDistance = GetUnitCell()->ComputeDirectPeriod(GetPhysicalLattice()->GetMillerOrientation(0),GetPhysicalLattice()->GetMillerOrientation(1),GetPhysicalLattice()->GetMillerOrientation(2));
    G4double vPotential = 0.;
    for(G4int i=-(fNumberOfPlanes/2);i<=+(fNumberOfPlanes/2);i++){
        vPotential += GetPotentialSinglePlane(vPositionVector.x() + vInterplanarDistance * i);
    }
    return vPotential;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XCrystalElectricalCharacteristicsAnalytical::GetElectricalField(G4ThreeVector vPositionVector){
    return G4ThreeVector(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
