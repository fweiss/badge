idf_component_register(SRCS
    AnimationProgram.cpp
    AnimationTask.cpp
    Timer.cpp
    TimerAnimationTask.cpp
    Display.cpp
    Profiler.cpp

    INCLUDE_DIRS inc inc/player
    REQUIRES
        animations
)
