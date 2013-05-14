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
#ifndef XVCrystalPlanarAnalytical_h
#define XVCrystalPlanarAnalytical_h

#include "XVCrystalCharacteristic.hh"
#include "XAtomicScreeningFunction.hh"
#include "XThomasFermiScreeningRadius.hh"

class XVCrystalPlanarAnalytical:public XVCrystalCharacteristic {

private:
    XAtomicScreeningFunction *fScreeningFunction;
    XThomasFermiScreeningRadius *fThomasFermiScreeningRadius;
    G4int fNumberOfPlanes;

public:
    //set function
    void SetNumberOfPlanes(G4int);
    void SetScreeningFunction(XAtomicScreeningFunction*);
    void SetTFSR(XThomasFermiScreeningRadius*);

    //retrieval function
    G4int GetNumberOfPlanes();
    XAtomicScreeningFunction* GetScreeningFunction();
    XThomasFermiScreeningRadius* GetTFSR();
    
    virtual G4double ComputeValueForSinglePlane(G4double,G4VPhysicalVolume*) = 0;
    
    //virtual function of XVCrystalCharacteristic
    G4ThreeVector ComputeValue(G4ThreeVector,G4VPhysicalVolume*);
    
    //Contructors
    XVCrystalPlanarAnalytical();
    ~XVCrystalPlanarAnalytical();
};

#endif
