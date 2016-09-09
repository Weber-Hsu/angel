#ifndef _ROS_play_motion_msgs_PlayMotionAction_h
#define _ROS_play_motion_msgs_PlayMotionAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "play_motion_msgs/PlayMotionActionGoal.h"
#include "play_motion_msgs/PlayMotionActionResult.h"
#include "play_motion_msgs/PlayMotionActionFeedback.h"

namespace play_motion_msgs
{

  class PlayMotionAction : public ros::Msg
  {
    public:
      play_motion_msgs::PlayMotionActionGoal action_goal;
      play_motion_msgs::PlayMotionActionResult action_result;
      play_motion_msgs::PlayMotionActionFeedback action_feedback;

    PlayMotionAction():
      action_goal(),
      action_result(),
      action_feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "play_motion_msgs/PlayMotionAction"; };
    const char * getMD5(){ return "b18530db1ae596c4c0ca2ede0819fc9e"; };

  };

}
#endif