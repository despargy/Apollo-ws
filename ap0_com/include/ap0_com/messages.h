#ifndef MESSAGES_H
#define MESSAGES_H

#include <string.h>
#include <ros/service_traits.h>
// #include <ros/serialization.h>
// #include <ros/builtin_message_traits.h>
// #include <ros/message_operations.h>
// #include <ros/types.h>

// #include <ap0_com/messagesRequest.h>
// #include <ap0_com/messagesResponse.h>

namespace ap0_com
{

  struct apollo_message
  {

    // bool move_to_next;
    int now;
    int next;
    char* msg;
    int request;
    int response;
    //
    // typedef apollo_messageRequest Request;
    // typedef apollo_messageResponse Response;
    // Request request;
    // Response response;
    //
    // typedef Request RequestType;
    // typedef Response ResponseType;

  };
}


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum<ap0_com::apollo_message > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ap0_com::apollo_message&) { return value(); }
};

template<>
struct DataType< ap0_com::apollo_message > {
  static const char* value()
  {
    return "ap0_com/apollo_message";
  }

  static const char* value(const ap0_com::apollo_message&) { return value(); }
};

//
// // service_traits::MD5Sum< ap0_com::apollo_message> should match
// // service_traits::MD5Sum< ap0_com::apollo_message >
// template<>
// struct MD5Sum< ap0_com::apollo_messageRequest>
// {
//   static const char* value()
//   {
//     return MD5Sum< ap0_com::apollo_message >::value();
//   }
//   static const char* value(const ap0_com::apollo_messageRequest&)
//   {
//     return value();
//   }
// };
//
// // service_traits::DataType< ap0_com::apollo_message> should match
// // service_traits::DataType< ap0_com::apollo_message >
// template<>
// struct DataType< ap0_com::apollo_messageRequest>
// {
//   static const char* value()
//   {
//     return DataType< ap0_com::apollo_message >::value();
//   }
//   static const char* value(const ap0_com::apollo_messageRequest&)
//   {
//     return value();
//   }
// };
//
// // service_traits::MD5Sum< ap0_com::apollo_message> should match
// // service_traits::MD5Sum< ap0_com::apollo_message >
// template<>
// struct MD5Sum< ap0_com::apollo_messageResponse>
// {
//   static const char* value()
//   {
//     return MD5Sum< ap0_com::apollo_message >::value();
//   }
//   static const char* value(const ap0_com::apollo_messageResponse&)
//   {
//     return value();
//   }
// };
//
// // service_traits::DataType< ap0_com::apollo_message> should match
// // service_traits::DataType< ap0_com::apollo_message >
// template<>
// struct DataType< ap0_com::apollo_messageResponse>
// {
//   static const char* value()
//   {
//     return DataType< ap0_com::apollo_message >::value();
//   }
//   static const char* value(const ap0_com::apollo_messageResponse&)
//   {
//     return value();
//   }
// };
//
} // namespace service_traits
} // namespace ros
//

#endif
