# 1. Find all .cpp files in the data_structures directory and save them to a list
file(GLOB DS_SOURCES "*.cpp")

# 2. Loop through every file found in that list
foreach(SOURCE_FILE ${DS_SOURCES})
    
    # Extract just the filename without the extension
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)
    
    # 3. Create a standalone executable for each data structure file
    add_executable(${TARGET_NAME} ${SOURCE_FILE})

endforeach()