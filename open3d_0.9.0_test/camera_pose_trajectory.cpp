
#include <Open3D/Open3D.h>

#define USE_GFLAGS

#ifdef USE_GFLAGS
#include "gflags/gflags.h"

DEFINE_string(trajectory, "",  "ascii file");
#endif

int main(int argc, char *argv[]) {
  using namespace open3d;
#ifdef USE_GFLAGS
  ::gflags::ParseCommandLineFlags(&argc, &argv, true);
#endif
  utility::SetVerbosityLevel(utility::VerbosityLevel::VerboseAlways);

  camera::PinholeCameraTrajectory trajectory;
#ifdef USE_GFLAGS
  io::ReadPinholeCameraTrajectory(FLAGS_trajectory, trajectory);
#else
  io::ReadPinholeCameraTrajectory(argv[1], trajectory);
#endif
  return 0;
}
