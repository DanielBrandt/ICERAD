#include "PhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ios.hh"          

#include "G4Proton.hh"    

PhysicsList::PhysicsList():  G4VUserPhysicsList()
{

}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
  G4Proton::ProtonDefinition();
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    if(particleName=="proton")
      {
	G4cout<<"\n\nPhysicsList::ConstructParticle: \n\tFOUND PROTON...\n"<<G4endl;
	pmanager->AddDiscreteProcess(new ProcessChanneling());
      }

  }
}

void PhysicsList::SetCuts()
{
  // These values are used as the default production thresholds
  // for the world volume.
  SetCutsWithDefault();
}


