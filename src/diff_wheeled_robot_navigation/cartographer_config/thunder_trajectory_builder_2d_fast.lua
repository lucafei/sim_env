-- Copyright 2016 The Cartographer Authors
--
-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at
--
--      http://www.apache.org/licenses/LICENSE-2.0
--
-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

TRAJECTORY_BUILDER_2D = {
  -- Currently we dont have imu data [Mario]
  use_imu_data = false,

  min_range = 1,
  max_range = 50., -- [Costly]
  min_z = -2,
  max_z = 2.,
  missing_data_ray_length = 5.,

  num_accumulated_range_data = 1,                                   -- Also Defined in ros/backpack_2d
  voxel_filter_size = 0.005,                                        -- Smaller, more calculation [Costly]

  adaptive_voxel_filter = {
    max_length = 0.5,
    min_num_points = 400, -- How many points are used [Costly] Velodyne have around 897 points
    max_range = 50.,
  },

  loop_closure_adaptive_voxel_filter = {
    max_length = 0.9,
    min_num_points = 400, -- [Costly]
    max_range = 50.,
  },

  use_online_correlative_scan_matching = true, -- defulat false

  real_time_correlative_scan_matcher = {
    linear_search_window = 0.2, --0.1 Costly
    angular_search_window = math.rad(30.), --30
    translation_delta_cost_weight = 1e-1,
    rotation_delta_cost_weight = 5e-1, -- 5 tend to be a good choice default: 1e-1
  },

  ceres_scan_matcher = {
    occupied_space_weight = 100.,
    translation_weight = 10.,
    rotation_weight = 40., --40
    ceres_solver_options = {
      use_nonmonotonic_steps = false, -- false
      max_num_iterations = 20,
      num_threads = 4,
    },
  },

  motion_filter = {
    max_time_seconds = 1, -- 5
    max_distance_meters = 0.05, -- 0.2
    max_angle_radians = math.rad(0.5), -- 1
  },

  -- TODO(schwoere,wohe): Remove this constant. This is only kept for ROS.
  imu_gravity_time_constant = 10.,
  pose_extrapolator = {
    use_imu_based = false,
    constant_velocity = {
      imu_gravity_time_constant = 10.,
      pose_queue_duration = 0.001,
    },
    imu_based = {
      pose_queue_duration = 5.,
      gravity_constant = 9.806,
      pose_translation_weight = 1.,
      pose_rotation_weight = 1.,
      imu_acceleration_weight = 1.,
      imu_rotation_weight = 1.,
      odometry_translation_weight = 1.,
      odometry_rotation_weight = 1.,
      solver_options = {
        use_nonmonotonic_steps = false;
        max_num_iterations = 10;
        num_threads = 1;
      },
    },
  },

  submaps = {
    num_range_data = 90, --90
    grid_options_2d = {
      grid_type = "PROBABILITY_GRID",
      -- grid_type = "TSDF",
      resolution = 0.10, --0.05
    },
    range_data_inserter = {
      range_data_inserter_type = "PROBABILITY_GRID_INSERTER_2D",
      probability_grid_range_data_inserter = {
        insert_free_space = true, -- true
        hit_probability = 0.85, --0.55
        miss_probability = 0.49, --0.49
      },
      tsdf_range_data_inserter = {
        truncation_distance = 0.3,
        maximum_weight = 10.,
        update_free_space = false,
        normal_estimation_options = {
          num_normal_samples = 4,
          sample_radius = 0.5,
        },
        project_sdf_distance_to_scan_normal = true,
        update_weight_range_exponent = 0,
        update_weight_angle_scan_normal_to_ray_kernel_bandwidth = 0.5,
        update_weight_distance_cell_to_hit_kernel_bandwidth = 0.5,
      },
    },
  },
}
