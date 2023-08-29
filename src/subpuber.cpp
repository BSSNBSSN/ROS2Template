#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "Socket heard: '%s'", msg.data.c_str());
    publisher_->publish(msg);
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
public:
  MinimalSubscriber()
  : Node("subpuber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 100, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    publisher_ = this->create_publisher<std_msgs::msg::String>("socket_topic", 1);
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
