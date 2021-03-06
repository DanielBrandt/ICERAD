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

#ifndef ProcessChanneling_h
#define ProcessChanneling_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VDiscreteProcess.hh"

#include "XLatticeManager3.hh"
#include "XVCrystalCharacteristic.hh"
#include "XCrystalIntegratedDensity.hh"

class ProcessChanneling : public G4VDiscreteProcess
{
public:
    
    ProcessChanneling(const G4String& processName = "ProcessChanneling" );
    
    virtual ~ProcessChanneling();
    
    virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);
    
    virtual G4bool IsApplicable(const G4ParticleDefinition&);
    
    virtual void BuildPhysicsTable(const G4ParticleDefinition&);
    
protected:
    virtual G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* );
    
public:
    XVCrystalCharacteristic* GetPotential();
    void SetPotential(XVCrystalCharacteristic*);

    XVCrystalCharacteristic* GetNucleiDensity();
    void SetNucleiDensity(XVCrystalCharacteristic*);
    
    XVCrystalCharacteristic* GetElectronDensity();
    void SetElectronDensity(XVCrystalCharacteristic*);

    XVCrystalCharacteristic* GetElectricField();
    void SetElectricField(XVCrystalCharacteristic*);
    
    XCrystalIntegratedDensity* GetIntegratedDensity();
    void SetIntegratedDensity(XCrystalIntegratedDensity*);
    
private:
    G4double GetChannelingMeanFreePath(const G4Track& aTrack);
    
    G4bool IsInChanneling(const G4Track& aTrack);

    void UpdatePositionMomentumDensity(const G4Track& aTrack);
    
    G4double ComputeChannelingCriticalEnergy(const G4Track& aTrack);
    G4ThreeVector ComputeTransverseEnergy(const G4Track& aTrack);
    
    void InitializeCrystalCharacteristics();
    void ComputeCrystalCharacteristicForChanneling(const G4Track& aTrack);

private:
    // hide assignment operator as private
    ProcessChanneling(ProcessChanneling&);
    ProcessChanneling& operator=(const ProcessChanneling& right);
    
private:
    XLatticeManager3* fLatticeManager;
    
    G4ThreeVector fMomentum;
    G4ThreeVector fPosition;
    G4double fDensity;
    G4bool fHasBeenInChanneling;
    
    G4bool fCompute;
  
    XVCrystalCharacteristic* fPotentialEnergy;
    XVCrystalCharacteristic* fNucleiDensity;
    XVCrystalCharacteristic* fElectronDensity;
    XVCrystalCharacteristic* fElectricField;
    
    XCrystalIntegratedDensity* fIntegratedDensity;
    
    std::ofstream fFileOut;
};

#endif










