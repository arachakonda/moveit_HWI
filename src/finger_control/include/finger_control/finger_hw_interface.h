#ifndef FINGER_HW_INTERFACE_H
#define FINGER_HW_INTERFACE_H

#include <ros_control_boilerplate/generic_hw_interface.h>
#include <finger_control/dynamixelCmd.h>
#include <finger_control/dynamixelTelemetry.h>

namespace finger_ns
{
/** \brief Hardware interface for a robot */
class fingerHWInterface : public ros_control_boilerplate::GenericHWInterface
{
public:
  /**
   * \brief Constructor
   * \param nh - Node handle for topics.
   */
  fingerHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model = NULL);

  /** \brief Initialize the robot hardware interface */
  virtual void init();

  /** \brief Read the state from the robot hardware. */
  virtual void read(ros::Duration& elapsed_time);

  /** \brief Write the command to the robot hardware. */
  virtual void write(ros::Duration& elapsed_time);

  /** \breif Enforce limits for all values before writing */
  virtual void enforceLimits(ros::Duration& period);

protected:
    //define the subscriber and publisher
  ros::Subscriber telemetry_sub;
  void telemetryCallback(const finger_control::dynamixelTelemetry::ConstPtr& msg);

  ros::Publisher cmd_pub;



};  // class

}  // namespace ros_control_boilerplate

#endif
