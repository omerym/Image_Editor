# CMakeList.txt : CMake project for Assignment, include source and define
# project specific logic here.
#

# Add source to this project's executable.
#add_executable (Assignment "CS213-2023-20220799-20220837-20220703-A1-FULL.cpp")
add_executable (Assignment "CS213-2023-S15-20220799-20220837-20220703-A1-Bonus.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Assignment PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
