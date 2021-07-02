/* -------------------------------------------------------------------------*
*								SPHinXsys									*
* --------------------------------------------------------------------------*
* SPHinXsys (pronunciation: s'finksis) is an acronym from Smoothed Particle	*
* Hydrodynamics for industrial compleX systems. It provides C++ APIs for	*
* physical accurate simulation and aims to model coupled industrial dynamic *
* systems including fluid, solid, multi-body dynamics and beyond with SPH	*
* (smoothed particle hydrodynamics), a meshless computational method using	*
* particle discretization.													*
*																			*
* SPHinXsys is partially funded by German Research Foundation				*
* (Deutsche Forschungsgemeinschaft) DFG HU1527/6-1, HU1527/10-1				*
* and HU1527/12-1.															*
*                                                                           *
* Portions copyright (c) 2017-2020 Technical University of Munich and		*
* the authors' affiliations.												*
*                                                                           *
* Licensed under the Apache License, Version 2.0 (the "License"); you may   *
* not use this file except in compliance with the License. You may obtain a *
* copy of the License at http://www.apache.org/licenses/LICENSE-2.0.        *
*                                                                           *
* --------------------------------------------------------------------------*/
/**
 * @file 	particle_generator_lattice.h
 * @brief 	This is the base class of particle generator, which generates particles
 * 			with given positions and volumes. The direct generator simply generate
 * 			particle with given position and volume. The lattice generator generate
 * 			at lattice position by check whether the poision is contained by a SPH body.
 * @author	Xiangyu Hu, Chi Zhang, Yongchuan Yu
 */

#ifndef PARTICLE_GENERATOR_LATTICE_SHELL_H
#define PARTICLE_GENERATOR_LATTICE_SHELL_H

#include "base_particle_generator.h"
#include <random>

namespace SPH {

	class ComplexShape;
	class ParticleSpacingByBodyShape;

	/**
	* @class ShellParticleGeneratorLattice
	* @brief generate particles from lattice positions for a body.
	*/
	class ShellParticleGeneratorLattice : public ParticleGenerator
	{
	public:
		ShellParticleGeneratorLattice();
		virtual ~ShellParticleGeneratorLattice() {};

		virtual void initialize(SPHBody* sph_body) override;
		virtual void createBaseParticles(BaseParticles* base_particles) override;
	protected:
		Real lattice_spacing_; // this will be the actual input, the particle spacing
		BoundingBox domain_bounds_;
		ComplexShape* body_shape_;

		Real total_volume_plate_; // calculated from level set
		Real total_volume_tube_;
		Real body_surface_area_; // ??
		Real global_avg_thickness_;
		Real particle_spacing_; // input from ParticleAdaptation
		Real avg_particle_volume_; // calculated as: particle spacing^2 * global avg thickness
		int number_of_particles_;

		// void calculateTotalVolume(){ total_volume_= 10000.0; };
		// void calculateGlobalAvgThickness(){ global_avg_thickness_= 4.0; };
		// void calculateAvgParticleSize(){ avg_particle_size_= particle_spacing_ * particle_spacing_ * global_avg_thickness_; };
		// void calculateNumberOfParticles(){ number_of_particles_ = total_volume_ / avg_particle_size_; };

		int generateRandomIntInRange(int min, int max)
		{
			std::random_device rd;
			std::default_random_engine eng(rd());
			std::uniform_int_distribution<int> distr(min, max);

			int random_int = distr(eng);
			//std::cout << "random int: " << random_int << "\n";

			return random_int;
		};

		virtual void createABaseParticle(BaseParticles* base_particles, 
			Vecd& particle_position, Real particle_volume, size_t& total_real_particles);
	};
}
#endif //PARTICLE_GENERATOR_LATTICE_SHELL_H