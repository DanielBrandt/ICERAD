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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4ScoringManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsList.hh"
#include "QGSP_BERT.hh"



#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
    
    
    G4RunManager* runManager = new G4RunManager;
    G4ScoringManager* scoreManager = G4ScoringManager::GetScoringManager();
    
    // Set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction);
    
    //G4VUserPhysicsList* physics = new QGSP_BERT();
    PhysicsList* physics = new PhysicsList();
    runManager->SetUserInitialization(physics);
    
    runManager->SetUserAction(new PrimaryGeneratorAction);
    
    runManager->Initialize();
    
    
    
    
#ifdef G4VIS_USE
    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
#endif
    
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc,argv);
    //UImanager->ApplyCommand("/control/execute file_name");
    ui->SessionStart();
    delete ui;
    
    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    //                 owned and deleted by the run manager, so they should not
    //                 be deleted in the main() program !
#ifdef G4VIS_USE
    delete visManager;
#endif
    delete runManager;
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
