/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
// %Tag(INCLUDES)%
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <thebot.h>
#include <theball.h>
#include <theplayer.h>
// %EndTag(INCLUDES)%

// %Tag(INIT)%
int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(10);
  ros::Publisher marker_pub  = n.advertise<visualization_msgs::Marker>("vismarker1",100);
  ros::Publisher marker2_pub = n.advertise<visualization_msgs::Marker>("vismarker2",100);
  ros::Publisher marker3_pub = n.advertise<visualization_msgs::Marker>("vismarker3",100);
  ros::Publisher ball_pub    = n.advertise<visualization_msgs::Marker>("visball", 100); 
// %EndTag(INIT)%

  // Set our initial shape type to be a cube
// %Tag(SHAPE_INIT)%
  //uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%

// %Tag(MARKER_INIT)%

    int myxv=1;
    int myyv=1;
    int ballcounter=0;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/my_frame";
    marker.header.stamp = ros::Time::now();
    marker.ns = "basic_shapes";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    visualization_msgs::Marker marker2;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker2.header.frame_id = "/my_frame";
    marker2.header.stamp = ros::Time::now();
    marker2.ns = "basic_shapes";
    marker2.id = 1;
    marker2.type = visualization_msgs::Marker::CUBE;
    marker2.action = visualization_msgs::Marker::ADD;
    marker2.pose.position.x = 0;
    marker2.pose.position.y = 2;
    marker2.pose.position.z = 0;
    marker2.pose.orientation.x = 0.0;
    marker2.pose.orientation.y = 0.0;
    marker2.pose.orientation.z = 0.0;
    marker2.pose.orientation.w = 1.0;
    marker2.scale.x = 1.0;
    marker2.scale.y = 1.0;
    marker2.scale.z = 1.0;
    marker2.color.r = 0.0f;
    marker2.color.g = 1.0f;
    marker2.color.b = 0.0f;
    marker2.color.a = 1.0;
    marker2.lifetime = ros::Duration();

    visualization_msgs::Marker marker3;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker3.header.frame_id = "/my_frame";
    marker3.header.stamp = ros::Time::now();
    marker3.ns = "basic_shapes";
    marker3.id = 2;
    marker3.type = visualization_msgs::Marker::CUBE;
    marker3.action = visualization_msgs::Marker::ADD;
    marker3.pose.position.x = 0;
    marker3.pose.position.y = -2;
    marker3.pose.position.z = 0;
    marker3.pose.orientation.x = 0.0;
    marker3.pose.orientation.y = 0.0;
    marker3.pose.orientation.z = 0.0;
    marker3.pose.orientation.w = 1.0;
    marker3.scale.x = 1.0;
    marker3.scale.y = 1.0;
    marker3.scale.z = 1.0;
    marker3.color.r = 0.0f;
    marker3.color.g = 0.0f;
    marker3.color.b = 1.0f;
    marker3.color.a = 1.0;
    marker3.lifetime = ros::Duration();

    visualization_msgs::Marker ballmarker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    ballmarker.header.frame_id = "/my_frame";
    ballmarker.header.stamp = ros::Time::now();
    ballmarker.ns = "basic_shapes";
    ballmarker.id = 3;
    ballmarker.type = visualization_msgs::Marker::SPHERE;
    ballmarker.action = visualization_msgs::Marker::ADD;
    ballmarker.pose.position.x = 0;
    ballmarker.pose.position.y = -2;
    ballmarker.pose.position.z = 0;
    ballmarker.pose.orientation.x = 0.0;
    ballmarker.pose.orientation.y = 0.0;
    ballmarker.pose.orientation.z = 0.0;
    ballmarker.pose.orientation.w = 1.0;
    ballmarker.scale.x = 1.0;
    ballmarker.scale.y = 1.0;
    ballmarker.scale.z = 1.0;
    ballmarker.color.r = 0.5f;
    ballmarker.color.g = 0.5f;
    ballmarker.color.b = 0.0f;
    ballmarker.color.a = 1.0;
    ballmarker.lifetime = ros::Duration();
  
    ourposition position1 = {5,2,0};
    ourposition position2 = {-10,-10,0};
    ourposition position3 = {5,-2,0};
    thebot mybot1(&position1);
    thebot mybot2(&position2);
    thebot mybot3(&position3);

    theplayer player1(&position1);
    theplayer player2(&position2);
    theplayer player3(&position3);
    theball myball(0,0);

  while (ros::ok())
  {
    
// %EndTag(MARKER_INIT)%

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
// %Tag(NS_ID)%

// %EndTag(NS_ID)%

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
// %Tag(TYPE)%

// %EndTag(TYPE)%

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
// %Tag(ACTION)%

// %EndTag(ACTION)%

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
// %Tag(POSE)%

// %EndTag(POSE)%

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
// %Tag(SCALE)%

// %EndTag(SCALE)%

    // Set the color -- be sure to set alpha to something non-zero!
// %Tag(COLOR)%

// %EndTag(COLOR)%

// %Tag(LIFETIME)%

// %EndTag(LIFETIME)%

    // Publish the marker
// %Tag(PUBLISH)%
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    //marker.pose.position.x +=myxv;
    //marker2.pose.position.x -= myxv;

    marker.pose.position.x = mybot1.getX();
    marker.pose.position.y = mybot1.getY();
    marker.pose.orientation.x = mybot1.getX()-.5;
    marker.pose.orientation.y = mybot1.getY()-.5;
    marker.pose.orientation.z = 1;
    marker.pose.orientation.w = mybot1.getW();

    marker2.pose.position.x = mybot2.getX();
    marker2.pose.position.y = mybot2.getY();
    marker2.pose.orientation.x = mybot2.getX();
    marker2.pose.orientation.y = mybot2.getY();
    marker2.pose.orientation.z =1;
    marker2.pose.orientation.w = mybot2.getW();

    marker3.pose.position.x = mybot3.getX();
    marker3.pose.position.y = mybot3.getY();
    marker3.pose.orientation.x = mybot3.getX();
    marker3.pose.orientation.y = mybot3.getY();
    marker3.pose.orientation.z =1;
    marker3.pose.orientation.w = mybot3.getW();

    ballmarker.pose.position.x = myball.getX();
    ballmarker.pose.position.y = myball.getY();

    mybot1.docmd(player1.eval(mybot1.getPOS(), myball.getX(), myball.getY()));
    mybot2.docmd(player2.eval(mybot2.getPOS(), myball.getX(), myball.getY()));
    mybot3.docmd(player3.eval(mybot3.getPOS(), myball.getX(), myball.getY()));

    myball.eval();
    //if (ballcounter++ > 100) myball.kick(.02,.02);

    marker_pub.publish(marker);
    marker_pub.publish(marker2);
    marker_pub.publish(marker3);
    marker_pub.publish(ballmarker);

    

    r.sleep();
// %EndTag(PUBLISH)%

    // Cycle between different shapes
// %Tag(CYCLE_SHAPES)%
    //switch (shape)
    {
    //case visualization_msgs::Marker::CUBE:
      //shape = visualization_msgs::Marker::SPHERE;
      
	//break;
    //case visualization_msgs::Marker::SPHERE:
      //shape = visualization_msgs::Marker::ARROW;
//      break;
//    case visualization_msgs::Marker::ARROW:
//      shape = visualization_msgs::Marker::CYLINDER;
//      break;
//    case visualization_msgs::Marker::CYLINDER:
 //     shape = visualization_msgs::Marker::CUBE;
 //     break;
    }
// %EndTag(CYCLE_SHAPES)%

// %Tag(SLEEP_END)%

  }
// %EndTag(SLEEP_END)%
}
// %EndTag(FULLTEXT)%
