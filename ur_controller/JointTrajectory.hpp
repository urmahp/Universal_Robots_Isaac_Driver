#pragma once

#include "engine/gems/algorithm/timeseries.hpp"
#include "JointSegment.hpp"

namespace isaac
{
namespace ur_controller
{
/*!
 * \brief This JointTrajectory Class is used store a trajectory for one joint.
 * The trajectory consist of waypoints that consist of time, position, velocity and acceleration.
 * It uses JointSegment to calculate the segments between all the waypoints and interpolate between
 * two waypoints.
 */

class JointTrajectory
{
public:
  /*!
   * \brief Construct a new Joint Trajectory object
   */
  JointTrajectory();

  /*!
   * \brief Storing the new trajectory and creating segment for each waypoint in the trajectory.
   *
   * \param trajectory trajectory for the joint to follow.
   */
  void initTrajectory(const Timeseries<VectorXd, double>& trajectory);

  /*!
   * \brief Calculates current position, velocity and acceleration, based on the time_stamp.
   *
   * \param stamp Current time to interpolate.
   * \param pos Variable to store position.
   * \param vel Variable to store velocity.
   * \param acc Variable to store acceleration.
   */
  void interpolate(const double& stamp, double& pos, double& vel, double& acc);

  /*!
   * \returns end time of trajectory.
   */
  const double endTime();

private:
  // Trajectory of waypoints for a joint
  Timeseries<VectorXd, double> joint_trajectory_;

  // List of segments between the waypoints
  std::vector<JointSegment> segments_;
};

}  // namespace ur_controller
}  // namespace isaac