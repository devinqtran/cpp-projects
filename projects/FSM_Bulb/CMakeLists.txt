# Create the executable from your source code
add_executable(FSM_Bulb 
    main.cpp
    
    # Header files (Included so they populate in your IDE's file tree)
    Bulb.h
    FSM.h
    State.h
    Transition.h
    LinkedList.h
    stdafx.h
)

# Note: If any of your headers have corresponding .cpp files 
# (e.g., FSM.cpp, State.cpp), make sure to add them to the list above!