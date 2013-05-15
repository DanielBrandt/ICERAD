#ifndef Tst1PhysicsList_h
#define Tst1PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "ProcessChanneling.hh"
#include "G4VModularPhysicsList.hh"

class PhysicsList: public G4VUserPhysicsList
{
private:
    
public:
    PhysicsList();
    ~PhysicsList();
    
    //Add processes
    void AddStandardSS();
    void AddChanneling();
    void AddDecay();
    void AddStepMax();
    
    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();
private:
    
};

#endif
