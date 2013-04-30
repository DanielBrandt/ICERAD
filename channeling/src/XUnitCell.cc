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

#include "XUnitCell.hh"
#include "G4PhysicalConstants.hh"
#include <cmath>

XUnitCell::XUnitCell(){
    InitializeXUnitCell();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XUnitCell::~XUnitCell(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::InitializeXUnitCell(){
    fLatticeAtomNumber = 0;
    fLatticeType = 0;
    for(G4uint i=0;i<MAXLATTICEATOMS;i++) fLatticeAtomPosition[i] = G4ThreeVector(0.,0.,0.);
    fSize = G4ThreeVector(1. * angstrom,1. * angstrom,1. * angstrom);
    fAngle = G4ThreeVector(0.5 * radian,0.5 * radian,0.5 * radian);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XUnitCell::GetSize(){
    return fSize;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector XUnitCell::GetAngle(){
    return fAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4uint XUnitCell::GetLatticeType(){
    return fLatticeType;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::SetLatticeType(G4uint vLatticeType){
    fLatticeType = vLatticeType;
    FindLatticePoints();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::AddAtom(G4ThreeVector vAtomPosition){
    fLatticeAtomNumber++;
    //Add an atom to the lattice
    fLatticeAtomPosition[fLatticeAtomNumber - 1] = vAtomPosition;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::DeleteAtom(G4ThreeVector vAtomPosition){
    //Delete atoms in the lattice in the selected position
    fLatticeAtomPosition[fLatticeAtomNumber - 1] = vAtomPosition;
    
    G4uint CheckIfAtomExist = fLatticeAtomNumber;
    for(G4uint i=0;i<fLatticeAtomNumber;i++)
        if(vAtomPosition = fLatticeAtomPosition[i])
        {
            CheckIfAtomExist = i;
            for(G4uint j=(i+1);j<fLatticeAtomNumber);j++)
            {
                fLatticeAtomPosition[j-1]=fLatticeAtomPosition[j];
            }
            i--;
            fLatticeAtomNumber--;
        }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::FindLatticePoints()
{
    if(fLatticeType == 0) //cubic lattice
    {
        AddAtom(G4ThreeVector(0.0,0.0,0.0));
    }
    else if(fLatticeType == "cubicc")//centered cubic lattice
    {
        AddAtom(G4ThreeVector(0.5,0.5,0.5));
    }
    else if(fLatticeType == "bcc")//body centered cubic
    {
        AddAtom(G4ThreeVector(0.0,0.0,0.0));
        AddAtom(G4ThreeVector(0.5,0.5,0.5));
    }
    else if(fLatticeType == "fcc")//face centered lattice
    {
        AddAtom(G4ThreeVector(0.0,0.0,0.0));
        AddAtom(G4ThreeVector(0.5,0.5,0.0));
        AddAtom(G4ThreeVector(0.0,0.5,0.5));
        AddAtom(G4ThreeVector(0.5,0.0,0.5));
    }
    else if(fLatticeType == "diamond")//diamond lattice
    {
        for(unsigned int i=0;i<2;i++)
        {
            AddAtom(G4ThreeVector0.0+0.25*i,0.0+0.25*i,0.0+0.25*i));
            AddAtom(G4ThreeVector0.5+0.25*i,0.5+0.25*i,0.0+0.25*i));
            AddAtom(G4ThreeVector0.0+0.25*i,0.5+0.25*i,0.5+0.25*i));
            AddAtom(G4ThreeVector0.5+0.25*i,0.0+0.25*i,0.5+0.25*i));
        }
    }
    else
    {
        G4cout << "XUnitCell::Not valid type selected!!!!" << endl;
    }
}

