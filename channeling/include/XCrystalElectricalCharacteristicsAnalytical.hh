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
// $Id$
//
#ifndef XCrystalElectricalCharacteristicsAnalytical_h
#define XCrystalElectricalCharacteristicsAnalytical_h

#include "XVCrystalElectricalCharacteristics.hh"
#include "XAtomicScreeningFunction.hh"
#include "XThomasFermiScreeningRadius.hh"

class XCrystalElectricalCharacteristicsAnalytical:public XVCrystalElectricalCharacteristics {

private:
    void InitializeXCrystalElectricalCharacteristicsAnalytical();
    XAtomicScreeningFunction *fScreeningFunction;
    XThomasFermiScreeningRadius *fThomasFermiScreeningRadius;
    G4int fNumberOfPlanes;

public:
    //set function
    void SetAtomicScreeningFunction(XAtomicScreeningFunction *vScreeningFunction);
    void SetThomasFermiScreeningFunction(XThomasFermiScreeningRadius*);

    //retrieval function
    XAtomicScreeningFunction* GetAtomicScreeningFunction();
    XThomasFermiScreeningRadius* GetThomasFermiScreeningFunction();
       
    //virtual function
    G4double GetNormalizedElectronDensity(G4ThreeVector);
    G4double GetNormalizedNucleiDensity(G4ThreeVector);
    G4double GetPotential(G4ThreeVector);
    G4ThreeVector GetElectricalField(G4ThreeVector);
    
    //class-only functions
    G4double GetPotentialSinglePlane(G4double);
    
    //Contructors
    XCrystalElectricalCharacteristicsAnalytical();
    ~XCrystalElectricalCharacteristicsAnalytical();
};

#endif
