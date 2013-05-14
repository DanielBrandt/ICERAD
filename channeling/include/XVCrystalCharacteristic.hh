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
#ifndef XVCrystalCharacteristic_h
#define XVCrystalCharacteristic_h

#include "XLatticeManager3.hh"

using namespace std;

class XVCrystalCharacteristic {

private:
    XLatticeManager3* fLatticeManager;
    
public:
    //retrieval functions
    XPhysicalLattice* GetPhysicalLattice(G4VPhysicalVolume*);
    XUnitCell* GetUnitCell(G4VPhysicalVolume*);
    XLogicalLattice* GetLogicalLattice(G4VPhysicalVolume*);
        
    //virtual function to compute value starting from the point in the xtal reference frame and the physical volume of the xtal
    virtual G4ThreeVector ComputeValue(G4ThreeVector,G4VPhysicalVolume*) = 0;
    virtual G4double ComputePositionInPeriodicUnit(G4double,G4double&);

    //Contructors
    XVCrystalCharacteristic();
    ~XVCrystalCharacteristic();
};

#endif
