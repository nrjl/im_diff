# im_diff
ROS sequential image differencer
Simple and stupid...

## Make workspace:
```
cd im_diff
catkin init
catkin build
```

To run:
```
source devel/setup.bash
rosrun im_diff im_diff
```
Expects input image transport stream on /camera/image_raw, outputs to /camera/im_diff
