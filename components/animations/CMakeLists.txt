idf_component_register(
	SRCS 
		Alphabet.cpp
		Animation.cpp
		BitmapAnimation.cpp
		CandyChaser.cpp
		Chaser.cpp
		DiceAnimation.cpp
		EmojiAnimation.cpp
		Felix.cpp
        Frame.cpp
		Funbit64.cpp
		Gravity.cpp
		HeartAnimation.cpp
        IndexedColorAnimation.cpp
		JsonAnimation.cpp
		Kaleidascope.cpp
		MarqueeAniumation.cpp
		MeteorShowerAnimation.cpp
		MiscellanyAnimation.cpp
		PaintPixel.cpp
		Party.cpp
		PathAnimation.cpp
		Plasma.cpp
		RainbowChaser.cpp
		SmearAnimation.cpp
		SpinBottle2.cpp
		SpinBottleAnimation.cpp
		SpiralAnimation.cpp
		Tween.cpp
		Weather.cpp
		WormholeAnimation.cpp

	INCLUDE_DIRS inc inc/animations
    REQUIRES
    	matrix
    	json
		motion
)

set_target_properties(${COMPONENT_LIB} PROPERTIES COMPILE_FLAGS "-save-temps=obj")
