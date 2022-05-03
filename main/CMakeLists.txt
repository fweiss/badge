idf_component_register(SRCS "BadgeService.cpp" "main.cpp" "UartService.cpp"
                    INCLUDE_DIRS .
	REQUIRES
		blewiz animations matrix motion nvs_flash app_update)
