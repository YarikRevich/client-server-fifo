if (NOT WIN32)
	cmake_minimum_required(VERSION 3.16)
	project(editor VERSION 0.0.1 LANGUAGES C CXX)

	set(CMAKE_CXX_COMPILER /usr/bin/g++)
	set(CMAKE_CXX_FLAGS "-std=c++17 -D_XOPEN_SOURCE_EXTENDED")
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
	message("Make build output path is /bin")

    # Describes prefix used for client input queue.
	add_compile_definitions(CLIENT_INPUT_QUEUE_SUFFIX="client_input")

    # Describes prefix used for client output queue.
	add_compile_definitions(CLIENT_OUTPUT_QUEUE_SUFFIX="client_output")

    # Describes prefix used for servermanager input queue.
	add_compile_definitions(SERVER_MANAGER_INPUT_QUEUE_SUFFIX="servermanager_input")

	# Describes server unit startup delay.
	add_compile_definitions(SERVER_UNIT_DELAY=200)

    # Describes max amount of elements in the given data.
	add_compile_definitions(MAX_DATA_NUM=30)

	include_directories(
		"include/"
	)

	add_executable(
		client-server 

		src/cmd/main.cpp

		src/internal/clientmanager/clientmanager.cpp
		src/internal/serverunit/serverunit.cpp
		src/internal/servermanager/servermanager.cpp
        src/internal/signalmanager/signalmanager.cpp
		src/internal/processor/processor.cpp
        src/internal/state/state.cpp
        src/internal/logger/logger.cpp

        src/internal/command/client/client.cpp
        src/internal/command/server/server.cpp
        src/internal/command/handler/handler.cpp
        src/internal/command/validator/validator.cpp
	)

	if (NOT WIN32)
		install(TARGETS client-server DESTINATION /usr/local/bin)
	endif()
else()
	message("You mustn't use the worst os in the world to install this perfect application")
endif()