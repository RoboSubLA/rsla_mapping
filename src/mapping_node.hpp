#ifndef MAPPING_NODE_HPP
#define MAPPING_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MappingNode : public rclcpp::Node
{
  public:
    MappingNode();
    ~MappingNode();

  private:
    void timer_callback();
    void topic_callback(const std_msgs::msg::String &msg) const;
    
    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

    size_t count_;
};

#endif