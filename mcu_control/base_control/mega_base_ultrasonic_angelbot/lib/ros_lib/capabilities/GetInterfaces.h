#ifndef _ROS_SERVICE_GetInterfaces_h
#define _ROS_SERVICE_GetInterfaces_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char GETINTERFACES[] = "capabilities/GetInterfaces";

  class GetInterfacesRequest : public ros::Msg
  {
    public:

    GetInterfacesRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETINTERFACES; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetInterfacesResponse : public ros::Msg
  {
    public:
      uint8_t interfaces_length;
      char* st_interfaces;
      char* * interfaces;

    GetInterfacesResponse():
      interfaces_length(0), interfaces(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = interfaces_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < interfaces_length; i++){
      uint32_t length_interfacesi = strlen(this->interfaces[i]);
      memcpy(outbuffer + offset, &length_interfacesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->interfaces[i], length_interfacesi);
      offset += length_interfacesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t interfaces_lengthT = *(inbuffer + offset++);
      if(interfaces_lengthT > interfaces_length)
        this->interfaces = (char**)realloc(this->interfaces, interfaces_lengthT * sizeof(char*));
      offset += 3;
      interfaces_length = interfaces_lengthT;
      for( uint8_t i = 0; i < interfaces_length; i++){
      uint32_t length_st_interfaces;
      memcpy(&length_st_interfaces, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_interfaces; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_interfaces-1]=0;
      this->st_interfaces = (char *)(inbuffer + offset-1);
      offset += length_st_interfaces;
        memcpy( &(this->interfaces[i]), &(this->st_interfaces), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return GETINTERFACES; };
    const char * getMD5(){ return "1e08367cf1ecdb90202f4711ad4955a7"; };

  };

  class GetInterfaces {
    public:
    typedef GetInterfacesRequest Request;
    typedef GetInterfacesResponse Response;
  };

}
#endif
