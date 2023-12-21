if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    cmake_minimum_required(VERSION 3.20)
else()
    cmake_minimum_required(VERSION 3.13)
endif()

# set the project name and version
project(
    JeuOne
    LANGUAGES    CXX ASM
    VERSION      1.1
    DESCRIPTION  "My first game"
)

# specify the C++ standard
if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_STANDARD 98)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR "MinSizeRel")
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(CMakeConfig.h.in CMakeConfig.h)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(SDL2 REQUIRED)
else()
    set(SDL2_INCLUDE_DIRS
        "E:/dev/SDL2-2.28.1/i686-w64-mingw32/include")
    set(SDL2_LIBRARIES
        "E:/dev/SDL2-2.28.1/i686-w64-mingw32/lib/libSDL2main.a"
        "E:/dev/SDL2-2.28.1/i686-w64-mingw32/lib/libSDL2.dll.a"
        "E:/dev/SDL2_image-2.6.3/i686-w64-mingw32/lib/libSDL2_image.dll.a")
    # set(SDL_INCLUDE_DIRS
    #     "E:/dev/SDL-1.2.15/include")
    # set(SDL_LIBRARIES
    #     "E:/dev/SDL-1.2.15/lib/libSDLmain.a"
    #     "E:/dev/SDL-1.2.15/lib/libSDL.dll.a"
    #     "E:/dev/SDL_image-1.2.12/lib/x86/SDL_image.lib")
endif()

# Fonctions de lecture/écriture de fichiers, fonctions de conversion de texte
if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    psn00bsdk_add_library(JeuES STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/psx/fichierES.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/conversions.cpp"
    )
else()
    add_library(JeuES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cstdio/fichierES.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/conversions.cpp"
    )
endif()
target_include_directories(JeuES PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Fonctions d'affichage de base
if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    psn00bsdk_add_library(JeuGfx STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/psx/Input.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/psx/moteur_graphique.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/fonctions_graphiques.cpp"
    )
else()
    add_library(JeuGfx
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl/Input.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl/moteur_graphique.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/fonctions_graphiques.cpp"
    )
    # add_library(JeuGfx
    #     "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl1/Input.cpp"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl1/moteur_graphique.cpp"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/src/fonctions_graphiques.cpp"
    # )
    # add_library(JeuGfx
    #     "${CMAKE_CURRENT_SOURCE_DIR}/src/cstdio/Input.cpp"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/src/cstdio/moteur_graphique.cpp"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/src/fonctions_graphiques.cpp"
    # )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    target_include_directories(JeuGfx PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
else()
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_link_libraries(JeuGfx PUBLIC -lSDL2 -lSDL2_image)
    else()
        target_link_libraries(JeuGfx PUBLIC ${SDL2_LIBRARIES})
        # target_link_libraries(JeuGfx PUBLIC ${SDL_LIBRARIES})
    endif()
    target_include_directories(JeuGfx PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        ${SDL2_INCLUDE_DIRS}
        # ${SDL_INCLUDE_DIRS}
    )
endif()

# Classes utilisées dans le jeu
set(JEULIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Alteration.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Capacite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Carte.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Effet.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Elements.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Equipable.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Equipe.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Evenement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/GroupeMonstres.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/GroupeObjets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Heros.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Inventaire.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Magasin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Monstre.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Objet.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Partie.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Personnage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Script.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Tileset.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/Utilisable.cpp"
)

if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    psn00bsdk_add_library(JeuLib STATIC ${JEULIB_SOURCES})
else()
    add_library(JeuLib ${JEULIB_SOURCES})
endif()

# Classe "Input" non implémentée avant JeuOne
# target_link_libraries(JeuLib PUBLIC JeuGfx)

target_include_directories(JeuLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Scenes (affichage et gestion des ressources) et main
set(JEUONE_SOURCES
    main.cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Combat.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Ecran_titre.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Game_Over.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Competences.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Configuration.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Equipement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Etat.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Magasin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Nom.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Objets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu_Sauver.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/affichage/Terrain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Combat.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Ecran_titre.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Game_Over.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Competences.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Configuration.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Equipement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Etat.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Magasin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Nom.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Objets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu_Sauver.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/Terrain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/bdd/fonctions.cpp"
)
if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    psn00bsdk_add_executable(JeuOne STATIC ${JEUONE_SOURCES})
else()
    add_executable(JeuOne ${JEUONE_SOURCES})
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    target_link_libraries(JeuOne JeuLib JeuGfx JeuES psn00bsdk_static_exe ${PSN00BSDK_LIBRARIES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(JeuOne PUBLIC JeuLib JeuGfx JeuES)
else()
    target_link_libraries(JeuOne PUBLIC -lmingw32 JeuLib JeuGfx JeuES)
endif()

# add the binary tree to the search path for include files
# so that we will find CMakeConfig.h
target_include_directories(JeuOne PRIVATE "${PROJECT_BINARY_DIR}")

# Convertisseur de bdd
if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    # psn00bsdk_add_executable(txt2dat STATIC txt2dat.cpp)
else()
    add_executable(txt2dat txt2dat.cpp)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    # target_link_libraries(txt2dat JeuLib JeuES)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(txt2dat PUBLIC JeuLib JeuES)
else()
    target_link_libraries(txt2dat PUBLIC -lmingw32 JeuLib JeuES)
endif()

# Convertir les textures
if(CMAKE_SYSTEM_NAME STREQUAL "PlayStation")
    # exec_program("../iso/img2tim" "${CMAKE_CURRENT_SOURCE_DIR}/graphics" ARGS "page_police.png"   -org 640 0 -plt 640 256 -b -tindex 0)
    # exec_program("../iso/img2tim" "${CMAKE_CURRENT_SOURCE_DIR}/graphics" ARGS "page_tuiles.png"   -org 640 0 -plt 640 256 -b -tindex 0)
    # exec_program("../iso/img2tim" "${CMAKE_CURRENT_SOURCE_DIR}/graphics" ARGS "page_tuiles.png"   -org 704 0 -plt 704 256 -b -tindex 0)
    # exec_program("../iso/img2tim" "${CMAKE_CURRENT_SOURCE_DIR}/graphics" ARGS "page_sprites.png"  -org 768 0 -plt 768 256 -b -tindex 0)
    # exec_program("../iso/img2tim" "${CMAKE_CURRENT_SOURCE_DIR}/graphics" ARGS "page_heros.png"    -org 832 0 -plt 832 256 -b -tindex 0)
    # exec_program("../iso/img2tim" "${CMAKE_CURRENT_SOURCE_DIR}/graphics" ARGS "page_monstres.png" -org 896 0 -plt 896 256 -b -tindex 0)

    psn00bsdk_add_cd_image(
        iso         # Target name
        image       # Output file name (= image.bin + image.cue)
        iso/iso.xml # Path to config file
        DEPENDS JeuOne
    )
endif()
