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
#ifndef XUnitCell_h
#define XUnitCell_h

#include <iostream>
#include <fstream>
#include <string>
#include "G4ThreeVector.hh"

#define MAXLATTICEATOMS 64

using namespace std;

class XUnitCell{

private:
    G4ThreeVector fSize;
    G4ThreeVector fAngle;
    
    
    // position of the atoms are saved in unit cell system, i.e MIN 0. & MAX 1.
    G4ThreeVector fLatticeAtomPosition[MAXLATTICEATOMS];
    G4int fLatticeAtomNumber;

    G4int fLatticeType;
    
    void FindLatticePoints();
    void InitializeXUnitCell();

public:
    G4ThreeVector& GetSize();
    G4ThreeVector& GetAngle();
    
    
    void SetLatticeType(G4int);
    G4int GetLatticeType();
    
    void AddAtom(G4ThreeVector);
    void DeleteAtom(G4ThreeVector);
    
    XUnitCell();
    ~XUnitCell();
};

#endif
