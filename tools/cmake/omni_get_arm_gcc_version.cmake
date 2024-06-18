function(check_arm_gcc_version required_version)
  # Execute arm-none-eabi-gcc to get the version info
  execute_process(COMMAND arm-none-eabi-gcc --version OUTPUT_VARIABLE GCC_VERSION_OUTPUT)

  # Extract the version number using a more general regex
  # This regex is designed to match version numbers in the format of X.Y.Z where X, Y, and Z are integers
  # It looks for these numbers following a space or a v character and possibly followed by additional text (e.g., "13.2.1 20231009")
  string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" GCC_VERSION ${GCC_VERSION_OUTPUT})

  # Format the detected version for comparison
  set(detected_version "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")

  # Check if the version matches the required version
  if(NOT "${detected_version}" STREQUAL "${required_version}")
    message(STATUS "The version of arm-none-eabi-gcc does not match the required version ${required_version}.")
    message(STATUS "Detected arm-none-eabi-gcc version ${detected_version}.")
    message(FATAL_ERROR "Please ensure the ${required_version} version is installed for compatibility.")
  else()
    message(STATUS "Detected arm-none-eabi-gcc version ${detected_version}.")
  endif()
endfunction()