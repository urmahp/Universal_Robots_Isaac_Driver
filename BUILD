load("//bzl:module.bzl", "isaac_cc_module")

filegroup(
    name = "universal_robots_resources",
    data = [
        "ur_robot_driver/resources/ros_control.urscript",
        "ur_robot_driver/resources/rtde_input_recipe.txt",
        "ur_robot_driver/resources/rtde_output_recipe.txt",
    ],
    visibility = ["//visibility:public"],
)

isaac_cc_module(
    name = "universal_robots",
    srcs = [
        "ur_robot_driver/UniversalRobots.cpp",
        "ur_robot_driver/DashboardClientIsaac.cpp",
        "ur_robot_driver/UrclLogHandler.cpp",
        "ur_client_library/src/log.cpp",
        "ur_client_library/src/default_log_handler.cpp",
        "ur_client_library/src/comm/server.cpp",
        "ur_client_library/src/comm/tcp_socket.cpp",
        "ur_client_library/src/primary/primary_package.cpp",
        "ur_client_library/src/primary/robot_message.cpp",
        "ur_client_library/src/primary/robot_state.cpp",
        "ur_client_library/src/primary/robot_message/version_message.cpp",
        "ur_client_library/src/primary/robot_state/kinematics_info.cpp",
        "ur_client_library/src/rtde/control_package_pause.cpp",
        "ur_client_library/src/rtde/control_package_setup_inputs.cpp",
        "ur_client_library/src/rtde/control_package_setup_outputs.cpp",
        "ur_client_library/src/rtde/control_package_start.cpp",
        "ur_client_library/src/rtde/data_package.cpp",
        "ur_client_library/src/rtde/get_urcontrol_version.cpp",
        "ur_client_library/src/rtde/request_protocol_version.cpp",
        "ur_client_library/src/rtde/rtde_client.cpp",
        "ur_client_library/src/rtde/rtde_package.cpp",
        "ur_client_library/src/rtde/rtde_writer.cpp",
        "ur_client_library/src/rtde/text_message.cpp",
        "ur_client_library/src/ur/calibration_checker.cpp",
        "ur_client_library/src/ur/dashboard_client.cpp",
        "ur_client_library/src/ur/tool_communication.cpp",
        "ur_client_library/src/ur/ur_driver.cpp",
    ],
    hdrs = [
        "ur_robot_driver/UniversalRobots.hpp",
        "ur_robot_driver/DashboardClientIsaac.hpp",
        "ur_robot_driver/UrclLogHandler.hpp",
        "ur_client_library/include/ur_client_library/comm/bin_parser.h",
        "ur_client_library/include/ur_client_library/comm/package.h",
        "ur_client_library/include/ur_client_library/comm/package_serializer.h",
        "ur_client_library/include/ur_client_library/comm/parser.h",
        "ur_client_library/include/ur_client_library/comm/pipeline.h",
        "ur_client_library/include/ur_client_library/comm/producer.h",
        "ur_client_library/include/ur_client_library/comm/reverse_interface.h",
        "ur_client_library/include/ur_client_library/comm/script_sender.h",
        "ur_client_library/include/ur_client_library/comm/server.h",
        "ur_client_library/include/ur_client_library/comm/shell_consumer.h",
        "ur_client_library/include/ur_client_library/comm/stream.h",
        "ur_client_library/include/ur_client_library/comm/tcp_socket.h",
        "ur_client_library/include/ur_client_library/exceptions.h",
        "ur_client_library/include/ur_client_library/log.h",
        "ur_client_library/include/ur_client_library/default_log_handler.h",
        "ur_client_library/include/ur_client_library/primary/abstract_primary_consumer.h",
        "ur_client_library/include/ur_client_library/primary/package_header.h",
        "ur_client_library/include/ur_client_library/primary/primary_package.h",
        "ur_client_library/include/ur_client_library/primary/primary_parser.h",
        "ur_client_library/include/ur_client_library/primary/robot_message.h",
        "ur_client_library/include/ur_client_library/primary/robot_message/version_message.h",
        "ur_client_library/include/ur_client_library/primary/robot_state.h",
        "ur_client_library/include/ur_client_library/primary/robot_state/kinematics_info.h",
        "ur_client_library/include/ur_client_library/queue/atomicops.h",
        "ur_client_library/include/ur_client_library/queue/readerwriterqueue.h",
        "ur_client_library/include/ur_client_library/rtde/control_package_pause.h",
        "ur_client_library/include/ur_client_library/rtde/control_package_setup_inputs.h",
        "ur_client_library/include/ur_client_library/rtde/control_package_setup_outputs.h",
        "ur_client_library/include/ur_client_library/rtde/control_package_start.h",
        "ur_client_library/include/ur_client_library/rtde/data_package.h",
        "ur_client_library/include/ur_client_library/rtde/get_urcontrol_version.h",
        "ur_client_library/include/ur_client_library/rtde/package_header.h",
        "ur_client_library/include/ur_client_library/rtde/request_protocol_version.h",
        "ur_client_library/include/ur_client_library/rtde/rtde_client.h",
        "ur_client_library/include/ur_client_library/rtde/rtde_package.h",
        "ur_client_library/include/ur_client_library/rtde/rtde_parser.h",
        "ur_client_library/include/ur_client_library/rtde/rtde_writer.h",
        "ur_client_library/include/ur_client_library/rtde/text_message.h",
        "ur_client_library/include/ur_client_library/types.h",
        "ur_client_library/include/ur_client_library/ur/calibration_checker.h",
        "ur_client_library/include/ur_client_library/ur/dashboard_client.h",
        "ur_client_library/include/ur_client_library/ur/datatypes.h",
        "ur_client_library/include/ur_client_library/ur/tool_communication.h",
        "ur_client_library/include/ur_client_library/ur/ur_driver.h",
        "ur_client_library/include/ur_client_library/ur/version_information.h",
    ],
    copts = ["-Ipackages/universal_robots/ur_client_library/include"],
    data = ["//packages/universal_robots:universal_robots_resources"],
    defines = ["ISAAC_BUILD"],
    visibility = ["//visibility:public"],
    deps = [
        "//packages/math/gems/kinematic_tree",
        "//packages/composite/gems:parser",
        "//packages/map:kinematic_tree",
        "@boost//:variant",
        "//packages/universal_robots/ur_msg:speed_slider_proto",
        "//packages/universal_robots/ur_msg:dashboard_command_proto",
        "//packages/universal_robots/ur_msg:dashboard_command",
        "//packages/universal_robots/controller_stopper:controller_stopper",
        "//packages/composite/gems:serializer",
    ],
)