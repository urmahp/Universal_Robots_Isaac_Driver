#include "JointSegment.hpp"
#include "engine/core/math/types.hpp"

namespace isaac
{
namespace ur_controller
{
namespace
{
constexpr int linearInterpolation = 1;
constexpr int cubicInterpolation = 2;
constexpr int quinticInterpolation = 3;
}  // namespace

JointSegment::JointSegment() : duration_(0.0), start_time_(0.0)
{
  coffiecients_ << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
}

JointSegment::JointSegment(const Timeseries<VectorXd, double>::Entry& start_waypoint,
                           const Timeseries<VectorXd, double>::Entry& end_waypoint)
{
  coffiecients_ << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
  initSegment(start_waypoint, end_waypoint);
}

void JointSegment::initSegment(const Timeseries<VectorXd, double>::Entry& start_waypoint,
                               const Timeseries<VectorXd, double>::Entry& end_waypoint)
{
  ASSERT(start_waypoint.stamp <= end_waypoint.stamp, "start_waypoint stamp shouldn't be larger than end_waypoint "
                                                     "stamp");
  ASSERT(start_waypoint.state.rows() >= linearInterpolation && end_waypoint.state.rows() >= linearInterpolation, "empty"
                                                                                                                 " stat"
                                                                                                                 "e");
  ASSERT(start_waypoint.state.rows() == end_waypoint.state.rows(), "start_waypoint and end_waypoint states size "
                                                                   "mismatch");

  // Set all coefficients to zero
  coffiecients_ << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;

  duration_ = end_waypoint.stamp - start_waypoint.stamp;
  start_time_ = start_waypoint.stamp;

  if (start_waypoint.state.rows() == linearInterpolation)
  {
    linearCoefficients(start_waypoint.state, end_waypoint.state, duration_);
  }
  else if (start_waypoint.state.rows() == cubicInterpolation)
  {
    cubicCoefficients(start_waypoint.state, end_waypoint.state, duration_);
  }
  else if (start_waypoint.state.rows() == quinticInterpolation)
  {
    quinticCoefficients(start_waypoint.state, end_waypoint.state, duration_);
  }
  else
  {
    PANIC("To many elements in the state vector");
  }
}

Vector6d JointSegment::getCoefficients()
{
  return coffiecients_;
}

const double JointSegment::getEndTime()
{
  return start_time_ + duration_;
}

const double JointSegment::getStartTime()
{
  return start_time_;
}

void JointSegment::interpolate(const double& stamp, double& pos, double& vel, double& acc)
{
  // We can only interpolate within the waypoints.
  ASSERT(start_time_ <= stamp && stamp <= start_time_ + duration_, "Time stamp is not within the boundaries.");

  const double x = stamp - start_time_;

  pos = ((((coffiecients_[5] * x + coffiecients_[4]) * x + coffiecients_[3]) * x + coffiecients_[2]) * x +
         coffiecients_[1]) * x + coffiecients_[0];
  vel = (((5.0 * coffiecients_[5] * x + 4.0 * coffiecients_[4]) * x + 3.0 * coffiecients_[3]) * x +
         2.0 * coffiecients_[2]) * x + coffiecients_[1];
  acc = ((20.0 * coffiecients_[5] * x + 12.0 * coffiecients_[4]) * x + 6.0 * coffiecients_[3]) * x +
        2.0 * coffiecients_[2];
}

void JointSegment::linearCoefficients(const VectorXd& start, const VectorXd& end, const double& x)
{
  if (x == 0.0)
  {
    coffiecients_[0] = start[0];
  }
  else
  {
    coffiecients_[0] = start[0];
    coffiecients_[1] = (end[0] - start[0]) / x;
  }
}

void JointSegment::cubicCoefficients(const VectorXd& start, const VectorXd& end, const double& x)
{
  if (x == 0.0)
  {
    coffiecients_[0] = start[0];
    coffiecients_[1] = start[1];
  }
  else
  {
    Vector4d powers;
    powers << 1.0, x, x * x, x * x * x;
    coffiecients_[0] = start[0];
    coffiecients_[1] = start[1];
    coffiecients_[2] = (3.0 * (-start[0] + end[0]) + (-2.0 * start[1] - end[1]) * powers[1]) / powers[2];
    coffiecients_[3] = (2.0 * (start[0] - end[0]) + (start[1] + end[1]) * powers[1]) / powers[3];
  }
}

void JointSegment::quinticCoefficients(const VectorXd& start, const VectorXd& end, const double& x)
{
  if (x == 0.0)
  {
    coffiecients_[0] = start[0];
    coffiecients_[1] = start[1];
    coffiecients_[2] = 0.5 * start[2];
  }
  else
  {
    Vector6d powers;
    powers << 1.0, x, x * x, x * x * x, x * x * x * x, x * x * x * x * x;
    coffiecients_[0] = start[0];
    coffiecients_[1] = start[1];
    coffiecients_[2] = 0.5 * start[2];
    coffiecients_[3] = (20.0 * (-start[0] + end[0]) + (-3.0 * start[2] + end[2]) * powers[2] +
                       (-12.0 * start[1] - 8.0 * end[1]) * powers[1]) / (2.0 * powers[3]);
    coffiecients_[4] = (30.0 * (start[0] - end[0]) + (3.0 * start[2] - 2.0 * end[2]) * powers[2] +
                       (16.0 * start[1] + 14.0 * end[1]) * powers[1]) / (2.0 * powers[4]);
    coffiecients_[5] = (12.0 * (-start[0] + end[0]) + (-start[2] + end[2]) * powers[2] + 6.0 *
                       (-start[1] - end[1]) * powers[1]) / (2.0 * powers[5]);
  }
}

}  // namespace ur_controller
}  // namespace isaac