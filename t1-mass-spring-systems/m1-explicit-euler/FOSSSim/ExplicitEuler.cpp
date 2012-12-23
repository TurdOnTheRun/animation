#include "ExplicitEuler.h"
#include <iostream>
#include <fstream>
#include "SimpleGravityForce.h"

using namespace std;

ofstream text_file;
int step_count = 0;

ExplicitEuler::ExplicitEuler()
: SceneStepper()
{
  text_file.open ("kinetic_energy.txt");
}

ExplicitEuler::~ExplicitEuler()
{
  text_file.close();
}

bool ExplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
    VectorXs& x = scene.getX();
    VectorXs& v = scene.getV();
    const VectorXs& m = scene.getM();
    // if( scene.isFixed(i) )  // Determine if the ith particle is fixed

    int num_particles = scene.getNumParticles();
    VectorXs forces(num_particles * 2);
    VectorXs dx(num_particles * 2);
    VectorXs dv(num_particles * 2);
    for (int i = 0; i < num_particles * 2; i++){
      forces(i) = 0.0;
      dx(i) = 0.0;
      dv(i) = 0.0;
    }
    scene.accumulateGradU(forces, dx, dv);//, const VectorXs& dx, const VectorXs& dv )

    for (int i = 0; i < num_particles; i++){
      if (!scene.isFixed(i)){
        int index = 2 * i; // even indeces of vector are x params and odd are y params

        const Vector2s next_velocity(v(index) + dt*forces(index)/m(index),
                                     v(index+1) + dt*forces(index+1)/m(index));
        scene.setVelocity(i, next_velocity);
        
        const Vector2s next_position(x(index) + dt*v(index),
                                     x(index + 1) + dt*v(index+1));
        scene.setPosition(i, next_position);

        scalar kinetic_energy = 0;
        text_file << step_count*dt << "\t" << scene.computeKineticEnergy() << endl;
      }
    }

    step_count++;
    return true;
}

std::string ExplicitEuler::getName() const
{
    return "Explicit Euler";
}
