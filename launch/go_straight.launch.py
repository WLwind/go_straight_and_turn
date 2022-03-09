from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    distance = LaunchConfiguration('distance', default = 0.1)
    velocity = LaunchConfiguration('velocity', default = 0.03)
    ctrl_freq = LaunchConfiguration('ctrl_freq', default=10.0)
    cmd_vel_topic = LaunchConfiguration('cmd_vel_topic', default = '/cmd_vel')
    odom_topic = LaunchConfiguration('odom_topic', default = '/odom')
    tolerance = LaunchConfiguration('tolerance', default = 0.005)

    return LaunchDescription([
        DeclareLaunchArgument(
            'distance',
            default_value = distance,
            description = 'Linear distance that robot will move for (m).'
        ),        
        DeclareLaunchArgument(
            'velocity',
            default_value = velocity,
            description = 'Linear velocity that robot will move with (m/s).'
        ),        
        DeclareLaunchArgument(
            'ctrl_freq',
            default_value = ctrl_freq,
            description = 'The frequence of /cmd_vel topic is published(Hz).'
        ),        
        DeclareLaunchArgument(
            'cmd_vel_topic',
            default_value = cmd_vel_topic,
            description = 'The topic published to the robot mobile base (geometry_msgs/Twist).'
        ),        
        DeclareLaunchArgument(
            'odom_topic',
            default_value = odom_topic,
            description = 'The topic published from odom sensor (nav_msgs/Odometry).'
        ),
        DeclareLaunchArgument(
            'tolerance',
            default_value = tolerance,
            description = 'The tolerance distance when achieving the goal.'
        ),
        Node(
            package = 'go_straight_and_turn',
            executable = 'go_straight_node',
            name = 'go_straight',
            output = "screen",
            parameters = [
                {'ctrl_freq': ctrl_freq},
                {'tolerance': tolerance}
            ],
            arguments = [distance,velocity],
            remappings = [
                ('/cmd_vel', cmd_vel_topic),
                ('/odom', odom_topic)
            ]
        )
    ])
