-- THUNDER T01演示定位用的配置
-- 需要将资源降到最低

include "thunder_map_builder_fast.lua"
include "thunder_trajectory_builder_fast.lua"

options = {

  map_builder = MAP_BUILDER,
  trajectory_builder = TRAJECTORY_BUILDER,

  num_subdivisions_per_laser_scan = 1,                   -- Crucial: scan data batch size

  -- Keep to default adjust
  num_laser_scans = 1,
  num_multi_echo_laser_scans = 0,
  num_point_clouds = 0,

  use_pose_extrapolator = false,                         -- Inference pose from imu
  use_odometry = false,                                  -- Inference pose from odom, T01 odom有跳变 不能用
  use_nav_sat = false,
  use_landmarks = false,

  map_frame = "map",
  tracking_frame = "base_footprint",                          -- TODO: (DEBUG) -- base_link
  published_frame = "base_footprint",
  odom_frame = "odom",

  publish_frame_projected_to_2d = false,                 -- TODO:
  provide_odom_frame = false,                            -- TODO: default: true

  submap_publish_period_sec = 0.3,
  pose_publish_period_sec = 5e-3,
  trajectory_publish_period_sec = 30e-3,
  lookup_transform_timeout_sec = 0.2,                    -- TODO: Meaning

  rangefinder_sampling_ratio = 1.,
  odometry_sampling_ratio = 1.,
  fixed_frame_pose_sampling_ratio = 1.,
  imu_sampling_ratio = 1.,
  landmarks_sampling_ratio = 1.,

}

MAP_BUILDER.use_trajectory_builder_2d = true
-- POSE_GRAPH.optimization_problem.fixed_frame_pose_translation_weight=1e6
-- POSE_GRAPH.optimization_problem.fixed_frame_pose_rotation_weight=1e5
TRAJECTORY_BUILDER_2D.num_accumulated_range_data = 1
TRAJECTORY_BUILDER_2D.max_range = 20
TRAJECTORY_BUILDER_2D.voxel_filter_size = 0.01
TRAJECTORY_BUILDER_2D.adaptive_voxel_filter.min_num_points = 200
TRAJECTORY_BUILDER_2D.loop_closure_adaptive_voxel_filter.min_num_points = 100
TRAJECTORY_BUILDER_2D.use_online_correlative_scan_matching = false
TRAJECTORY_BUILDER_2D.submaps.range_data_inserter.probability_grid_range_data_inserter.hit_probability = 0.70

return options
