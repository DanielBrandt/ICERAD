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

#include "ProcessChanneling.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4VParticleChange.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include "G4RandomTools.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4GeometryTolerance.hh"

#include "G4SystemOfUnits.hh"

ProcessChanneling::ProcessChanneling(const G4String& aName):G4VDiscreteProcess(aName){
    fLatticeManager = XLatticeManager3::GetXLatticeManager();
    
    G4double kCarTolerance = G4GeometryTolerance::GetInstance()->GetSurfaceTolerance();
    G4cout<<"\n ProcessChanneling::Constructor: Geometry surface tolerance is: " << kCarTolerance / mm << " mm";
    if(verboseLevel>1) {
        G4cout << GetProcessName() << " is created "<< G4endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ProcessChanneling::~ProcessChanneling(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ProcessChanneling::ProcessChanneling(ProcessChanneling& right):G4VDiscreteProcess(right){
    ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double ProcessChanneling::GetChannelingCriticalEnergy(const G4Track& aTrack){
    G4double vMaximumPotentialWell = 21. * eV; //Maximum Potential Well Energy U_0 for Si(1,1,0)
    return vMaximumPotentialWell;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void ProcessChanneling::UpdateMomentum(const G4Track& aTrack){
    fMomentum = fLatticeManager->GetXPhysicalLattice(aTrack.GetStep()->GetPostStepPoint()->GetPhysicalVolume())->ProjectVectorFromWorldToLattice(aTrack.GetMomentum());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double ProcessChanneling::GetChannelingAcceptanceProbability(const G4Track& aTrack){
    G4double vChannelingAcceptanceProbability = pow( 1. - pow(fMomentum.y() / GetChannelingCriticalEnergy(aTrack),2.),0.5);
    return vChannelingAcceptanceProbability;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool ProcessChanneling::IsInChanneling(const G4Track& aTrack){
    //----------------------------------------
    // check if the particle momentum
    // transverse to the (h,k,l) plane
    // is small enough to permit channeling
    //----------------------------------------
    UpdateMomentum(aTrack);
    
    if( fabs(fMomentum.y()) < GetChannelingCriticalEnergy(aTrack) ){
        if( G4UniformRand() < GetChannelingAcceptanceProbability(aTrack)){
            return true;
        }
    }
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double
ProcessChanneling::GetChannelingMeanFreePath(const G4Track& aTrack)
{
    // dechanneling length is the dacay length for the dechanneling processes
    G4double vChannelingMeanFreePathNearNuclei = 1.5 * mm; // dechanneling length for particles which enter the crystal near nuclei
    G4double vChannelingMeanFreePathFarFromNuclei = 20. * cm; // dechannelign length for particles which enter the crystal far from nuclei
    G4double vParticleFractionNearNuclei = 0.2; // fraction of particles which enter the crystal near the nuclei
    G4double vParticleFractionFarFromNuclei = 1. - vParticleFractionNearNuclei; // fraction of particles which enter the crystal far from nuclei
    
    if(G4UniformRand()<0.2){
        return vChannelingMeanFreePathNearNuclei;
    }
    else{
        return vChannelingMeanFreePathFarFromNuclei;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double
ProcessChanneling::GetMeanFreePath(const G4Track& aTrack, G4double /*previousStepSize*/, G4ForceCondition* condition  )
{
    //----------------------------------------
    // the condition is forced to check if
    // the volume has a lattice at each step
    //----------------------------------------
    
    *condition = Forced;
    
    if(aTrack.GetStep()->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="Target")
    {
        if(IsInChanneling(aTrack)){
            return GetChannelingMeanFreePath(aTrack);
        }
    }
    else{
        return DBL_MAX;
    }
    
    return DBL_MAX;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VParticleChange* ProcessChanneling::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep){
    
    aParticleChange.Initialize(aTrack);
    G4VPhysicalVolume* vVolume = aTrack.GetStep()->GetPostStepPoint()->GetPhysicalVolume();
    
    if(vVolume->GetName()=="Target")
    {
        if(IsInChanneling(aTrack)){
            //aParticleChange.ProposeMomentumDirection(fLatticeManager->GetXPhysicalLattice(vVolume)->GetLatticeDirection().unit());
            aParticleChange.ProposeMomentumDirection(G4ThreeVector(1.,1.,0.).unit());
        }
    }
    
    return &aParticleChange;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


G4bool ProcessChanneling::IsApplicable(const G4ParticleDefinition& aPD)
{
    return(aPD.GetPDGCharge()>0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void ProcessChanneling::BuildPhysicsTable(const G4ParticleDefinition&)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


