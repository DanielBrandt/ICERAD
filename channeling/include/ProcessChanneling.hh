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

//#include "XPhysicalLattice.hh"
//#include "XLatticeManager3.hh"

class G4Material;

class ProcessChanneling : public G4VDiscreteProcess 
{
  public:

     ProcessChanneling(const G4String& processName ="ProcessChanneling" );

  virtual ~ProcessChanneling();
  
  virtual G4VParticleChange* PostStepDoIt(
                const G4Track&, const G4Step& );
  
  virtual G4bool IsApplicable(const G4ParticleDefinition&);

  virtual void BuildPhysicsTable(const G4ParticleDefinition&);
                           
  protected:

  virtual G4double GetMeanFreePath(
                const G4Track&, G4double, G4ForceCondition* );

    G4double GetChannelingAcceptanceProbability(const G4Track& aTrack);
    G4double GetChannelingCriticalAngle(const G4Track& aTrack);
    G4double GetChannelingMaximumEfficiency(const G4Track& aTrack);
    G4double GetChannelingMeanFreePath(const G4Track& aTrack);

    G4bool IsInChanneling(const G4Track& aTrack);
    void ProjectMomentumInCrystalCoordinateSystem(const G4Track& aTrack);

  private:
  
  // hide assignment operator as private 
     ProcessChanneling(ProcessChanneling&);
     ProcessChanneling& operator=(const ProcessChanneling& right);

  private:
    //XPhysicalLattice* fLattice;
    G4double fTransverseMomentumX;
    G4double fTransverseMomentumY;
    G4double fLongitudinalMomentum;
    std::ofstream fFileOut;

};

#endif










