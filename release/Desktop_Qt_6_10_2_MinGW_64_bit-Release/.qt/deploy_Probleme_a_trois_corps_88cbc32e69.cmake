include("C:/Users/admin/Desktop/Projet_version_final/build/Desktop_Qt_6_10_2_MinGW_64_bit-Release/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Probleme_a_trois_corps-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "C:/Users/admin/Desktop/Projet_version_final/build/Desktop_Qt_6_10_2_MinGW_64_bit-Release/Probleme_a_trois_corps.exe"
    GENERATE_QT_CONF
)
