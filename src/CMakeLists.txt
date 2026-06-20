cmake_minimum_required(VERSION 3.19)
project(Probleme_a_trois_corps LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets PrintSupport)

qt_standard_project_setup()

qt_add_executable(Probleme_a_trois_corps
    WIN32 MACOSX_BUNDLE

    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    experiencerecord.h
    bodypanel.h bodypanel.cpp bodypanel.ui
    addexperiencedialog.h addexperiencedialog.cpp
    templatedialog.h templatedialog.cpp templatedialog.ui
    createtemplatedialog.h createtemplatedialog.cpp
    main.cpp

    vect.h vect.cpp
    corps.h corps.cpp
    simview.h simview.cpp
    randomgenerator.h randomgenerator.cpp
    startexperience.h startexperience.cpp
    historydialog.h historydialog.cpp
    modele.h modele.cpp
    constants.h constants.cpp
    lancertemplatedialog.h lancertemplatedialog.cpp
    integrateur.h
    integrateur.cpp
    app.rc

)
qt_add_resources(Probleme_a_trois_corps "resources"
    PREFIX "/images"
    FILES logo.ico
)

target_include_directories(Probleme_a_trois_corps
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Probleme_a_trois_corps
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::PrintSupport
)

include(GNUInstallDirs)

install(TARGETS Probleme_a_trois_corps
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Probleme_a_trois_corps
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
