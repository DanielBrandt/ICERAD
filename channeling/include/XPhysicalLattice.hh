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
/// \file exoticphysics/phonon/include/XPhysicalLattice.hh
/// \brief Definition of the XPhysicalLattice class
//
// $Id$
//
#ifndef XPhysicalLattice_h
#define XPhysicalLattice_h 1

#include "XLogicalLattice.hh"
#include "G4ThreeVector.hh"
#include "G4AffineTransform.hh"
#include "XUnitCell.hh"

class G4VPhysicalVolume;

class XPhysicalLattice{
    
private:
    G4double fTheta, fPhi;
    XLogicalLattice* fLattice;
    G4VPhysicalVolume* fVolume;
    
    double fA;       //Scaling constant for Anh.Dec. mean free path
    double fB;       //Scaling constant for Iso.Scat. mean free path
    double fDosL;    //Density of states for L-phonons
    double fDosST;   //Density of states for ST-phonons
    double fDosFT;    //Density of states for FT-phonons
    double fBeta, fGamma, fLambda, fMu; //dynamical constants for material
    
    
public:
    G4AffineTransform fLocalToGlobal;
    G4AffineTransform fGlobalToLocal;
    
    void SetDynamicalConstants(double, double, double, double);
    void SetScatteringConstant(G4double);
    void SetAnhDecConstant(G4double);
    void SetLDOS(double);
    void SetSTDOS(double);
    void SetFTDOS(double);
    
    double GetBeta();
    double GetGamma();
    double GetLambda();
    double GetMu();
    G4double GetScatteringConstant();
    G4double GetAnhDecConstant();
    double GetLDOS();
    double GetSTDOS();
    double GetFTDOS();
    
    XPhysicalLattice();
    XPhysicalLattice(G4VPhysicalVolume*, XLogicalLattice*);
    ~XPhysicalLattice();
    double MapKtoV(int, G4ThreeVector);
    G4ThreeVector MapKtoVDir(int, G4ThreeVector);
    G4VPhysicalVolume* GetVolume();
    void SetPhysicalVolume(G4VPhysicalVolume*);
    void SetXLogicalLattice(XLogicalLattice*);
    void SetLatticeOrientation(G4double, G4double);
    void SetMillerOrientation(int, int, int);
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
    // Begin channeling specific code
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
    
public:
    //set methods
    void SetUnitCell(XUnitCell*);
    G4ThreeVector ProjectVectorFromWorldToLattice(G4ThreeVector);
    G4ThreeVector ProjectVectorFromLatticeToWorld(G4ThreeVector);
    G4ThreeVector GetLatticeDirection();

    //retrieval methods
    XUnitCell* GetXUnitCell();
    XLogicalLattice* GetLogicalLattice();
    G4int GetMiller(G4int);

    //general functions
    G4double ComputeInterplanarPeriod();
    
private:
    G4int fMillerOrientation[3];
    XUnitCell* fUnitCell;
};

#endif
