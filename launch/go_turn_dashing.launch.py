from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    distance=LaunchConfiguration('distance', default=1.570796327)
    velocity=LaunchConfiguration('velocity', default=0.3)
    ctrl_freq=LaunchConfiguration('ctrl_freq', default=10.0)
    cmd_vel_topic=LaunchConfiguration('cmd_vel_topic', default='/cmd_vel')
    odom_topic=LaunchConfiguration('odom_topic', default='/odom')

    return LaunchDescription([
        DeclareLaunchArgument(
            'distance',
            default_value=distance,
            description='Angular distance that robot will move for (rad).'
        ),        
        DeclareLaunchArgument(
            'velocity',
            default_value=velocity,
            description='Angular velocity that robot will move with (rad/s).'
        ),        
        DeclareLaunchArgument(
            'ctrl_freq',
            default_value=ctrl_freq,
            description='The frequence of /cmd_vel topic is published(Hz).'
        ),        
        DeclareLaunchArgument(
            'cmd_vel_topic',
            default_value=cmd_vel_topic,
            description='The topic published to the robot mobile base (geometry_msgs/Twist).'
        ),        
        DeclareLaunchArgument(
            'odom_topic',
            default_value=odom_topic,
            description='The topic published from odom sensor (nav_msgs/Odometry).'
        ),
        Node(
            package='go_straight_and_turn',
            node_executable='go_turn_node',
            node_name='go_turn',
            output="screen",
            parameters=[
                {'ctrl_freq': ctrl_freq}
            ],
            arguments=[distance,velocity],
            remappings=[
                ('/cmd_vel',cmd_vel_topic),
                ('/odom',odom_topic)
            ]
        )
    ])
