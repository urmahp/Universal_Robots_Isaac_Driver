#include "JointTrajectory.hpp"

namespace isaac
{
namespace ur_controller
{
JointTrajectory::JointTrajectory() = default;

void JointTrajectory::initTrajectory(const Timeseries<VectorXd, double>& trajectory)
{
  ASSERT(trajectory.empty() == false, "The trajectory shouldn't be empty");
  joint_trajectory_ = trajectory;

  Timeseries<VectorXd, double>::Entry waypoint;
  Timeseries<VectorXd, double>::Entry next_waypoint;
  // Create a vector of segments
  segments_.clear();
  for (unsigned int j = 0; j < trajectory.size() - 1; ++j)
  {
    waypoint = trajectory.at(j);
    next_waypoint = trajectory.at(j + 1);
    JointSegment segment(waypoint, next_waypoint);
    segments_.push_back(segment);
  }
  // Last segment is the final position of the trajectory, but with a duration of 0.
  waypoint = joint_trajectory_.youngest();
  next_waypoint = joint_trajectory_.youngest();
  JointSegment segment(waypoint, next_waypoint);
  segments_.push_back(segment);
}

void JointTrajectory::interpolate(const double& stamp, double& pos, double& vel, double& acc)
{
  // If we are before trajectory start time or after trajectory end time return position
  if (stamp < joint_trajectory_.oldest().stamp)
  {
    pos = joint_trajectory_.oldest().state[0];
    vel = 0.0;
    acc = 0.0;
    return;
  }
  else if (stamp > joint_trajectory_.youngest().stamp)
  {
    pos = joint_trajectory_.youngest().state[0];
    vel = 0.0;
    acc = 0.0;
    return;
  }

  // Find current segmet and interpolate
  ssize_t index = joint_trajectory_.lower_index(stamp);
  segments_[index].interpolate(stamp, pos, vel, acc);
}

const double JointTrajectory::endTime()
{
  return joint_trajectory_.youngest().stamp;
}

}  // namespace ur_controller
}  // namespace isaac