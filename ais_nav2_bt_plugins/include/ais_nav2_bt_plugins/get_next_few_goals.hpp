#ifndef AIS_NAV2_BT_PLUGINS__GET_NEXT_FEW_GOALS_HPP_
#define AIS_NAV2_BT_PLUGINS__GET_NEXT_FEW_GOALS_HPP_

#include <string>
#include <vector>

#include "behaviortree_cpp_v3/action_node.h"
#include "geometry_msgs/msg/pose_stamped.hpp"

namespace nav2_behavior_tree
{

class GetNextFewGoals : public BT::ActionNodeBase
{
public:
  GetNextFewGoals(const std::string & name, const BT::NodeConfiguration & conf);

  BT::NodeStatus tick() override;

  void halt() override;

  static BT::PortsList providedPorts();
};

}  // namespace nav2_behavior_tree

#endif  // AIS_NAV2_BT_PLUGINS__GET_NEXT_FEW_GOALS_HPP_
