/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/umkc/umkc_robot_2014_arduino/wesley/ros/src/wesley/msg/arm_angle.msg
 *
 */


#ifndef WESLEY_MESSAGE_ARM_ANGLE_H
#define WESLEY_MESSAGE_ARM_ANGLE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace wesley
{
template <class ContainerAllocator>
struct arm_angle_
{
  typedef arm_angle_<ContainerAllocator> Type;

  arm_angle_()
    : base(0)
    , shoulder(0)
    , elbow(0)
    , wrist_pitch(0)
    , wrist_roll(0)
    , hand(0)  {
    }
  arm_angle_(const ContainerAllocator& _alloc)
    : base(0)
    , shoulder(0)
    , elbow(0)
    , wrist_pitch(0)
    , wrist_roll(0)
    , hand(0)  {
    }



   typedef uint16_t _base_type;
  _base_type base;

   typedef uint16_t _shoulder_type;
  _shoulder_type shoulder;

   typedef uint16_t _elbow_type;
  _elbow_type elbow;

   typedef uint16_t _wrist_pitch_type;
  _wrist_pitch_type wrist_pitch;

   typedef uint16_t _wrist_roll_type;
  _wrist_roll_type wrist_roll;

   typedef uint16_t _hand_type;
  _hand_type hand;




  typedef boost::shared_ptr< ::wesley::arm_angle_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::wesley::arm_angle_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct arm_angle_

typedef ::wesley::arm_angle_<std::allocator<void> > arm_angle;

typedef boost::shared_ptr< ::wesley::arm_angle > arm_anglePtr;
typedef boost::shared_ptr< ::wesley::arm_angle const> arm_angleConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::wesley::arm_angle_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::wesley::arm_angle_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace wesley

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'wesley': ['/home/umkc/umkc_robot_2014_arduino/wesley/ros/src/wesley/msg'], 'std_msgs': ['/opt/ros/hydro/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::wesley::arm_angle_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::wesley::arm_angle_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::wesley::arm_angle_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::wesley::arm_angle_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::wesley::arm_angle_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::wesley::arm_angle_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::wesley::arm_angle_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ef33d4984a305fd75dffb44db14b17ea";
  }

  static const char* value(const ::wesley::arm_angle_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xef33d4984a305fd7ULL;
  static const uint64_t static_value2 = 0x5dffb44db14b17eaULL;
};

template<class ContainerAllocator>
struct DataType< ::wesley::arm_angle_<ContainerAllocator> >
{
  static const char* value()
  {
    return "wesley/arm_angle";
  }

  static const char* value(const ::wesley::arm_angle_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::wesley::arm_angle_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# wesley::arm_angle\n\
\n\
uint16 base\n\
uint16 shoulder\n\
uint16 elbow\n\
uint16 wrist_pitch\n\
uint16 wrist_roll\n\
uint16 hand\n\
\n\
";
  }

  static const char* value(const ::wesley::arm_angle_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::wesley::arm_angle_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.base);
      stream.next(m.shoulder);
      stream.next(m.elbow);
      stream.next(m.wrist_pitch);
      stream.next(m.wrist_roll);
      stream.next(m.hand);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct arm_angle_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::wesley::arm_angle_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::wesley::arm_angle_<ContainerAllocator>& v)
  {
    s << indent << "base: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.base);
    s << indent << "shoulder: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.shoulder);
    s << indent << "elbow: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.elbow);
    s << indent << "wrist_pitch: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.wrist_pitch);
    s << indent << "wrist_roll: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.wrist_roll);
    s << indent << "hand: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.hand);
  }
};

} // namespace message_operations
} // namespace ros

#endif // WESLEY_MESSAGE_ARM_ANGLE_H
