# CMake generated Testfile for 
# Source directory: /home/fyin/sim_env/src/navigation/map_server
# Build directory: /home/fyin/sim_env/build/navigation/map_server
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_map_server_gtest_map_server_utest "/home/fyin/sim_env/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/fyin/sim_env/build/test_results/map_server/gtest-map_server_utest.xml" "--return-code" "/home/fyin/sim_env/devel/lib/map_server/map_server_utest --gtest_output=xml:/home/fyin/sim_env/build/test_results/map_server/gtest-map_server_utest.xml")
add_test(_ctest_map_server_rostest_test_rtest.xml "/home/fyin/sim_env/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/fyin/sim_env/build/test_results/map_server/rostest-test_rtest.xml" "--return-code" "/usr/bin/python2 /opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/fyin/sim_env/src/navigation/map_server --package=map_server --results-filename test_rtest.xml --results-base-dir \"/home/fyin/sim_env/build/test_results\" /home/fyin/sim_env/src/navigation/map_server/test/rtest.xml ")
