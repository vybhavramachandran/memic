###############################################################################Biogears_THROW_READONLY_EXCEPTIONS
# Policy adjustments
###############################################################################


###############################################################################
# Options
###############################################################################

option (${ROOT_PROJECT_NAME}_THROW_READONLY_EXCEPTIONS "Toggle the throwing CommonDataModelExceptions when a ReadOnly SEScalar is Modified." ON)
option (${ROOT_PROJECT_NAME}_THROW_NAN_EXCEPTIONS "Toggle the throwing CommonDataModelExceptions when an  SEScalar is NaNExceptions." ON)
option (${ROOT_PROJECT_NAME}_USE_OVERRIDE_CONTROL       "When enabled Biogears will control the ranges of override"  OFF)
option (${ROOT_PROJECT_NAME}_BUILD_CIRCUIT_TESTS       "Toggle on the Circuit Test Library which is a dependeny of libbiogears_jni"  ON)

###############################################################################
# Base Variables
###############################################################################
set(PROJECT_NAME biogears)
set(PREFIX bio)

set(${PREFIX}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/include" )
set(${PREFIX}_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/src" )
set(${PREFIX}_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}" )
set(${PREFIX}_UNIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/unit" PARENT_SCOPE)

###############################################################################
# Requirments
###############################################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
if(WIN32)
  set(Boost_USE_STATIC_LIBS ON) 
endif()
verify_package(Threads REQUIRED)
verify_package(Eigen3 REQUIRED)
verify_package(CodeSynthesis REQUIRED)

###############################################################################
#Code Generation
###############################################################################
file(GLOB_RECURSE biogears_xsd_list "${PROJECT_SOURCE_DIR}/share/xsd/biogears/*.xsd")
file(GLOB_RECURSE cdm_xsd_list "${PROJECT_SOURCE_DIR}/share/xsd/cdm/*.xsd")


REGISTER_XSD_DIR(  ""   CONFIG BioGearsDataModel.cfg 
                    ROOT "biogears" SUBPATH "schema" RESOURCE_FOLDER "resources/schema"
                    TARGETS XSD_TARGETS)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/src/version.cpp.in  ${CMAKE_CURRENT_BINARY_DIR}/libBiogears/src/version.cpp NEWLINE_STYLE LF)
###############################################################################
#Sorce and Header Defines
###############################################################################
message(STATUS "")
message(STATUS "Configuring ${PROJECT_NAME}")

#Biogears CDM
add_source_files(PUBLIC_CDM_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/libCDM "*.h"  "Headers\\Public\\")
add_source_files(GEN_CDM_HDRS ${CMAKE_CURRENT_BINARY_DIR}/biogears "*.hxx"  "Headers\\Public\\")
add_source_files(GEN_CDM_SRCS ${CMAKE_CURRENT_BINARY_DIR}/biogears "*.cxx" "Sources\\")
#Biogears Core
add_source_files(HDRS ${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/src "*.h"   "Headers\\Private\\")
add_source_files(SRCS ${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/src "*.cpp" "Sources\\")
add_source_files(GEN_SRCS ${CMAKE_CURRENT_BINARY_DIR}/libBiogears/src "version.cpp" "Sources\\")

add_source_files(PUBLIC_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/include "*.h"  "Headers\\Public\\")
add_source_files(PUBLIC_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/libBiogears/include "*.inl"  "Headers\\Public\\")
#Biogears circuit_test
add_source_files(PUBLIC_CIRCUIT_TEST_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/libCircuitTest/include "*.h"  "Headers\\Public\\")
add_source_files(CIRCUIT_TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/libCircuitTest/src "*cpp" "Sources\\")
#Biogears JNI
add_source_files(PUBLIC_JNI_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/libJNI/include "*.h"  "Headers\\Public\\")
add_source_files(JNI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/libJNI/src "*cpp" "Sources\\")

set(LIB${PREFIX}_CDM_HEADERS ${CDM_HDRS} ${PUBLIC_CDM_HDRS} ${GEN_CDM_HDRS})
set(LIB${PREFIX}_CDM_SOURCES ${CDM_SRCS} ${GEN_CDM_SRCS})

set(LIB${PREFIX}_HEADERS ${HDRS} ${PUBLIC_HDRS} ${GEN_HDRS})
set(LIB${PREFIX}_SOURCES ${SRCS} ${GEN_SRCS})

set(LIB${PREFIX}_CIRCUIT_TEST_HEADERS ${CIRCUIT_TEST_HDRS} ${PUBLIC_CIRCUIT_TEST_HDRS} ${GEN_CIRCUIT_TEST_HDRS})
set(LIB${PREFIX}_CIRCUIT_TEST_SOURCES ${CIRCUIT_TEST_SRCS} ${GEN_CIRCUIT_TEST_SRCS})

set(LIB${PREFIX}_JNI_HEADERS ${JNI_HDRS} ${PUBLIC_JNI_HDRS} ${GEN_JNI_HDRS})
set(LIB${PREFIX}_JNI_SOURCES ${JNI_SRCS} ${GEN_JNI_SRCS})

message(STATUS CMAKE_GENERATOR=${CMAKE_GENERATOR})
###############################################################################
#Define Logic
###############################################################################
if(${PREFIX}_BUILD_STATIC)
  add_library(lib${PROJECT_NAME} STATIC ${LIB${PREFIX}_SOURCES} ${LIB${PREFIX}_HEADERS})
  add_library(Biogears::lib${PROJECT_NAME} ALIAS lib${PROJECT_NAME})
	set_target_properties(lib${PROJECT_NAME}
    PROPERTIES
    DEFINE_SYMBOL ${PROJECT_NAME}_EXPORTS
    FOLDER "Libraries"
    OUTPUT_NAME "${PROJECT_NAME}"
    COMPILE_PDB_NAME "${PROJECT_NAME}"
    PROJECT_LABEL "lib${PROJECT_NAME}"
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    CXX_STANDARD 14
    )
  set_target_properties(lib${PROJECT_NAME} PROPERTIES SOVERSION "${${ROOT_PROJECT_NAME}_LIB_VERSION}")
   if(${PROJECT_NAME}_USE_OVERRIDE_CONTROL)
      target_compile_definitions( lib${PROJECT_NAME} PRIVATE BIOGEARS_USE_OVERRIDE_CONTROL)
   endif()
  if(WIN32)
    list(APPEND ${PREFIX}_CPPFLAGS _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS NOMINMAX $ENV{PARALLEL_COMPILE} )
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND ${PREFIX}_CPPFLAGS  ${CodeSynthesis_CPPFLAGS})
    list(APPEND ${PREFIX}_LDFLAGS "-Wl,--no-as-needed" )
    set_target_properties(lib${PROJECT_NAME} PROPERTIES LINK_FLAGS ${${PREFIX}_LDFLAGS})
endif()
  ###############################################################################
  # COMPILATION & LINKAGE MODIFICATIONS
  ###############################################################################
  target_compile_definitions(lib${PROJECT_NAME} PUBLIC ${PREFIX}_BUILT_AS_STATIC ${${PREFIX}_CPPFLAGS_INTERFACE} $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},armv7-a>:XSD_NO_EXPORT>)
  target_compile_definitions(lib${PROJECT_NAME} PRIVATE ${${PREFIX}_CPPFLAGS} )
  target_compile_options(lib${PROJECT_NAME} PRIVATE $<$<PLATFORM_ID:Windows>:/bigobj>  PRIVATE $<$<PLATFORM_ID:Windows>:/MP${${ROOT_PROJECT_NAME}_BUILD_PARALLEL_LEVEL}>)
  if(${ROOT_PROJECT_NAME}_THROW_READONLY_EXCEPTIONS)
        target_compile_definitions(lib${PROJECT_NAME} PUBLIC BIOGEARS_THROW_READONLY_EXCEPTIONS)
  endif()
   if(${ROOT_PROJECT_NAME}_THROW_NAN_EXCEPTIONS )
        target_compile_definitions(lib${PROJECT_NAME} PUBLIC BIOGEARS_THROW_NAN_EXCEPTIONS )
  endif()
  target_include_directories(lib${PROJECT_NAME}
      PRIVATE  ${${PREFIX}_INCLUDE_DIR} ${${PREFIX}_PRIVATE_INCLUDE_DIR} ${${PREFIX}_GENERATED_INCLUDE_DIR}
      INTERFACE $<BUILD_INTERFACE:${${PREFIX}_GENERATED_INCLUDE_DIR}> 
                $<BUILD_INTERFACE:${${PREFIX}_INCLUDE_DIR}>
                $<INSTALL_INTERFACE:include>
  )
  
  if(${ROOT_PROJECT_NAME}_BUILD_JAVATOOLS)
	  target_include_directories(lib${PROJECT_NAME} PRIVATE ${Java_INCLUDE_DIRS})
  endif()

  set(${PREFIX}_LIBS
        Threads::Threads
        Eigen3::Eigen
        Log4cpp::Log4cpp
        CodeSynthesis::XSD
        ${CMAKE_DL_LIBS}
  )
  target_link_libraries(lib${PROJECT_NAME} Biogears::common ${${PREFIX}_LIBS} )
  add_dependencies(lib${PROJECT_NAME} ${XSD_TARGETS} prepare_runtime_dir)

else()
  ###############################################################################
  # libBiogears_cdm
  ###############################################################################
  add_library(lib${PROJECT_NAME}_cdm    SHARED ${LIB${PREFIX}_CDM_SOURCES} ${LIB${PREFIX}CMD__HEADERS})
  add_library(Biogears::lib${PROJECT_NAME}_cdm ALIAS lib${PROJECT_NAME}_cdm)
  set_target_properties(lib${PROJECT_NAME}_cdm
    PROPERTIES
    DEFINE_SYMBOL ${PROJECT_NAME}_cdm_EXPORTS
    FOLDER "Libraries"
    OUTPUT_NAME "${PROJECT_NAME}_cdm"
    COMPILE_PDB_NAME "${PROJECT_NAME}_cdm"
    PROJECT_LABEL "lib${PROJECT_NAME}_cdm"
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    CXX_STANDARD 14
    )
  set_target_properties(lib${PROJECT_NAME}_cdm PROPERTIES SOVERSION "${${ROOT_PROJECT_NAME}_LIB_VERSION}")
  add_dependencies(lib${PROJECT_NAME}_cdm ${XSD_TARGETS})

  ###############################################################################
  # libBiogears_cdm COMPILATION & LINKAGE MODIFICATIONS
  ###############################################################################
  set( ${PREFIX}_CPPFLAGS $<$<PLATFORM_ID:Windows>:_SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS NOMINMAX > )
  target_compile_definitions(lib${PROJECT_NAME}_cdm  PUBLIC ${${PREFIX}_CPPFLAGS_INTERFACE} $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},armv7-a>:XSD_NO_EXPORT>)
  target_compile_definitions(lib${PROJECT_NAME}_cdm  PRIVATE ${${PREFIX}_CPPFLAGS} )
  target_compile_options(lib${PROJECT_NAME}_cdm PRIVATE $<$<PLATFORM_ID:Windows>:/bigobj>  PRIVATE $<$<PLATFORM_ID:Windows>:/MP${${ROOT_PROJECT_NAME}_BUILD_PARALLEL_LEVEL}>)
  
  target_include_directories(lib${PROJECT_NAME}_cdm 
      PRIVATE  ${${PREFIX}_INCLUDE_DIR} ${${PREFIX}_PRIVATE_INCLUDE_DIR} ${${PREFIX}_GENERATED_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libCDM/include
      INTERFACE 
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libCDM/include>
                $<INSTALL_INTERFACE:include>
  )
  
  set(${PREFIX}_cdm_LIBS
            CodeSynthesis::XSD
            Eigen3::Eigen
  )
	message(STATUS "${PREFIX}_cdm_LIBS=${${PREFIX}_cdm_LIBS}")
    target_link_libraries(lib${PROJECT_NAME}_cdm  PUBLIC ${${PREFIX}_cdm_LIBS} )

  install(TARGETS lib${PROJECT_NAME}_cdm  EXPORT libBiogears
      RUNTIME DESTINATION bin/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
      LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
      ARCHIVE DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
  )
  if(WIN32)
	install(FILES $<TARGET_PDB_FILE:lib${PROJECT_NAME}_cdm> DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>> OPTIONAL)
  endif()
  ###############################################################################
  # libBiogears
  ###############################################################################
  add_library(lib${PROJECT_NAME} SHARED ${LIB${PREFIX}_SOURCES} ${LIB${PREFIX}_HEADERS})
  add_library(Biogears::lib${PROJECT_NAME} ALIAS lib${PROJECT_NAME})
  	set_target_properties(lib${PROJECT_NAME}
    PROPERTIES
    DEFINE_SYMBOL ${PROJECT_NAME}_EXPORTS
    FOLDER "Libraries"
    OUTPUT_NAME "${PROJECT_NAME}"
    COMPILE_PDB_NAME "${PROJECT_NAME}"
    PROJECT_LABEL "lib${PROJECT_NAME}"
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    CXX_STANDARD 14
    )
  set_target_properties(lib${PROJECT_NAME} PROPERTIES SOVERSION "${${ROOT_PROJECT_NAME}_LIB_VERSION}")

  ###############################################################################
  # libBiogears COMPILATION & LINKAGE MODIFICATIONS
  ###############################################################################
  set( ${PREFIX}_CPPFLAGS $<$<PLATFORM_ID:Windows>:_SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS NOMINMAX > )
  target_compile_definitions(lib${PROJECT_NAME}  PUBLIC ${${PREFIX}_CPPFLAGS_INTERFACE})
  target_compile_definitions(lib${PROJECT_NAME}  PRIVATE ${${PREFIX}_CPPFLAGS} )

    target_compile_options(lib${PROJECT_NAME} PRIVATE $<$<PLATFORM_ID:Windows>:/bigobj> PRIVATE $<$<PLATFORM_ID:Windows>:/MP${${ROOT_PROJECT_NAME}_BUILD_PARALLEL_LEVEL}>)

    if(${ROOT_PROJECT_NAME}_THROW_READONLY_EXCEPTIONS)
        target_compile_definitions(lib${PROJECT_NAME} PUBLIC BIOGEARS_THROW_READONLY_EXCEPTIONS)
  endif()
   if(${ROOT_PROJECT_NAME}_THROW_NAN_EXCEPTIONS )
        target_compile_definitions(lib${PROJECT_NAME} PUBLIC BIOGEARS_THROW_NAN_EXCEPTIONS )
  endif()
	if(${ROOT_PROJECT_NAME}_USE_OVERRIDE_CONTROL)
	  target_compile_definitions( lib${PROJECT_NAME}  PRIVATE BIOGEARS_USE_OVERRIDE_CONTROL)
  endif()

  target_include_directories(lib${PROJECT_NAME} 
      PRIVATE  ${${PREFIX}_INCLUDE_DIR} ${${PREFIX}_PRIVATE_INCLUDE_DIR} ${${PREFIX}_GENERATED_INCLUDE_DIR} 
      INTERFACE 
                $<BUILD_INTERFACE:${${PREFIX}_INCLUDE_DIR}>
				$<BUILD_INTERFACE:${${PREFIX}_GENERATED_INCLUDE_DIR}>
                $<INSTALL_INTERFACE:include>
  )
  
  set(${PREFIX}_LIBS
            Eigen3::Eigen
            Log4cpp::Log4cpp
			Biogears::lib${PROJECT_NAME}_common
            Biogears::lib${PROJECT_NAME}_cdm
  )
  message(STATUS "${PREFIX}_LIBS=${${PREFIX}_LIBS}")
  target_link_libraries(lib${PROJECT_NAME}  PUBLIC ${${PREFIX}_LIBS} )
  #install(TARGETS lib${PROJECT_NAME} EXPORT libBiogears
  #    RUNTIME DESTINATION bin/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
  #    LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
  #    ARCHIVE DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
  #)
  if(WIN32)
		install(FILES $<TARGET_PDB_FILE:lib${PROJECT_NAME}> DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>> OPTIONAL)
  endif()
  ###############################################################################
  # libBiogears_circuit_test
  ###############################################################################
  if( ${ROOT_PROJECT_NAME}_BUILD_CIRCUIT_TESTS)
     add_library(lib${PROJECT_NAME}_circuit_test  SHARED ${LIB${PREFIX}_CIRCUIT_TEST_SOURCES} ${LIB${PREFIX}_CIRCUIT_TEST_HEADERS})
     add_library(Biogears::lib${PROJECT_NAME}_circuit_test ALIAS lib${PROJECT_NAME}_circuit_test)
       set_target_properties(lib${PROJECT_NAME}_circuit_test
       PROPERTIES
       DEFINE_SYMBOL ${PROJECT_NAME}_CIRCUIT_TEST_EXPORTS
       FOLDER "Libraries"
       OUTPUT_NAME "${PROJECT_NAME}_circuit_test"
       COMPILE_PDB_NAME "${PROJECT_NAME}_circuit_test"
       PROJECT_LABEL "lib${PROJECT_NAME}_circuit_test"
       DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
       CXX_STANDARD 14
       )
   set_target_properties(lib${PROJECT_NAME}_circuit_test PROPERTIES SOVERSION "${${ROOT_PROJECT_NAME}_LIB_VERSION}")
  ###############################################################################
  # libBiogears_circuit_test COMPILATION & LINKAGE MODIFICATIONS
  ###############################################################################
  set( ${PREFIX}_CPPFLAGS $<$<PLATFORM_ID:Windows>:_SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS NOMINMAX > )
  target_compile_definitions(lib${PROJECT_NAME}_circuit_test  PUBLIC ${${PREFIX}_CPPFLAGS_INTERFACE})
  target_compile_definitions(lib${PROJECT_NAME}_circuit_test  PRIVATE ${${PREFIX}_CPPFLAGS} )
  target_compile_options(lib${PROJECT_NAME}_circuit_test PRIVATE $<$<PLATFORM_ID:Windows>:/bigobj>  PRIVATE $<$<PLATFORM_ID:Windows>:/MP${${ROOT_PROJECT_NAME}_BUILD_PARALLEL_LEVEL}>)
  
  target_include_directories(lib${PROJECT_NAME}_circuit_test 
      PRIVATE  ${${PREFIX}_INCLUDE_DIR} ${${PREFIX}_PRIVATE_INCLUDE_DIR} ${${PREFIX}_GENERATED_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libCircuitTest/include
      PUBLIC   ${CIRCUIT_TEST_INCLUDE_DIRS}
      INTERFACE 
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libCircuitTest/include>
                $<INSTALL_INTERFACE:include>
  )

  set(${PREFIX}_CIRCUIT_TEST_LIBS
            CodeSynthesis::XSD
            Eigen3::Eigen
            Biogears::lib${PROJECT_NAME}
  )
  message(STATUS "${PREFIX}_circuit_test_LIBS=${${PREFIX}_circuit_test_LIBS}")
    target_link_libraries(lib${PROJECT_NAME}_circuit_test  PUBLIC ${${PREFIX}_CIRCUIT_TEST_LIBS} )


     install(TARGETS lib${PROJECT_NAME}_circuit_test EXPORT libBiogears
         RUNTIME DESTINATION bin/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
         LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
         ARCHIVE DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
      )
	  if(WIN32)
	    install(FILES $<TARGET_PDB_FILE:lib${PROJECT_NAME}_circuit_test> DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>> OPTIONAL)
	  endif()
   endif()
  ###############################################################################
  # libBiogears_jni
  ###############################################################################
  if(Java_FOUND AND ${ROOT_PROJECT_NAME}_BUILD_JAVATOOLS AND ${ROOT_PROJECT_NAME}_BUILD_CIRCUIT_TESTS)
     add_library(lib${PROJECT_NAME}_jni  SHARED ${LIB${PREFIX}_JNI_SOURCES} ${LIB${PREFIX}_JNI_HEADERS})
     add_library(Biogears::lib${PROJECT_NAME}_jni ALIAS lib${PROJECT_NAME}_jni)
  	   set_target_properties(lib${PROJECT_NAME}_jni
       PROPERTIES
       DEFINE_SYMBOL ${PROJECT_NAME}_jni_EXPORTS
       FOLDER "Libraries"
       OUTPUT_NAME "${PROJECT_NAME}_jni"
       COMPILE_PDB_NAME "${PROJECT_NAME}_jni"
       PROJECT_LABEL "lib${PROJECT_NAME}_jni"
       DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
       CXX_STANDARD 14
       )
     set_target_properties(lib${PROJECT_NAME}_jni PROPERTIES SOVERSION "${${ROOT_PROJECT_NAME}_LIB_VERSION}")
  ###############################################################################
  # libBiogears_jni COMPILATION & LINKAGE MODIFICATIONS
  ###############################################################################
  set( ${PREFIX}_CPPFLAGS $<$<PLATFORM_ID:Windows>:_SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS NOMINMAX > )
  target_compile_definitions(lib${PROJECT_NAME}_jni  PUBLIC ${${PREFIX}_CPPFLAGS_INTERFACE})
  target_compile_definitions(lib${PROJECT_NAME}_jni  PRIVATE ${${PREFIX}_CPPFLAGS} )
  target_compile_options(lib${PROJECT_NAME}_jni PRIVATE $<$<PLATFORM_ID:Windows>:/bigobj>  PRIVATE $<$<PLATFORM_ID:Windows>:/MP${${ROOT_PROJECT_NAME}_BUILD_PARALLEL_LEVEL}>)
  
  target_include_directories(lib${PROJECT_NAME}_jni 
      PRIVATE  ${${PREFIX}_INCLUDE_DIR} ${${PREFIX}_PRIVATE_INCLUDE_DIR} ${${PREFIX}_GENERATED_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libJNI/include
	    PUBLIC   ${JNI_INCLUDE_DIRS}
      INTERFACE 
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libJNI/include>
                $<INSTALL_INTERFACE:include>
  )
  
  set(${PREFIX}_jni_LIBS
            CodeSynthesis::XSD
            Eigen3::Eigen
            Biogears::lib${PROJECT_NAME}_circuit_test
  )
	message(STATUS "${PREFIX}_jni_LIBS=${${PREFIX}_jni_LIBS}")
    target_link_libraries(lib${PROJECT_NAME}_jni  PUBLIC ${${PREFIX}_jni_LIBS} )


     install(TARGETS lib${PROJECT_NAME}_jni EXPORT libBiogears
         RUNTIME DESTINATION bin/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
         LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
         ARCHIVE DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
      )
	  if(WIN32)
		 install(FILES $<TARGET_PDB_FILE:lib${PROJECT_NAME}_jni> DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>> OPTIONAL)
	  endif()
   endif()
endif() #${PREFIX}_BUILD_STATIC

######################################################################################################
# INSTALL LOGIC
######################################################################################################
install(TARGETS lib${PROJECT_NAME} EXPORT libBiogears
     RUNTIME DESTINATION bin/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
     LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
     ARCHIVE DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>>
)
if(WIN32)
	install(FILES $<TARGET_PDB_FILE:lib${PROJECT_NAME}> DESTINATION lib/${${ROOT_PROJECT_NAME}_PLATFORM_PREFIX}$<$<BOOL:${${ROOT_PROJECT_NAME}_BREAKOUT_INSTALL}>:/$<CONFIG>> OPTIONAL)
endif()

install(DIRECTORY 
    libBiogears/include/biogears
    libCDM/include/biogears
    libJNI/include/biogears
    libCircuitTest/include/biogears
	  ${CMAKE_CURRENT_BINARY_DIR}/biogears
    DESTINATION include/
    FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
    )
  
install(DIRECTORY 
    ${PROJECT_SOURCE_DIR}/share/xsd 
    DESTINATION share/biogears/${${ROOT_PROJECT_NAME}_VERSION_TAG}
    FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
    )

install(DIRECTORY 
    ${PROJECT_SOURCE_DIR}/share/data
    DESTINATION share/biogears/${${ROOT_PROJECT_NAME}_VERSION_TAG}
    FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
	FILES_MATCHING 
	  PATTERN "*.xml"
	  PATTERN "log4j.properties"
	  PATTERN "*.csv"
	  PATTERN "*.xlsx"
    )
install(DIRECTORY 
    ${PROJECT_SOURCE_DIR}/share/Scenarios
    DESTINATION share/biogears/${${ROOT_PROJECT_NAME}_VERSION_TAG}/data/
    FILE_PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
	FILES_MATCHING 
	PATTERN "*.xml"
    )
message(STATUS "")



#####################
## CYTHON LOGIC
#####################



# find_package(PythonExtensions REQUIRED)
# find_package(Cython REQUIRED)

# set(cython_modules_with_cpp
#     pycardio
#     )

# foreach(cython_module ${cython_modules_with_cpp})
#     add_cython_target(${cython_module} PY3 CXX)
#     add_library(${cython_module} MODULE ${${cython_module}})
#     # For some reason this command prints the name of the resulting module. Would
#     # be good to suppress if possible.
#     python_extension_module(${cython_module})
  
#     target_compile_definitions(
#       ${cython_module}
#       # Avoid deprecation warnings for unsupported NumPy API versions. See
#       # https://numpy.org/doc/1.19/reference/c-api/deprecations.html
#       PRIVATE "NPY_NO_DEPRECATED_API=NPY_1_10_API_VERSION"
#       # Default voro++ verbosity is high.
#       PRIVATE "VOROPP_VERBOSE=1")
#     if(COVERAGE)
#       target_compile_definitions(
#         ${cython_module} # Enable line tracing for coverage purposes if requested.
#         PRIVATE "CYTHON_TRACE_NOGIL=1")
#     endif()
  
#     target_link_libraries(${cython_module} libbiogears)
  
#     # Separate logic required for targets with C++ code.
#     if("${cython_module}" IN_LIST cython_modules_with_cpp)
  
#       target_include_directories(
#         ${cython_module} PRIVATE ${PROJECT_SOURCE_DIR}/projects/biogears/libBiogears/include/)
#     endif()
  
#     install(TARGETS ${cython_module} DESTINATION biogears)
  
#     # Coverage requires the Cython-compiled C++ files for line coverage.
#     if(COVERAGE)
#       install(FILES ${${cython_module}} DESTINATION biogears)
#     endif()
  
#     if(APPLE)
#       set_target_properties(${cython_module} PROPERTIES INSTALL_RPATH
#                                                         "@loader_path")
#     else()
#       set_target_properties(${cython_module} PROPERTIES INSTALL_RPATH "$ORIGIN")
#     endif()
#   endforeach()



#### PYBIND LOGICs

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
# find_package(pybind11 REQUIRED)
include_directories(/usr/include/python3.8/)
# FIND_PACKAGE(PythonInterp 3)
# FIND_PACKAGE(PythonLibs   3)


add_subdirectory(pybind11)
# pybind11_add_module(cmake_example src/main.cpp)


pybind11_add_module(pybcardio ./libBiogears/src/pybcardio.cpp)
pybind11_add_module(pyblogger ./libBiogears/src/pyblogger.cpp)
pybind11_add_module(pybscalarpressure ./libBiogears/src/pybscalarpressure.cpp)
pybind11_add_module(pybBioGearsEngine ./libBiogears/src/pybwrappers/engine/Controller/pybBioGearsEngine.cpp)
pybind11_add_module(pybBioGearsEngineHeader ./libBiogears/src/pybwrappers/engine/Controller/pybBioGearsEngineHeader.cpp)

set(pybind_include_directories /usr/include/python3.8 /home/vybhav/anaconda3/include/python3.8 /home/vybhav/Downloads/pybind11/include /opt/biogears/core/build/../projects/biogears/libCDM/include /opt/biogears/core/build/../build/projects/biogears /opt/biogears/core/projects/biogears/libBiogears/include  /opt/biogears/core/projects/biogears-common/include /opt/biogears/core/build/projects/biogears/biogears/schema /opt/biogears/core/projects/biogears/libBiogears/include/biogears/cdm/engine/)

target_include_directories(pybcardio
PRIVATE pybind_include_directories
)
target_include_directories(pyblogger
PRIVATE pybind_include_directories
)
target_include_directories(pybscalarpressure
PRIVATE pybind_include_directories
)

target_include_directories(pybBioGearsEngine PRIVATE pybind_include_directories)
target_include_directories(pybBioGearsEngineHeader PRIVATE pybind_include_directories)



TARGET_LINK_LIBRARIES(pybcardio PRIVATE python3.8)
target_link_libraries(pybcardio PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears python3.8)

TARGET_LINK_LIBRARIES(pyblogger PRIVATE python3.8)
target_link_libraries(pyblogger PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears python3.8)

TARGET_LINK_LIBRARIES(pybscalarpressure PRIVATE python3.8)
target_link_libraries(pybscalarpressure PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears python3.8)

TARGET_LINK_LIBRARIES(pybBioGearsEngine PRIVATE python3.8)
target_link_libraries(pybBioGearsEngine PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybBioGearsEngineHeader PRIVATE python3.8)
target_link_libraries(pybBioGearsEngineHeader PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)
