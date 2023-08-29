#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class Subpuber : public rclcpp::Node
{
private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
public:
  Subpuber()
  : Node("listener")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 1, std::bind(&Subpuber::topic_callback, this, _1));
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Subpuber>());
  rclcpp::shutdown();
  return 0;
}
