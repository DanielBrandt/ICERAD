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
#include "XThomasFermiScreeningRadius.hh"

class XVCrystalPlanarAnalytical:public XVCrystalCharacteristic {

private:
    G4int fNumberOfPlanes;
    XThomasFermiScreeningRadius *fThomasFermiScreeningRadius;
    G4double fThermalVibrationAmplitude;

public:
    //set function
    void SetNumberOfPlanes(G4int);
    void SetTFSR(XThomasFermiScreeningRadius*);
    void SetThermalVibrationAmplitude(G4double);

    //retrieval function
    G4int GetNumberOfPlanes();
    XThomasFermiScreeningRadius* GetTFSR();
    G4double GetThermalVibrationAmplitude();

    virtual G4double ComputeValueForSinglePlane(G4double vPosition,const G4Track& aTrack) = 0;
    
    //virtual function of XVCrystalCharacteristic
    G4ThreeVector ComputeValue(G4ThreeVector,const G4Track& aTrack);
    
    //Contructors
    XVCrystalPlanarAnalytical();
    ~XVCrystalPlanarAnalytical();
};

#endif
