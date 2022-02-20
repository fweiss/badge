idf_component_register(
	SRCS
		BLEAttribute.cpp
		BLECharacteristic.cpp
		BLECore.cpp
		BLEDescriptor.cpp
		BLEService.cpp
		
	INCLUDE_DIRS inc/blewiz inc
	REQUIRES bt
)
