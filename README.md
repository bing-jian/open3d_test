# open3d_test
A simple program to test linking Open3D and other libraries on different platforms.

## Open3D version tested 
1.10.0

## Current behavior (09/03/2020)
### macOS
Succeeded when USE_GFLAGS is on.
% ./camera_pose_trajectory --helpshort

camera_pose_trajectory: Warning: SetUsageMessage() never called


  Flags from /Users/bingjian-bj/mygit/open3d_test/camera_pose_trajectory.cpp:
  
    -trajectory (ascii file) type: string default: ""

### ubuntu
Failed when USE_GFLAGS is on.  Succeeded when USE_GFLAGS is off. 
