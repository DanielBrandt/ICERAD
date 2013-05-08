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
#ifndef XVCrystalElectricalCharacteristics_h
#define XVCrystalElectricalCharacteristics_h

#include "XLatticeManager3.hh"

using namespace std;

class XVCrystalElectricalCharacteristics {

private:
    XLatticeManager3* fLatticeManager;
    G4VPhysicalVolume* fVolume;
    
public:
    //retrieval functions
    XPhysicalLattice* GetPhysicalLattice();
    XUnitCell* GetUnitCell();
    XLogicalLattice* GetLogicalLattice();
    G4VPhysicalVolume* GetPhysicalVolume();
    
    
    //set methods
    void SetVolume(G4VPhysicalVolume*);
    
    //virtual function in XVCrystalElectricalCharacteristics
    virtual G4double GetNormalizedElectronDensity(G4ThreeVector) {return 0.;};
    virtual G4double GetNormalizedNucleiDensity(G4ThreeVector) {return 0.;};
    virtual G4double GetPotential(G4ThreeVector) {return 0.;};
    virtual G4ThreeVector GetElectricalField(G4ThreeVector) {return G4ThreeVector(0.,0.,0.);};
        
    //Contructors
    XVCrystalElectricalCharacteristics();
    ~XVCrystalElectricalCharacteristics();
};

#endif
