# open3d_test
A simple program to test linking Open3D and other libraries on different platforms.

## Open3D version tested 
1.10.0

## Current behavior (09/03/2020)
### macOS
Succeeded when USE_GFLAGS is on.

```
% ./camera_pose_trajectory --helpshort
camera_pose_trajectory: Warning: SetUsageMessage() never called

  Flags from /Users/bingjian-bj/mygit/open3d_test/camera_pose_trajectory.cpp:
    -trajectory (ascii file) type: string default: ""
```

### ubuntu
Failed when USE_GFLAGS is on.  Succeeded when USE_GFLAGS is off. 

```
MakeFiles/camera_pose_trajectory.dir/camera_pose_trajectory.cpp.o: In function `_GLOBAL__sub_I__ZN3fLS16FLAGS_trajectoryE':
camera_pose_trajectory.cpp:(.text.startup+0x150): undefined reference to `google::FlagRegisterer::FlagRegisterer<std::string>(char const*, char const*, char const*, std::string*, std::string*)'
collect2: error: ld returned 1 exit status
CMakeFiles/camera_pose_trajectory.dir/build.make:104: recipe for target 'camera_pose_trajectory' failed
make[2]: *** [camera_pose_trajectory] Error 1
CMakeFiles/Makefile2:72: recipe for target 'CMakeFiles/camera_pose_trajectory.dir/all' failed
make[1]: *** [CMakeFiles/camera_pose_trajectory.dir/all] Error 2
Makefile:83: recipe for target 'all' failed
make: *** [all] Error 2
```
