/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef CONSTANTGRAINFORCESPOSTPROCESSOR_H
#define CONSTANTGRAINFORCESPOSTPROCESSOR_H

#include "GeneralVectorPostprocessor.h"
// #include "ComputeGrainForceAndTorque.h"
#include "ConstantGrainForceAndTorque.h"

//Forward Declarations
class ConstantGrainForcesPostprocessor;

template<>
InputParameters validParams<ConstantGrainForcesPostprocessor>();

/**
 *  ConstantGrainForcesPostprocessor is a type of VectorPostprocessor that outputs the
 *  values of an arbitrary user-specified set of postprocessors as a vector in the order specified by the user.
 */

class ConstantGrainForcesPostprocessor :
  public GeneralVectorPostprocessor
{
public:
  /**
    * Class constructor
    * @param name The name of the object
    * @param parameters The input parameters
    */
  ConstantGrainForcesPostprocessor(const InputParameters & parameters);

  /**
   * Destructor
   */
  virtual ~ConstantGrainForcesPostprocessor() {}

  /**
   * Initialize, clears the postprocessor vector
   */
  virtual void initialize(){};

  /**
   * Populates the postprocessor vector of values with the supplied postprocessors
   */
  virtual void execute();

  ///@{
  /**
   * no-op because the postprocessors are already parallel consistent
   */
  virtual void finalize() {}
  virtual void threadJoin(const UserObject &) {}
  ///@}

protected:
  /// The VectorPostprocessorValue object where the results are stored
  VectorPostprocessorValue & _grain_force_torque_vector;

  /// The vector of PostprocessorValue objects that are used to get the values of the postprocessors
  const ConstantGrainForceAndTorque & _const_grain_force_torque;
  const std::vector<RealGradient> & _grain_forces;
  const std::vector<RealGradient> & _grain_torques;
  const std::vector<RealGradient> & _grain_force_derivatives;
  const std::vector<RealGradient> & _grain_torque_derivatives;

  unsigned int _total_grains;
};

#endif //CONSTANTGRAINFORCESPOSTPROCESSOR_H
