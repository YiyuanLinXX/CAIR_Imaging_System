// Generated by gencpp from file phenobot_camera/AddTwoInts.msg
// DO NOT EDIT!


#ifndef PHENOBOT_CAMERA_MESSAGE_ADDTWOINTS_H
#define PHENOBOT_CAMERA_MESSAGE_ADDTWOINTS_H

#include <ros/service_traits.h>


#include <phenobot_camera/AddTwoIntsRequest.h>
#include <phenobot_camera/AddTwoIntsResponse.h>


namespace phenobot_camera
{

struct AddTwoInts
{

typedef AddTwoIntsRequest Request;
typedef AddTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct AddTwoInts
} // namespace phenobot_camera


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::phenobot_camera::AddTwoInts > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::phenobot_camera::AddTwoInts&) { return value(); }
};

template<>
struct DataType< ::phenobot_camera::AddTwoInts > {
  static const char* value()
  {
    return "phenobot_camera/AddTwoInts";
  }

  static const char* value(const ::phenobot_camera::AddTwoInts&) { return value(); }
};


// service_traits::MD5Sum< ::phenobot_camera::AddTwoIntsRequest> should match
// service_traits::MD5Sum< ::phenobot_camera::AddTwoInts >
template<>
struct MD5Sum< ::phenobot_camera::AddTwoIntsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::phenobot_camera::AddTwoInts >::value();
  }
  static const char* value(const ::phenobot_camera::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::phenobot_camera::AddTwoIntsRequest> should match
// service_traits::DataType< ::phenobot_camera::AddTwoInts >
template<>
struct DataType< ::phenobot_camera::AddTwoIntsRequest>
{
  static const char* value()
  {
    return DataType< ::phenobot_camera::AddTwoInts >::value();
  }
  static const char* value(const ::phenobot_camera::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::phenobot_camera::AddTwoIntsResponse> should match
// service_traits::MD5Sum< ::phenobot_camera::AddTwoInts >
template<>
struct MD5Sum< ::phenobot_camera::AddTwoIntsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::phenobot_camera::AddTwoInts >::value();
  }
  static const char* value(const ::phenobot_camera::AddTwoIntsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::phenobot_camera::AddTwoIntsResponse> should match
// service_traits::DataType< ::phenobot_camera::AddTwoInts >
template<>
struct DataType< ::phenobot_camera::AddTwoIntsResponse>
{
  static const char* value()
  {
    return DataType< ::phenobot_camera::AddTwoInts >::value();
  }
  static const char* value(const ::phenobot_camera::AddTwoIntsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // PHENOBOT_CAMERA_MESSAGE_ADDTWOINTS_H
