The source code of my Extended Essay

The Qt framework is required for building the project
The path in "widget.h" need to be changed depending on where the project was downloaded to and what platform the project is run on (use linPath, macPath and winPath for the appropriate platform)

When building with CMake the path to the install path of the Qt library (CMAKE_PREFIX_PATH) has to be set in the CMakeLists.txt file. The build and clean scripts can be used to automatically run CMake folowed by make (pass Debug or Release as first command line argument). The compiled program will be located under ./Sources/build
