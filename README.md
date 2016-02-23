The source code of my Extended Essay

The path in "widget.h" need to be changed depending on where the project was downloaded to and what platform the project is run on (use linPath, macPath and winPath for the appropriate platform)
When building with CMake the path to the install path of the Qt library has to be set (CMAKE_PREFIX_PATH).
