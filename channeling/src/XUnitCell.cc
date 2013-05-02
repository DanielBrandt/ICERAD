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
    //for(G4int i=0;i<MAXATOMNUMBER;i++) fLatticeAtomPosition[i] = G4ThreeVector(0.,0.,0.);
    fSize = G4ThreeVector(1. * angstrom,1. * angstrom,1. * angstrom);
    fAngle = G4ThreeVector(0.5 * radian,0.5 * radian,0.5 * radian);
    fNumberOfBases = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector& XUnitCell::GetSize(){
    return fSize;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ThreeVector& XUnitCell::GetAngle(){
    return fAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

XLogicalBase* XUnitCell::GetBase(G4int i){
    if(i<fNumberOfBases){
        return fBase[i];
    }
    else{
        G4cout << "XUnitCell::GetBase(G4int) Base " << i << " does not exist" << std::endl;
        return NULL;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::SetBase(G4int i,XLogicalBase* base){
    if(i<fNumberOfBases){
        fBase[i] = base;
    }
    else{
        G4cout << "XUnitCell::SetBase Base(G4int,G4XLogicalBase) " << i << " does not exist" << std::endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void XUnitCell::AddBase(XLogicalBase* base){
    fNumberOfBases++;
    //the new added basis will be in the last of the [0,fNumberOfBases-1] bases
    fBase[fNumberOfBases-1] = base;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateVolume()
{
    if(IsOrthogonal()){
        return ( fSize.x()*fSize.y()*fSize.z() );
    }
    else{
        return ( fSize.x()*fSize.y()*fSize.z()*cos(fAngle.x())*sin(fAngle.z()) );
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateMillerOverSizeSquared(G4int h, G4int k, G4int l)
{
    return pow(h/fSize.x(),2.) + pow(k/fSize.y(),2.) + pow(l/fSize.z(),2.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateMillerPerSizeSquared(G4int h, G4int k, G4int l)
{
    return pow(h*fSize.x(),2.) + pow(k*fSize.y(),2.) + pow(l*fSize.z(),2.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateReciprocalVectorSquared(G4int h, G4int k, G4int l)
{
    
    if(IsOrthogonal()){
        return EvaluateReciprocalPeriodSquared(h,k,l);
    }
    else{
        G4double vTempDouble[6];
        G4double vVolume = EvaluateVolume();
        
        vTempDouble[0] = fSize.y() * fSize.z() * sin(fAngle.y());
        vTempDouble[0] = pow(vTempDouble[0] * h,2.) / vVolume;
        
        vTempDouble[1] = fSize.x() * fSize.z() * sin(fAngle.x());
        vTempDouble[1] = pow(vTempDouble[1] * k,2.) / vVolume;
        
        vTempDouble[2] = fSize.x() * fSize.y() * sin(fAngle.z());
        vTempDouble[2] = pow(vTempDouble[2] * l,2.) / vVolume;
        
        vTempDouble[3] = fSize.x() * fSize.y() * pow(fSize.z(),2.) * (cos(fAngle.x()) * cos(fAngle.y()) - cos(fAngle.z()));
        vTempDouble[3] *= (2. * h * k);
        
        vTempDouble[4] = fSize.x() * pow(fSize.y(),2.) * fSize.z() * (cos(fAngle.z()) * cos(fAngle.x()) - cos(fAngle.y()));
        vTempDouble[4] *= (2. * l * h);
        
        vTempDouble[5] = pow(fSize.x(),2.) * fSize.y() * fSize.z() * (cos(fAngle.y()) * cos(fAngle.z()) - cos(fAngle.x()));
        vTempDouble[5] *= (2. * l * l);

        G4double vReciprocalVectorSquared = 0.0;
        vReciprocalVectorSquared = (vTempDouble[0]+vTempDouble[1]+vTempDouble[2]) / vVolume;
        vReciprocalVectorSquared += (vTempDouble[3]+vTempDouble[4]+vTempDouble[5]);
        vReciprocalVectorSquared  *= (4. * M_PI * M_PI);
        vReciprocalVectorSquared /= vVolume;
        return vReciprocalVectorSquared;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateReciprocalPeriodSquared(G4int h, G4int k, G4int l)
{
    G4double vReciprocalPeriodSquared = EvaluateMillerOverSizeSquared(h,k,l) * (4. * M_PI * M_PI);
    return vReciprocalPeriodSquared;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateReciprocalPeriod(G4int h, G4int k, G4int l)
{
    return sqrt(EvaluateReciprocalPeriodSquared(h,k,l));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateDirectVectorSquared(G4int h, G4int k, G4int l)
{
    if(IsOrthogonal()){
        return EvaluateMillerPerSizeSquared(h,k,l);
    }
    else{
        double vDirectVectorSquared = 0.0;
        vDirectVectorSquared = EvaluateMillerPerSizeSquared(h,k,l);
        vDirectVectorSquared += 2. * h * k * fSize.y() * fSize.z() * cos(fAngle.y()) ;
        vDirectVectorSquared += 2. * l * h * fSize.x() * fSize.z() * cos(fAngle.x()) ;
        vDirectVectorSquared += 2. * l * l * fSize.x() * fSize.y() * cos(fAngle.z()) ;
        return vDirectVectorSquared;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateDirectVector(G4int h, G4int k, G4int l)
{
    return sqrt(EvaluateDirectVectorSquared(h,k,l));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateDirectPeriodSquared(G4int h, G4int k, G4int l)
{
    G4double vDirectPeriodSquared = EvaluateMillerOverSizeSquared(h,k,l);
    return sqrt(1./vDirectPeriodSquared);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double XUnitCell::EvaluateDirectPeriod(G4int h, G4int k, G4int l)
{
    return sqrt(EvaluateDirectPeriodSquared(h,k,l));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4bool XUnitCell::IsOrthogonal()
{
    if(fAngle.x() == M_PI/2)
        if(fAngle.y() == M_PI/2)
            if(fAngle.z() == M_PI/2)
                return true;
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool XUnitCell::IsCubic()
{
    if(IsOrthogonal())
        if(fSize.x() == fSize.y())
            if(fSize.y() == fSize.z())
                return true;
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
