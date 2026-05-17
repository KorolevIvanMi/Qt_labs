cmake_minimum_required(VERSION 3.5)

project(OOP_Qt_Labs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Qt с компонентами Widgets и Sql
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OOP_Qt_Labs
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        reader.h reader.cpp
        newreader.h newreader.cpp
        regularreader.h regularreader.cpp
        premiumreader.h premiumreader.cpp
        readerfactory.h readerfactory.cpp
        book.h book.cpp
        loan.h loan.cpp
        publisher.h publisher.cpp
        libraryfacade.h libraryfacade.cpp
        searchstrategy.h searchstrategy.cpp
        modelfactory.h modelfactory.cpp
        loanobserver.h loanobserver.cpp
        addbookdialog.h addbookdialog.cpp
        addreaderdialog.h addreaderdialog.cpp
        addpublisherdialog.h addpublisherdialog.cpp
        issuedialog.h issuedialog.cpp
        returndialog.h returndialog.cpp
        editbookdialog.h editbookdialog.cpp
        editreaderdialog.h editreaderdialog.cpp
        editpublisherdialog.h editpublisherdialog.cpp
    )
else()
    if(ANDROID)
        add_library(OOP_Qt_Labs SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(OOP_Qt_Labs
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линкуем Widgets и Sql модули
target_link_libraries(OOP_Qt_Labs PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.OOP_Qt_Labs)
endif()
set_target_properties(OOP_Qt_Labs PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS OOP_Qt_Labs
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OOP_Qt_Labs)
endif()
