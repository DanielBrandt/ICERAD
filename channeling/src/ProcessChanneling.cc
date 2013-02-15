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


ProcessChanneling::ProcessChanneling(const G4String& aName)
:G4VDiscreteProcess(aName)
{
    G4double kCarTolerance = G4GeometryTolerance::GetInstance()->GetSurfaceTolerance();
    G4cout<<"\n ProcessChanneling::Constructor: Geometry surface tolerance is: " << kCarTolerance /mm << " mm";
    if (verboseLevel>1) {
        G4cout << GetProcessName() << " is created "<< G4endl;
    }
    fFileOut.open("out.txt");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


ProcessChanneling::~ProcessChanneling()
{
    fFileOut.close();
}

ProcessChanneling::ProcessChanneling(ProcessChanneling& right)
: G4VDiscreteProcess(right)
{;}


void
ProcessChanneling::ProjectMomentumInCrystalCoordinateSystem(const G4Track& aTrack)
{
    //XLatticeManager3* xtal_manager = XLatticeManager3::GetXLatticeManager();
    //fLattice = xtal_manager->GetXPhysicalLattice(aTrack.GetVolume());
    
    //project momentum in the xtal reference frame to check if the particle can be channeled
    G4ThreeVector startMomentum = G4ThreeVector(aTrack.GetMomentumDirection().unit());
    
    //get orthonormal vectors to the crystal plane to evaluate the transverse particle momentum on such a direction
    //starting from transverse momentum we evaluate change in position and momentum in the crystal basis
    G4ThreeVector vPlaneDirectionX = G4ThreeVector(0,1,0); // we have to link to the direction of the lattice
    G4ThreeVector vPlaneDirectionY = G4ThreeVector(0,0,1); // we have to link to the direction of the lattice
    G4ThreeVector vPlaneDirectionZ = G4ThreeVector(1,0,0); // we have to link to the direction of the lattice
    
    //project the momentum vector over the orthonormal vectors
    fTransverseMomentumX = vPlaneDirectionX.dot(startMomentum);
    fTransverseMomentumY = vPlaneDirectionY.dot(startMomentum);
    fLongitudinalMomentum = vPlaneDirectionZ.dot(startMomentum);
}

G4double
ProcessChanneling::GetChannelingCriticalAngle(const G4Track& aTrack)
{
    G4double vMaximumPotentialWell = 21. * eV;//Maximum Potential Well Energy U_0 for Si(1,1,0)
    G4double vChannelingCriticalAngle = pow( vMaximumPotentialWell / (fLongitudinalMomentum*aTrack.GetKineticEnergy()*aTrack.GetStep()->GetPreStepPoint()->GetBeta() )* 2.,0.5);
    G4cout << "\tvChannelingCriticalAngle " << vChannelingCriticalAngle << G4endl;
    G4cout << "\t fLongitudinalMomentum" << fLongitudinalMomentum << G4endl;
    G4cout << "\t aTrack.GetKineticEnergy()" << aTrack.GetKineticEnergy() << G4endl;
    G4cout << "\t aTrack.GetStep()->GetPreStepPoint()->GetBeta()" << aTrack.GetStep()->GetPreStepPoint()->GetBeta() << G4endl;
    return vChannelingCriticalAngle;
}

G4double
ProcessChanneling::GetChannelingMaximumEfficiency(const G4Track& aTrack)
{
    G4double vChannelingMaximumEfficiency = 1.;
    G4cout << "\tvChannelingMaximumEfficiency " << vChannelingMaximumEfficiency << G4endl;
    return vChannelingMaximumEfficiency;
}

G4double
ProcessChanneling::GetChannelingAcceptanceProbability(const G4Track& aTrack)
{
    G4double vChannelingAcceptanceProbability = GetChannelingMaximumEfficiency(aTrack) * pow( 1. - pow(fTransverseMomentumX/GetChannelingCriticalAngle(aTrack),2.),0.5);
    G4cout << "\tGetChannelingAcceptanceProbability " << vChannelingAcceptanceProbability << G4endl;
    return vChannelingAcceptanceProbability;
}


G4bool
ProcessChanneling::IsInChanneling(const G4Track& aTrack)
{
    //obtain pointer from the xtal_manager tot the xtal
    //XLatticeManager3* xtal_manager = XLatticeManager3::GetXLatticeManager();
    //fLattice = xtal_manager->GetXPhysicalLattice(aTrack.GetVolume());
    
    
    ProjectMomentumInCrystalCoordinateSystem(aTrack);
    
    //check if the particle transverse momentum is low enough to be less than the critical angle for channeling (2. * U_0 * E)^0.5
    // c = 1 coordinates ????????
    // we should loop over main planes or make an algorithm to choose the nearest plane
    G4cout<<"\nProcessChanneling::IsInChanneling:\n\tcalled: "<<G4endl;
    
    if(fLongitudinalMomentum!=0.)
        //if( fabs(fTransverseMomentumX) < GetChannelingCriticalAngle(aTrack) )
            //if( G4UniformRand() < GetChannelingAcceptanceProbability(aTrack))
            {
                fFileOut << fTransverseMomentumX << " ";
                fFileOut << GetChannelingCriticalAngle(aTrack) << " ";
                fFileOut << GetChannelingAcceptanceProbability(aTrack) << std::endl;
                return true;
            }
    return false;
}

G4double
ProcessChanneling::GetChannelingMeanFreePath(const G4Track& aTrack)
{
    //obtain pointer from the xtal_manager tot the xtal
    //XLatticeManager3* xtal_manager = XLatticeManager3::GetXLatticeManager();
    //fLattice = xtal_manager->GetXPhysicalLattice(aTrack.GetVolume());
    
    // dechanneling length is the dacay length for the dechanneling processes
    G4double vChannelingMeanFreePathNearNuclei = 1.5 * mm; // dechanneling length for particles which enter the crystal near nuclei
    G4double vChannelingMeanFreePathFarFromNuclei = 20. * cm; // dechannelign length for particles which enter the crystal far from nuclei
    G4double vParticleFractionNearNuclei = 0.2; // fraction of particles which enter the crystal near the nuclei
    G4double vParticleFractionFarFromNuclei = 1. - vParticleFractionNearNuclei; // fraction of particles which enter the crystal far from nuclei
    
    G4double vChannelingMeanFreePath = 15. * cm; //to be understood how to treat the different kind of particles depending on their impact parameter
    
    return vChannelingMeanFreePath;
}

G4double
ProcessChanneling::GetMeanFreePath(
                                   const G4Track& aTrack, G4double /*previousStepSize*/, G4ForceCondition* condition  )
{
    // Always return DBL_MAX and Forced
    // This ensures that the process is called
    // at the end of every step. In
    // PostStepDoIt the process decides whether
    // the step encountered a volume boundary
    // and a reflection should be applied
    
    //always condition is forced (to be better understood)
    *condition = Forced;
    
    //XLatticeManager3* xtal_manager = XLatticeManager3::GetXLatticeManager();
    //fLattice = xtal_manager->GetXPhysicalLattice(aTrack.GetVolume());
    
    // xtal_manager.HasLattice(volume) (we call the manager to check if the volume has a lattice or not)
    //if( xtal_manager->HasLattice(aTrack.GetVolume()) )
    G4cout<<"\nProcessChanneling::GetMeanFreePath:\n\tcalled in volume: "<<aTrack.GetVolume()->GetName();
    G4double freepath;
    if(aTrack.GetStep()->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="Target")
    {
        
        //if( IsInChanneling(aTrack) )
        freepath = GetChannelingMeanFreePath(aTrack);
        //else freepath = DBL_MAX;
    }
    else freepath = DBL_MAX;
    
    G4cout << "\n\tmean free path:"<<freepath/cm << " cm"<<G4endl;
    
    return freepath;//freepath;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VParticleChange*
ProcessChanneling::PostStepDoIt( const G4Track& aTrack,
                                const G4Step& aStep )
{
    
    //This process handles the interaction of phonons with
    //boundaries. Implementation of this class is highly
    //geometry dependent.Currently, phonons are killed when
    //they reach a boundary. If the other side of the
    //boundary was Al, a hit is registered.
    G4cout<<"\nProcessChanneling::PostStepDoIt:\n\tcalled: " <<G4endl;
    
    aParticleChange.Initialize(aTrack);
    ProjectMomentumInCrystalCoordinateSystem(aTrack);
    G4ThreeVector vNewMomentum = G4ThreeVector(aTrack.GetMomentumDirection().unit());//function of fTransverseMomentum
    
    if(aTrack.GetStep()->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="Target")
        //if( IsInChanneling(aTrack) )
        {
            //Here we update momentum of the particle
            //G4cout << "\t" << vNewMomentum.unit() << G4endl;
            //vNewMomentum += G4ThreeVector(5.,3.,0.).unit();//function of fTransverseMomentum
            vNewMomentum = G4ThreeVector(fLongitudinalMomentum,(G4UniformRand()-0.5)*fTransverseMomentumX,fTransverseMomentumY);
            //G4cout << "\tMomentum " << fLongitudinalMomentum << " " << fTransverseMomentumX << " " << fTransverseMomentumY << G4endl;
        }
    
    aParticleChange.ProposeMomentumDirection(vNewMomentum.unit());
    
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


