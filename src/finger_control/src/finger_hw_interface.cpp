
#include <finger_control/finger_hw_interface.h>


namespace finger_ns
{
fingerHWInterface::fingerHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model)
  : ros_control_boilerplate::GenericHWInterface(nh, urdf_model)
{
    // Initialize ROS interfaces
  telemetry_sub = nh.subscribe("/finger_ops/dynamixelTelemetry", 1, &fingerHWInterface::telemetryCallback, this);

  cmd_pub=nh.advertise<finger_control::dynamixelCmd>("/finger_ops/dynamixelCmd", 1);

  ROS_INFO("fingerHWInterface Constructed.");

}

void fingerHWInterface::telemetryCallback(const finger_control::dynamixelTelemetry::ConstPtr& msg){

//   float32 pulses
// float32 velocity
// float32 current
// time startSyncTime
// uint32 isrTicks
// uint8 bufferHealth

// // States
// std::vector<double> joint_position_;
// std::vector<double> joint_velocity_;
// std::vector<double> joint_effort_;



  for(int i=0; i<num_joints_; i++){
    joint_position_[i]=msg->angle[i];
    joint_velocity_[i]=msg->velocity[i];
  }

}

void fingerHWInterface::init()
{
  // Call parent class version of this function
  GenericHWInterface::init();

  ROS_INFO("fingerHWInterface Ready.");
}

void fingerHWInterface::read(ros::Duration& elapsed_time)
{
  // No need to read since our write() command populates our state for us
  // ros::spinOnce();
}

void fingerHWInterface::write(ros::Duration& elapsed_time)
{
  // Safety
  //enforceLimits(elapsed_time);

  // NOTE: the following is a "simuation" example so that this boilerplate can be run without being
  // connected to hardware
  // When converting to your robot, remove the built-in PID loop and instead let the higher leverl
  // ros_control controllers take
  // care of PID loops for you. This P-controller is only intended to mimic the delay in real
  // hardware, somewhat like a simualator
  static finger_control::dynamixelCmd dyn_cmd;
  // these are nothing but the trajectories of position and velocity given by the controller
  for(int i=0; i<num_joints_; i++){
    dyn_cmd.angle[i]=joint_position_command_[i];
    dyn_cmd.velocity[i]=joint_velocity_command_[i];
    // dyn_cmd.current[i]=joint_effort_command_[i];
  }
  cmd_pub.publish(dyn_cmd);


}

void fingerHWInterface::enforceLimits(ros::Duration& period)
{
  // Enforces position and velocity
  // pos_jnt_sat_interface_.enforceLimits(period);
}



}  // namespace finger_ns
