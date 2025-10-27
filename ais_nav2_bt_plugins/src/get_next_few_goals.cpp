#include "ais_nav2_bt_plugins/get_next_few_goals.hpp"

#include <string>
#include <vector>

#include "behaviortree_cpp_v3/bt_factory.h"
#include "rclcpp/rclcpp.hpp"

namespace nav2_behavior_tree
{

GetNextFewGoals::GetNextFewGoals(
  const std::string & name,
  const BT::NodeConfiguration & conf)
: BT::ActionNodeBase(name, conf)
{
}

void GetNextFewGoals::halt()
{
  BT::ActionNodeBase::halt();
}

BT::NodeStatus GetNextFewGoals::tick()
{
  setStatus(BT::NodeStatus::RUNNING);

  std::vector<geometry_msgs::msg::PoseStamped> input_goals;
  std::vector<geometry_msgs::msg::PoseStamped> output_goals;
  unsigned int num_goals = 0u;

  if (!getInput("input_goals", input_goals)) {
    RCLCPP_ERROR(rclcpp::get_logger("GetNextFewGoals"), "Failed to get 'input_goals'");
    return BT::NodeStatus::FAILURE;
  }

  if (!getInput("num_goals", num_goals)) {
    RCLCPP_ERROR(rclcpp::get_logger("GetNextFewGoals"), "Failed to get 'num_goals'");
    return BT::NodeStatus::FAILURE;
  }

  if (input_goals.empty()) {
    RCLCPP_WARN(rclcpp::get_logger("GetNextFewGoals"), "No goals received");
    return BT::NodeStatus::FAILURE;
  }

  for (unsigned int i = 0; i < num_goals && i < input_goals.size(); ++i) {
    output_goals.push_back(input_goals.at(i));
  }

  if (!setOutput("output_goals", output_goals)) {
    RCLCPP_ERROR(rclcpp::get_logger("GetNextFewGoals"), "Failed to set 'output_goals'");
    return BT::NodeStatus::FAILURE;
  }

  RCLCPP_INFO(rclcpp::get_logger("GetNextFewGoals"), "Provided %zu goals", output_goals.size());
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList GetNextFewGoals::providedPorts()
{
  return BT::PortsList({
    BT::InputPort<std::vector<geometry_msgs::msg::PoseStamped>>(
      "input_goals", "Goals available for selection"),
    BT::InputPort<unsigned int>(
      "num_goals", 1u, "Number of goals to provide"),
    BT::OutputPort<std::vector<geometry_msgs::msg::PoseStamped>>(
      "output_goals", "Selected subset of goals")
  });
}

BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<GetNextFewGoals>("GetNextFewGoals");
}

}  // namespace nav2_behavior_tree
