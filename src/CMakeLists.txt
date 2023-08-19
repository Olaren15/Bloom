add_executable(${PROJECT_NAME}
        main.cpp
        bloomApp.h
        bloomApp.cpp
        validationHelper.cpp
        validationHelper.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        $<IF:$<TARGET_EXISTS:glm::glm>,glm::glm,glm>
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        volk::volk
)