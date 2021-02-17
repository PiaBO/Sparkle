#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/motor2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Sprite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Status.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/KitchenStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Shop.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TextureManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Npc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pocion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MenuStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MenuInGameStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EndMenuStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/FontManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Text.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Clock.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libroStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Alert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AguaQteStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/FuegoQteStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AireQteStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TierraQteStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TutorialStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Pot.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Missions.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mission.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Music.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

