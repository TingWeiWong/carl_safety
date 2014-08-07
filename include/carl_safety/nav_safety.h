/*!
 * \nav_safety.h
 * \brief Prevents CARL from (manually) driving past a linear boundary on the map.
 *
 * nav_safety creates a ROS node that prevents CARL from crossing a line on the map
 * during manual navigation.  The node also adds estop functionality that prevents
 * only online manual navigation commands.
 *
 * \author David Kent, WPI - davidkent@wpi.edu
 * \date August 6, 2014
 */

#ifndef NAV_SAFETY_H_
#define NAV_SAFETY_H_

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

//controller types
#define ANALOG 0 //analog triggers
#define DIGITAL 1 //digital triggers

//Boundary
#define BOUNDARY_X 4.4
#define PI 3.14159

/*!
 * \class navSafety
 * \brief Prevents CARL from (manually) driving past a linear boundary on the map.
 *
 * nav_safety creates a ROS node that prevents CARL from crossing a line on the map
 * during manual navigation.  The node also adds estop functionality that prevents
 * only online manual navigation commands.
 */
class navSafety
{
public:
  /**
   * \brief Constructor
   */
  navSafety();

  /**
   * \brief getter for stopped
   * @return true if safe nav commands should be stopped
   */
  bool isStopped();
  
  /**
   * \brief cancels all nav goals
   */
  void cancelNavGoals();

private:
  /**
   * \brief Joystick input callback.
   * @param joy joystick input data
   */
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  /**
   * \brief Callback for safe base velocity commands
   * @param msg velocity base command
   */
  void safeBaseCommandCallback(const geometry_msgs::Twist::ConstPtr& msg);
  
  /**
   * \brief Callback for robot base pose
   * @param msg pose message
   */
  void poseCallback(const geometry_msgs::Pose::ConstPtr& msg);

  ros::NodeHandle node; /*!< a handle for this ROS node */

  ros::Publisher baseCommandPublisher; /*!< actual base command publisher */
  ros::Subscriber safeBaseCommandSubscriber; /*!< subscriber for base commands coming from the web */
  ros::Subscriber joySubscriber; /*!< subscriber for joystick input */
  ros::Subscriber robotPoseSubscriber; /*!< subscriber for the robot base pose */
  
  int controllerType;
  bool stopped; /*!< true if safe nav commands should be stopped */
  float x;
  float y;
  float theta;
};

#endif
