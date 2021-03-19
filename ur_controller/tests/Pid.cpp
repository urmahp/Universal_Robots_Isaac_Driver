#include "packages/universal_robots/ur_controller/Pid.hpp"
#include "gtest/gtest.h"

namespace isaac
{
namespace ur_controller
{
TEST(Pid, BadDurationTest)
{
  Pid<double> pid;
  pid.initPid(1.0, 0.0, 0.0, 1.0, -1.0);

  // When duration time is zero or less than zero we expect the output to be zero.
  EXPECT_EQ(pid.calculate(1.0, 0.0), 0.0);
  EXPECT_EQ(pid.calculate(1.0, -1.0), 0.0);
  EXPECT_EQ(pid.calculate(1.0, 1.0, -1.0), 0.0);
  EXPECT_EQ(pid.calculate(1.0, 1.0, 0.0), 0.0);
}

TEST(Pid, ResetErrorsTest)
{
  Pid<double> pid;
  pid.initPid(1.0, 0.1, 0.1, 1.0, -1.0);
  pid.calculate(1, 0.1, 0.1);

  double last_error, i_error;
  pid.reset();
  pid.getErrors(last_error, i_error);

  EXPECT_EQ(last_error, 0);
  EXPECT_EQ(i_error, 0);
}

TEST(Pid, InitTest)
{
  Pid<double> pid;
  // Empty JSON object
  nlohmann::json json = { { "gains", {} } };

  // Init should return false, when there is no propertional gain
  EXPECT_FALSE(pid.init(json));

  double p_gain = 5.0;
  double i_gain = 0.1;
  double d_gain = 0.01;
  double i_clamp = 1;

  // JSON
  json = { { "p", p_gain }, { "i", i_gain }, { "d", d_gain }, { "i_clamp", i_clamp } };

  // Init should now return true
  EXPECT_TRUE(pid.init(json));

  double p_return, i_return, d_return, i_max_return, i_min_return;
  pid.getGains(p_return, i_return, d_return, i_max_return, i_min_return);

  EXPECT_EQ(p_gain, p_return);
  EXPECT_EQ(i_gain, i_return);
  EXPECT_EQ(d_gain, d_return);
  EXPECT_EQ(std::abs(i_clamp), i_max_return);
  EXPECT_EQ(-std::abs(i_clamp), i_min_return);
}

TEST(Pid, PGainTest)
{
  Pid<double> pid;
  pid.initPid(1.0, 0.0, 0.0, 0.0, 0.0);

  double cmd = pid.calculate(-0.6, 1);
  EXPECT_FLOAT_EQ(cmd, -0.6);

  cmd = pid.calculate(-0.2, 1);
  EXPECT_FLOAT_EQ(cmd, -0.2);

  cmd = pid.calculate(0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.2);

  cmd = pid.calculate(0.8, 1);
  EXPECT_FLOAT_EQ(cmd, 0.8);

  cmd = pid.calculate(0.0, 1);
  EXPECT_FLOAT_EQ(cmd, 0.0);
}

TEST(Pid, IGainTest)
{
  Pid<double> pid;
  pid.initPid(0.0, 1.0, 0.0, 10.0, -10.0);

  double cmd = pid.calculate(-0.6, 1);
  EXPECT_FLOAT_EQ(cmd, -0.6);

  cmd = pid.calculate(-0.2, 1);
  EXPECT_FLOAT_EQ(cmd, -0.8);

  cmd = pid.calculate(0.0, 1);
  EXPECT_FLOAT_EQ(cmd, -0.8);

  pid.reset();

  cmd = pid.calculate(0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.2);

  cmd = pid.calculate(0.8, 1);
  EXPECT_FLOAT_EQ(cmd, 1.0);

  cmd = pid.calculate(0.0, 1);
  EXPECT_FLOAT_EQ(cmd, 1.0);
}

TEST(Pid, DGainTest)
{
  Pid<double> pid;
  pid.initPid(0.0, 0.0, 1.0, 0.0, 0.0);

  double cmd = pid.calculate(-0.6, 1);
  EXPECT_FLOAT_EQ(cmd, -0.6);

  cmd = pid.calculate(-0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.4);

  cmd = pid.calculate(-0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.0);

  pid.reset();

  cmd = pid.calculate(0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.2);

  cmd = pid.calculate(0.8, 1);
  EXPECT_FLOAT_EQ(cmd, 0.6);

  cmd = pid.calculate(0.0, 1);
  EXPECT_FLOAT_EQ(cmd, -0.8);
}

TEST(Pid, CompleteGainTest)
{
  Pid<double> pid;
  pid.initPid(1.0, 1.0, 1.0, 10.0, -10.0);

  double cmd = pid.calculate(0.5, 1);
  EXPECT_FLOAT_EQ(cmd, 1.5);

  cmd = pid.calculate(0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.6);

  cmd = pid.calculate(0.0, 1);
  EXPECT_FLOAT_EQ(cmd, 0.5);

  cmd = pid.calculate(-0.2, 1);
  EXPECT_FLOAT_EQ(cmd, 0.1);

  cmd = pid.calculate(-0.5, 1);
  EXPECT_FLOAT_EQ(cmd, -0.8);
}

}  // namespace ur_controller
}  // namespace isaac
