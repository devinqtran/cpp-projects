# 1. Find all .cpp files in the current directory and save them to a list
file(GLOB PRACTICE_SOURCES "*.cpp")

# 2. Loop through every file found in that list
foreach(SOURCE_FILE ${PRACTICE_SOURCES})
    
    # Extract just the filename without the extension (e.g., "loops" from "loops.cpp")
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    
    # 3. Create an executable using that filename
    add_executable(${TARGET_NAME} ${SOURCE_FILE})

endforeach()