#pragma once

#include <vector>

#include "engine/core/math/types.hpp"
#include "engine/gems/algorithm/timeseries.hpp"

namespace isaac
{
namespace ur_controller
{
/*!
 * \brief Calculates a segment between two waypoints. The segment is a function describing
 * joint position as a function of time. The function can be linear, cubic or quintic.
 */

class JointSegment
{
public:
  /*!
   * \brief Construct a new Joint Segment object
   */
  JointSegment();

  /*!
   * \brief Construct a new Joint Segment object with a start_waypoint and end_waypoint.
   * This constructor calls initSegment.
   *
   * Timeseries<VectorXd, double>::Entry is a struct describing a waypoint.
   * Struct Entry {
   *   double Stamp
   *   VectorXd state
   * };
   * An Entry consist of a timestamp and a state which is the current state at that timestamp.
   * State is vector with 1, 2 or 3 entries depending on wheter the vector consist of pos, vel and acc.
   * This function calls InitSegment.
   *
   * \param start_waypoint the first waypoint
   * \param end_waypoint the second waypoint
   */
  JointSegment(const Timeseries<VectorXd, double>::Entry& start_waypoint,
               const Timeseries<VectorXd, double>::Entry& end_waypoint);

  /*!
   * \brief Calculates the function between the two waypoints.
   *
   * If State has length 1 linear function will be calculated.
   * y = coffiecients_[1]*x + coffiecients_[0]
   * coffiecients_[2] = coffiecients_[3] = coffiecients_[4] = coffiecients_[5] = 0.
   *
   * If State has length 2 cubic function will be calculated.
   * y = coffiecients_[3]*x^3 + coffiecients_[2]*x^2 + coffiecients_[1]*x + coffiecients_[0]
   * coffiecients_[4] = coffiecients_[5] = 0.
   *
   * If State has length 3 quintic function will be calculated.
   * y = coffiecients_[5]*x^5 + coffiecients_[4]*x^4 + coffiecients_[3]*x^3 + coffiecients_[2]*x^2 + coffiecients_[1]*x
   * + coffiecients_[0]
   *
   * \param start_waypoint the first waypoint
   * \param end_waypoint the second waypoint
   */
  void initSegment(const Timeseries<VectorXd, double>::Entry& start_waypoint,
                   const Timeseries<VectorXd, double>::Entry& end_waypoint);

  /*!
   * \returns Segment coefficients
   */
  Vector6d getCoefficients();

  /*!
   * \returns End time of the segment
   */
  const double getEndTime();

  /*!
   * \returns Start time of the segment
   */
  const double getStartTime();

  /*!
   * \brief interpolate at a given time stamp.
   *
   * \param stamp Time stamp to do the interpolation, make sure it is within the boundaries.
   * \param pos Variable to store calculated position
   * \param vel Variable to store calculated velocity
   * \param acc Variable to store calculated acceleration
   */
  void interpolate(const double& stamp, double& pos, double& vel, double& acc);

private:
  /*!
   * \brief Calculates linear coefficients for the segment.
   *
   * \param start Start state
   * \param end End state
   * \param x duration of the segment
   */
  void linearCoefficients(const VectorXd& start, const VectorXd& end, const double& x);

  /*!
   * \brief Calculates cubic coefficients for the segment.
   *
   * \param start Start state
   * \param end End state
   * \param x duration of the segment
   */
  void cubicCoefficients(const VectorXd& start, const VectorXd& end, const double& x);

  /*!
   * \brief Calculates quintic coefficients for the segment.
   *
   * \param start Start state
   * \param end End state
   * \param x duration of the segment
   */
  void quinticCoefficients(const VectorXd& start, const VectorXd& end, const double& x);

  // Coefficients
  Vector6d coffiecients_;

  // Segment start time, end time and duration for a segment
  double duration_, start_time_;
};

}  // namespace ur_controller
}  // namespace isaac
