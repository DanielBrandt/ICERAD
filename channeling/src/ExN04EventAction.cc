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

#include "ExN04EventAction.hh"

#include "ExN04TrackerHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include "G4THitsMap.hh"

ExN04EventAction::ExN04EventAction()
{
    trackerCollID = -1;
    fFileOut.open("data.txt",std::ios_base::app);
}

ExN04EventAction::~ExN04EventAction()
{
    fFileOut.close();
}

void ExN04EventAction::BeginOfEventAction(const G4Event*)
{
    G4SDManager * SDman = G4SDManager::GetSDMpointer();
    if(trackerCollID<0)
    {
        G4String colNam;
        trackerCollID = SDman->GetCollectionID(colNam="trackerCollection");
    }
}

void ExN04EventAction::EndOfEventAction(const G4Event* evt)
{
    G4cout << ">>> Event " << evt->GetEventID() << G4endl;
    
    if(trackerCollID<0) return;
    
    G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    ExN04TrackerHitsCollection* THC = 0;
    
    if(HCE){
        THC = (ExN04TrackerHitsCollection*)(HCE->GetHC(trackerCollID));
    }
    
    if(THC){
        int n_hit = THC->entries();
        G4cout << "     " << n_hit << " hits are stored in ExN04TrackerHitsCollection." << G4endl;
        G4ThreeVector pos;
        G4double vCorrection = 1.E6/(10.*cm);
        for(int i=0 ; i<n_hit; i++ ){
            pos = (THC->GetVector()->at(i))->GetPos();
            fFileOut << pos.y()*vCorrection << " " << pos.z()*vCorrection << std::endl;
        }
    }
}
