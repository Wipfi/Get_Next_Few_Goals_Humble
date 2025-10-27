# Get Next Few Goals Behavior Tree Plugin for ROS 2 Humble

This repository contains the `ais_nav2_bt_plugins` ROS 2 package, which provides a Nav2
Behavior Tree action node named `GetNextFewGoals`. The node selects the first N goals from a
provided list and makes them available to downstream tree nodes.

## Package Overview

- **Plugin library:** `libget_next_few_goals_bt.so`
- **Plugin XML:** `share/ais_nav2_bt_plugins/plugin.xml`
- **BT node registration:** `GetNextFewGoals`

## Building

Build the package within a ROS 2 workspace using `colcon`:

```bash
colcon build --packages-select ais_nav2_bt_plugins
```

## Usage

Add the plugin XML to the Nav2 Behavior Tree plugin search path (for example via the
`nav2_bt_navigator` `plugin_lib_names` parameter) and reference the node inside your tree:

```xml
<GetNextFewGoals input_goals="path_goals" num_goals="3" output_goals="next_goals"/>
```

Ensure that the blackboard entries for `input_goals` and `num_goals` are set before the node
executes. The node writes the selected subset to the `output_goals` port.
