idf_component_register(
	SRCS
		Motion.cpp
		MPU6050.cpp
		I2CDevice.cpp
    INCLUDE_DIRS 
    	inc/motion
    	inc
    REQUIRES driver esp_timer
)
