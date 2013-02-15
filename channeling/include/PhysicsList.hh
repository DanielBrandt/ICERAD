#ifndef Tst1PhysicsList_h
#define Tst1PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "ProcessChanneling.hh"

class PhysicsList: public G4VUserPhysicsList
{
  public:
    PhysicsList();
    ~PhysicsList();

    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();
private:
   
};

#endif
