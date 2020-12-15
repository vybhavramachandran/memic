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
pybind11_add_module(pybLogger ./libBiogears/src/pybwrappers/cdm/utils/pybLogger.cpp)
pybind11_add_module(pybscalarpressure ./libBiogears/src/pybscalarpressure.cpp)
pybind11_add_module(pybBioGearsEngine ./libBiogears/src/pybwrappers/engine/Controller/pybBioGearsEngine.cpp)
pybind11_add_module(pybBioGearsEngineHeader ./libBiogears/src/pybwrappers/engine/Controller/pybBioGearsEngineHeader.cpp)
pybind11_add_module(pybPhysiologyEngineTrack ./libBiogears/src/pybwrappers/cdm/engine/pybPhysiologyEngineTrack.cpp)
pybind11_add_module(pybSEDataRequestManager ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEDataRequestManager.cpp)
pybind11_add_module(pybSEDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEDataRequest.cpp)
pybind11_add_module(pybSEPhysiologyDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEPhysiologyDataRequest.cpp)
pybind11_add_module(pybSEAsthmaAttack ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEAsthmaAttack.cpp)
pybind11_add_module(pybSEScalar0To1 ./libBiogears/src/pybwrappers/cdm/properties/pybSEScalar0To1.cpp)
pybind11_add_module(pybSEBurnWound ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEBurnWound.cpp)
pybind11_add_module(pybSEAcuteRespiratoryDistress ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEAcuteRespiratoryDistress.cpp)
pybind11_add_module(pybSEBreathHold ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEBreathHold.cpp)
pybind11_add_module(pybSEBronchoconstriction ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEBronchoconstriction.cpp)
pybind11_add_module(pybSECardiacArrest ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSECardiacArrest.cpp)
pybind11_add_module(pybSEChestCompressionForce ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEChestCompressionForce.cpp)
pybind11_add_module(pybSEAcuteStress ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEAcuteStress.cpp)
pybind11_add_module(pybSEBrainInjury ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEBrainInjury.cpp)
pybind11_add_module(pybSEApnea ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEApnea.cpp)
pybind11_add_module(pybSEAirwayObstruction ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEAirwayObstruction.cpp)
pybind11_add_module(pybSEChestCompressionForceScale ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEChestCompressionForceScale.cpp)
pybind11_add_module(pybSEChestOcclusiveDressing ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEChestOcclusiveDressing.cpp)
pybind11_add_module(pybSEConsciousRespiration ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEConsciousRespiration.cpp)
pybind11_add_module(pybSEConsumeNutrients ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEConsumeNutrients.cpp)
pybind11_add_module(pybSEExercise ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEExercise.cpp)
pybind11_add_module(pybSEForcedExhale ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEForcedExhale.cpp)
pybind11_add_module(pybSEForcedInhale ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEForcedInhale.cpp)
pybind11_add_module(pybSEHemorrhage ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEHemmorrhage.cpp)
pybind11_add_module(pybSEInfection ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEInfection.cpp)
pybind11_add_module(pybSEIntubation ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEIntubation.cpp)
pybind11_add_module(pybSEMechanicalVentilation ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEMechanicalVentilation.cpp)
pybind11_add_module(pybSENeedleDecompression ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSENeedleDecompression.cpp)
pybind11_add_module(pybSEOverride ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEOverride.cpp)
pybind11_add_module(pybSEPainStimulus ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEPainStimulus.cpp)
# pybind11_add_module(pybSEPatientAction ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEPatientAction.cpp)
pybind11_add_module(pybSEPatientAssessmentRequest ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEPatientAssessmentRequest.cpp)
pybind11_add_module(pybSEPericardialEffusion ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEPericardialEffusion.cpp)
pybind11_add_module(pybSEPupillaryResponse ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEPupillaryResponse.cpp)
pybind11_add_module(pybSESleep ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESleep.cpp)
# pybind11_add_module(pybSESubstanceAdministration ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESubstanceAdministration.cpp)
pybind11_add_module(pybSESubstanceBolus ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESubstanceBolus.cpp)
pybind11_add_module(pybSESubstanceCompoundInfusion ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESubstanceCompoundInfusion.cpp)
pybind11_add_module(pybSESubstanceInfusion ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESubstanceInfusion.cpp)
pybind11_add_module(pybSESubstanceNasalDose ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESubstanceNasalDose.cpp)
pybind11_add_module(pybSESubstanceOralDose ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSESubstanceOralDose.cpp)
pybind11_add_module(pybSETensionPneumothroax ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSETensionPneumothroax.cpp)
pybind11_add_module(pybSETourniquet ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSETourniquet.cpp)
pybind11_add_module(pybSEUrinate ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEUrinate.cpp)
pybind11_add_module(pybSEUseInhaler ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEUseInhaler.cpp)
pybind11_add_module(pybSECompleteBloodCount ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSECompleteBloodCount.cpp)
pybind11_add_module(pybSEComprehensiveMetabolicPanel ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSEComprehensiveMetabolicPanel.cpp)
# pybind11_add_module(pybSEPsychomotorVigilanceTask ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSEPsychomotorVigilanceTask.cpp)
pybind11_add_module(pybSEPulmonaryFunctionTest ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSEPulmonaryFunctionTest.cpp)
pybind11_add_module(pybSESequentialOrganFailureAssessment ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSESequentialOrganFailureAssessment.cpp)
pybind11_add_module(pybSEUrinalysis ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSEUrinalysis.cpp)
pybind11_add_module(pybSEUrinalysisMicroscopic ./libBiogears/src/pybwrappers/cdm/patient/assessments/pybSEUrinalysisMicroscopic.cpp)
pybind11_add_module(pybSEChronicAnemia ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEChronicAnemia.cpp)
pybind11_add_module(pybSEChronicObstructivePulmonaryDisease ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEChronicObstructivePulmonaryDisease.cpp)
pybind11_add_module(pybSEChronicPericardialEffusion ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEChronicPericardialEffusion.cpp)
pybind11_add_module(pybSEChronicRenalStenosis ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEChronicRenalStenosis.cpp)
pybind11_add_module(pybSEChronicVentricularSystolicDysfunction ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEChronicVentricularSystolicDysfunction.cpp)
pybind11_add_module(pybSEDehydration ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEDehydration.cpp)
pybind11_add_module(pybSEDiabetesType1 ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEDiabetesType1.cpp)
pybind11_add_module(pybSEDiabetesType2 ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEDiabetesType2.cpp)
pybind11_add_module(pybSEImpairedAlveolarExchange ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEImpairedAlveolarExchange.cpp)
pybind11_add_module(pybSELobarPneumonia ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSELobarPneumonia.cpp)
pybind11_add_module(pybSEStarvation ./libBiogears/src/pybwrappers/cdm/patient/conditions/pybSEStarvation.cpp)
pybind11_add_module(pybSENutrition ./libBiogears/src/pybwrappers/cdm/patient/pybSENutrition.cpp)
pybind11_add_module(pybSEPatient ./libBiogears/src/pybwrappers/cdm/patient/pybSEPatient.cpp)
pybind11_add_module(pybSECompartmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSECompartmentDataRequest.cpp)
pybind11_add_module(pybSECompartmentSubstanceDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSECompartmentSubstanceDataRequest.cpp)
pybind11_add_module(pybSEEnvironmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEEnvironmentDataRequest.cpp)
pybind11_add_module(pybSEEquipmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEEquipmentDataRequest.cpp)
pybind11_add_module(pybSEGasCompartmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEGasCompartmentDataRequest.cpp)
pybind11_add_module(pybSELiquidCompartmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSELiquidCompartmentDataRequest.cpp)
pybind11_add_module(pybSEPatientDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEPatientDataRequest.cpp)
pybind11_add_module(pybSESubstanceDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSESubstanceDataRequest.cpp)
pybind11_add_module(pybSEThermalCompartmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSEThermalCompartmentDataRequest.cpp)
pybind11_add_module(pybSETissueCompartmentDataRequest ./libBiogears/src/pybwrappers/cdm/scenario/requests/pybSETissueCompartmentDataRequest.cpp)
pybind11_add_module(pybSEActionManager ./libBiogears/src/pybwrappers/cdm/scenario/pybSEActionManager.cpp)
pybind11_add_module(pybSEAdvanceTime ./libBiogears/src/pybwrappers/cdm/scenario/pybSEAdvanceTime.cpp)
pybind11_add_module(pybSEAnesthesiaMachineActionCollection ./libBiogears/src/pybwrappers/cdm/scenario/pybSEAnesthesiaMachineActionCollection.cpp)
pybind11_add_module(pybSEConditionManager ./libBiogears/src/pybwrappers/cdm/scenario/pybSEConditionManager.cpp)
pybind11_add_module(pybSEEnvironmentActionCollection ./libBiogears/src/pybwrappers/cdm/scenario/pybSEEnvironmentActionCollection.cpp)
pybind11_add_module(pybSEInhalerActionCollection ./libBiogears/src/pybwrappers/cdm/scenario/pybSEInhalerActionCollection.cpp)
pybind11_add_module(pybSEPatientActionCollection /opt/biogears/core/projects/biogears/libBiogears/src/pybwrappers/cdm/scenario/pybSEPatientActionCollection.cpp)
pybind11_add_module(pybSEScenario ./libBiogears/src/pybwrappers/cdm/scenario/pybSEScenario.cpp)
pybind11_add_module(pybSEScenarioAutoSerialization ./libBiogears/src/pybwrappers/cdm/scenario/pybSEScenarioAutoSerialization.cpp)
pybind11_add_module(pybSEScenarioExec ./libBiogears/src/pybwrappers/cdm/scenario/pybSEScenarioExec.cpp)
pybind11_add_module(pybSEScenarioInitialParameters ./libBiogears/src/pybwrappers/cdm/scenario/pybSEScenarioInitialParameters.cpp)
pybind11_add_module(pybSESerializeState ./libBiogears/src/pybwrappers/cdm/scenario/pybSESerializeState.cpp)
pybind11_add_module(pybSESubstance ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstance.cpp)
pybind11_add_module(pybSESubstanceAerosolization ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstanceAerosolization.cpp)
pybind11_add_module(pybSESubstanceClearance ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstanceClearance.cpp)
pybind11_add_module(pybSESubstanceCompound ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstanceCompound.cpp)
pybind11_add_module(pybSESubstanceConcentration ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstanceConcentration.cpp)
pybind11_add_module(pybSESubstanceFraction ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstanceFraction.cpp)
pybind11_add_module(pybSESubstancePharmacodynamics ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstancePharmacodynamics.cpp)
pybind11_add_module(pybSESubstancePharmacokinetics ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstancePharmacokinetics.cpp)
pybind11_add_module(pybSESubstancePhysicochemicals ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstancePhysicochemicals.cpp)
pybind11_add_module(pybSESubstanceTissuePharmacokinetics ./libBiogears/src/pybwrappers/cdm/substance/pybSESubstanceTissuePharmacokinetics.cpp)
# pybind11_add_module(pybSEBloodChemistrySystem ./libBiogears/src/pybwrappers/cdm/system/physiology/pybSEBloodChemistrySystem.cpp)
pybind11_add_module(pybSECardiovascularSystem ./libBiogears/src/pybwrappers/cdm/system/physiology/pybSECardiovascularSystem.cpp)
pybind11_add_module(pybSEPatientAction ./libBiogears/src/pybwrappers/cdm/patient/actions/pybSEPatientAction.cpp)
pybind11_add_module(pybSEAction ./libBiogears/src/pybwrappers/cdm/scenario/pybSEAction.cpp)
pybind11_add_module(pybSESystem ./libBiogears/src/pybwrappers/cdm/system/pybSESystem.cpp)

set(pybind_include_directories /usr/include/python3.8 /home/vybhav/anaconda3/include/python3.8 /home/vybhav/Downloads/pybind11/include /opt/biogears/core/build/../projects/biogears/libCDM/include /opt/biogears/core/build/../build/projects/biogears /opt/biogears/core/projects/biogears/libBiogears/include  /opt/biogears/core/projects/biogears-common/include /opt/biogears/core/build/projects/biogears/biogears/schema /opt/biogears/core/projects/biogears/libBiogears/include/biogears/cdm/engine/)

target_include_directories(pybcardio
PRIVATE pybind_include_directories
)
target_include_directories(pybLogger
PRIVATE pybind_include_directories
)
target_include_directories(pybscalarpressure
PRIVATE pybind_include_directories
)

target_include_directories(pybBioGearsEngine PRIVATE pybind_include_directories)
target_include_directories(pybBioGearsEngineHeader PRIVATE pybind_include_directories)
target_include_directories(pybPhysiologyEngineTrack PRIVATE pybind_include_directories)
target_include_directories(pybSEDataRequestManager PRIVATE pybind_include_directories)
target_include_directories(pybSEDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEPhysiologyDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEAsthmaAttack PRIVATE pybind_include_directories)
target_include_directories(pybSEScalar0To1 PRIVATE pybind_include_directories)
target_include_directories(pybSEBurnWound PRIVATE pybind_include_directories)
target_include_directories(pybSEAcuteRespiratoryDistress PRIVATE pybind_include_directories)
target_include_directories(pybSEBreathHold PRIVATE pybind_include_directories)
target_include_directories(pybSEBronchoconstriction PRIVATE pybind_include_directories)
target_include_directories(pybSECardiacArrest PRIVATE pybind_include_directories)
target_include_directories(pybSEChestCompressionForce PRIVATE pybind_include_directories)
target_include_directories(pybSEAcuteStress PRIVATE pybind_include_directories)
target_include_directories(pybSEBrainInjury PRIVATE pybind_include_directories)
target_include_directories(pybSEApnea PRIVATE pybind_include_directories)
target_include_directories(pybSEAirwayObstruction PRIVATE pybind_include_directories)
target_include_directories(pybSEChestCompressionForceScale PRIVATE pybind_include_directories)
target_include_directories(pybSEChestOcclusiveDressing PRIVATE pybind_include_directories)
target_include_directories(pybSEConsciousRespiration PRIVATE pybind_include_directories)
target_include_directories(pybSEConsumeNutrients PRIVATE pybind_include_directories)
target_include_directories(pybSEExercise PRIVATE pybind_include_directories)
target_include_directories(pybSEForcedExhale PRIVATE pybind_include_directories)
target_include_directories(pybSEForcedInhale PRIVATE pybind_include_directories)
target_include_directories(pybSEHemorrhage PRIVATE pybind_include_directories)
target_include_directories(pybSEInfection PRIVATE pybind_include_directories)
target_include_directories(pybSEIntubation PRIVATE pybind_include_directories)
target_include_directories(pybSEMechanicalVentilation PRIVATE pybind_include_directories)
target_include_directories(pybSENeedleDecompression PRIVATE pybind_include_directories)
target_include_directories(pybSEOverride PRIVATE pybind_include_directories)
target_include_directories(pybSEPainStimulus PRIVATE pybind_include_directories)
# target_include_directories(pybSEPatientAction PRIVATE pybind_include_directories)
target_include_directories(pybSEPatientAssessmentRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEPericardialEffusion PRIVATE pybind_include_directories)
target_include_directories(pybSEPupillaryResponse PRIVATE pybind_include_directories)
target_include_directories(pybSESleep PRIVATE pybind_include_directories)
# target_include_directories(pybSESubstanceAdministration PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceBolus PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceCompoundInfusion PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceInfusion PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceNasalDose PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceOralDose PRIVATE pybind_include_directories)
target_include_directories(pybSETensionPneumothroax PRIVATE pybind_include_directories)
target_include_directories(pybSETourniquet PRIVATE pybind_include_directories)
target_include_directories(pybSEUrinate PRIVATE pybind_include_directories)
target_include_directories(pybSEUseInhaler PRIVATE pybind_include_directories)
target_include_directories(pybSECompleteBloodCount PRIVATE pybind_include_directories)
target_include_directories(pybSEComprehensiveMetabolicPanel PRIVATE pybind_include_directories)
# target_include_directories(pybSEPsychomotorVigilanceTask PRIVATE pybind_include_directories)
target_include_directories(pybSEPulmonaryFunctionTest PRIVATE pybind_include_directories)
target_include_directories(pybSESequentialOrganFailureAssessment PRIVATE pybind_include_directories)
target_include_directories(pybSEUrinalysis PRIVATE pybind_include_directories)
target_include_directories(pybSEUrinalysisMicroscopic PRIVATE pybind_include_directories)
target_include_directories(pybSEChronicAnemia PRIVATE pybind_include_directories)
target_include_directories(pybSEChronicObstructivePulmonaryDisease PRIVATE pybind_include_directories)
target_include_directories(pybSEChronicPericardialEffusion PRIVATE pybind_include_directories)
target_include_directories(pybSEChronicRenalStenosis PRIVATE pybind_include_directories)
target_include_directories(pybSEChronicVentricularSystolicDysfunction PRIVATE pybind_include_directories)
target_include_directories(pybSEDehydration PRIVATE pybind_include_directories)
target_include_directories(pybSEDiabetesType1 PRIVATE pybind_include_directories)
target_include_directories(pybSEDiabetesType2 PRIVATE pybind_include_directories)
target_include_directories(pybSEImpairedAlveolarExchange PRIVATE pybind_include_directories)
target_include_directories(pybSELobarPneumonia PRIVATE pybind_include_directories)
target_include_directories(pybSEStarvation PRIVATE pybind_include_directories)
target_include_directories(pybSENutrition PRIVATE pybind_include_directories)
target_include_directories(pybSEPatient PRIVATE pybind_include_directories)
target_include_directories(pybSECompartmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSECompartmentSubstanceDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEEnvironmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEEquipmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEGasCompartmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSELiquidCompartmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEPatientDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEThermalCompartmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSETissueCompartmentDataRequest PRIVATE pybind_include_directories)
target_include_directories(pybSEActionManager PRIVATE pybind_include_directories)
target_include_directories(pybSEAdvanceTime PRIVATE pybind_include_directories)
target_include_directories(pybSEAnesthesiaMachineActionCollection PRIVATE pybind_include_directories)
target_include_directories(pybSEConditionManager PRIVATE pybind_include_directories)
target_include_directories(pybSEEnvironmentActionCollection PRIVATE pybind_include_directories)
target_include_directories(pybSEInhalerActionCollection PRIVATE pybind_include_directories)
target_include_directories(pybSEPatientActionCollection PRIVATE pybind_include_directories)
target_include_directories(pybSEScenario PRIVATE pybind_include_directories)
target_include_directories(pybSEScenarioAutoSerialization PRIVATE pybind_include_directories)
target_include_directories(pybSEScenarioExec PRIVATE pybind_include_directories)
target_include_directories(pybSEScenarioInitialParameters PRIVATE pybind_include_directories)
target_include_directories(pybSESerializeState PRIVATE pybind_include_directories)
target_include_directories(pybSESubstance PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceAerosolization PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceClearance PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceCompound PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceConcentration PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceFraction PRIVATE pybind_include_directories)
target_include_directories(pybSESubstancePharmacodynamics PRIVATE pybind_include_directories)
target_include_directories(pybSESubstancePharmacokinetics PRIVATE pybind_include_directories)
target_include_directories(pybSESubstancePhysicochemicals PRIVATE pybind_include_directories)
target_include_directories(pybSESubstanceTissuePharmacokinetics PRIVATE pybind_include_directories)
# target_include_directories(pybSEBloodChemistrySystem PRIVATE pybind_include_directories)
target_include_directories(pybSECardiovascularSystem PRIVATE pybind_include_directories)
target_include_directories(pybSEPatientAction PRIVATE pybind_include_directories)
target_include_directories(pybSEAction PRIVATE pybind_include_directories)
target_include_directories(pybSESystem PRIVATE pybind_include_directories)

TARGET_LINK_LIBRARIES(pybcardio PRIVATE python3.8)
target_link_libraries(pybcardio PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears python3.8)

TARGET_LINK_LIBRARIES(pybLogger PRIVATE python3.8)
target_link_libraries(pybLogger PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears python3.8)

TARGET_LINK_LIBRARIES(pybscalarpressure PRIVATE python3.8)
target_link_libraries(pybscalarpressure PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears python3.8)

TARGET_LINK_LIBRARIES(pybBioGearsEngine PRIVATE python3.8)
target_link_libraries(pybBioGearsEngine PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybBioGearsEngineHeader PRIVATE python3.8)
target_link_libraries(pybBioGearsEngineHeader PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybPhysiologyEngineTrack PRIVATE python3.8)
target_link_libraries(pybPhysiologyEngineTrack PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEDataRequestManager PRIVATE python3.8)
target_link_libraries(pybSEDataRequestManager PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEDataRequest PRIVATE python3.8)
target_link_libraries(pybSEDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPhysiologyDataRequest PRIVATE python3.8)
target_link_libraries(pybSEPhysiologyDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAsthmaAttack PRIVATE python3.8)
target_link_libraries(pybSEAsthmaAttack PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEScalar0To1 PRIVATE python3.8)
target_link_libraries(pybSEScalar0To1 PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEBurnWound PRIVATE python3.8)
target_link_libraries(pybSEBurnWound PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAcuteRespiratoryDistress PRIVATE python3.8)
target_link_libraries(pybSEAcuteRespiratoryDistress PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEBreathHold PRIVATE python3.8)
target_link_libraries(pybSEBreathHold PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEBronchoconstriction PRIVATE python3.8)
target_link_libraries(pybSEBronchoconstriction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSECardiacArrest PRIVATE python3.8)
target_link_libraries(pybSECardiacArrest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChestCompressionForce PRIVATE python3.8)
target_link_libraries(pybSEChestCompressionForce PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAcuteStress PRIVATE python3.8)
target_link_libraries(pybSEAcuteStress PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEBrainInjury PRIVATE python3.8)
target_link_libraries(pybSEBrainInjury PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEApnea PRIVATE python3.8)
target_link_libraries(pybSEApnea PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAirwayObstruction PRIVATE python3.8)
target_link_libraries(pybSEAirwayObstruction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChestCompressionForceScale PRIVATE python3.8)
target_link_libraries(pybSEChestCompressionForceScale PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChestOcclusiveDressing PRIVATE python3.8)
target_link_libraries(pybSEChestOcclusiveDressing PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEConsciousRespiration PRIVATE python3.8)
target_link_libraries(pybSEConsciousRespiration PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEConsumeNutrients PRIVATE python3.8)
target_link_libraries(pybSEConsumeNutrients PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEExercise PRIVATE python3.8)
target_link_libraries(pybSEExercise PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEForcedExhale PRIVATE python3.8)
target_link_libraries(pybSEForcedExhale PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEForcedInhale PRIVATE python3.8)
target_link_libraries(pybSEForcedInhale PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSEHemorrhage PRIVATE python3.8)
target_link_libraries(pybSEHemorrhage PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEInfection PRIVATE python3.8)
target_link_libraries(pybSEInfection PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEIntubation PRIVATE python3.8)
target_link_libraries(pybSEIntubation PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEMechanicalVentilation PRIVATE python3.8)
target_link_libraries(pybSEMechanicalVentilation PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSENeedleDecompression PRIVATE python3.8)
target_link_libraries(pybSENeedleDecompression PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEOverride PRIVATE python3.8)
target_link_libraries(pybSEOverride PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPainStimulus PRIVATE python3.8)
target_link_libraries(pybSEPainStimulus PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

# TARGET_LINK_LIBRARIES(pybSEPatientAction PRIVATE python3.8)
# target_link_libraries(pybSEPatientAction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPatientAssessmentRequest PRIVATE python3.8)
target_link_libraries(pybSEPatientAssessmentRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPericardialEffusion PRIVATE python3.8)
target_link_libraries(pybSEPericardialEffusion PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPupillaryResponse PRIVATE python3.8)
target_link_libraries(pybSEPupillaryResponse PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESleep PRIVATE python3.8)
target_link_libraries(pybSESleep PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

# TARGET_LINK_LIBRARIES(pybSESubstanceAdministration PRIVATE python3.8)
# target_link_libraries(pybSESubstanceAdministration PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceBolus PRIVATE python3.8)
target_link_libraries(pybSESubstanceBolus PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceCompoundInfusion PRIVATE python3.8)
target_link_libraries(pybSESubstanceCompoundInfusion PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceInfusion PRIVATE python3.8)
target_link_libraries(pybSESubstanceInfusion PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceNasalDose PRIVATE python3.8)
target_link_libraries(pybSESubstanceNasalDose PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceOralDose PRIVATE python3.8)
target_link_libraries(pybSESubstanceOralDose PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSETensionPneumothroax PRIVATE python3.8)
target_link_libraries(pybSETensionPneumothroax PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSETourniquet PRIVATE python3.8)
target_link_libraries(pybSETourniquet PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEUrinate PRIVATE python3.8)
target_link_libraries(pybSEUrinate PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEUseInhaler PRIVATE python3.8)
target_link_libraries(pybSEUseInhaler PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSECompleteBloodCount PRIVATE python3.8)
target_link_libraries(pybSECompleteBloodCount PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEComprehensiveMetabolicPanel PRIVATE python3.8)
target_link_libraries(pybSEComprehensiveMetabolicPanel PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

# TARGET_LINK_LIBRARIES(pybSEPsychomotorVigilanceTask PRIVATE python3.8)
# target_link_libraries(pybSEPsychomotorVigilanceTask PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPulmonaryFunctionTest PRIVATE python3.8)
target_link_libraries(pybSEPulmonaryFunctionTest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESequentialOrganFailureAssessment PRIVATE python3.8)
target_link_libraries(pybSESequentialOrganFailureAssessment PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEUrinalysis PRIVATE python3.8)
target_link_libraries(pybSEUrinalysis PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEUrinalysisMicroscopic PRIVATE python3.8)
target_link_libraries(pybSEUrinalysisMicroscopic PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChronicAnemia PRIVATE python3.8)
target_link_libraries(pybSEChronicAnemia PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChronicObstructivePulmonaryDisease PRIVATE python3.8)
target_link_libraries(pybSEChronicObstructivePulmonaryDisease PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChronicPericardialEffusion PRIVATE python3.8)
target_link_libraries(pybSEChronicPericardialEffusion PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChronicRenalStenosis PRIVATE python3.8)
target_link_libraries(pybSEChronicRenalStenosis PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEChronicVentricularSystolicDysfunction PRIVATE python3.8)
target_link_libraries(pybSEChronicVentricularSystolicDysfunction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEDehydration PRIVATE python3.8)
target_link_libraries(pybSEDehydration PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEDiabetesType1 PRIVATE python3.8)
target_link_libraries(pybSEDiabetesType1 PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEDiabetesType2 PRIVATE python3.8)
target_link_libraries(pybSEDiabetesType2 PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEImpairedAlveolarExchange PRIVATE python3.8)
target_link_libraries(pybSEImpairedAlveolarExchange PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSELobarPneumonia PRIVATE python3.8)
target_link_libraries(pybSELobarPneumonia PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEStarvation PRIVATE python3.8)
target_link_libraries(pybSEStarvation PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSENutrition PRIVATE python3.8)
target_link_libraries(pybSENutrition PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPatient PRIVATE python3.8)
target_link_libraries(pybSEPatient PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSECompartmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSECompartmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSECompartmentSubstanceDataRequest PRIVATE python3.8)
target_link_libraries(pybSECompartmentSubstanceDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEEnvironmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSEEnvironmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEEquipmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSEEquipmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEGasCompartmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSEGasCompartmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSELiquidCompartmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSELiquidCompartmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPatientDataRequest PRIVATE python3.8)
target_link_libraries(pybSEPatientDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceDataRequest PRIVATE python3.8)
target_link_libraries(pybSESubstanceDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEThermalCompartmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSEThermalCompartmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSETissueCompartmentDataRequest PRIVATE python3.8)
target_link_libraries(pybSETissueCompartmentDataRequest PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEActionManager PRIVATE python3.8)
target_link_libraries(pybSEActionManager PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAdvanceTime PRIVATE python3.8)
target_link_libraries(pybSEAdvanceTime PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAnesthesiaMachineActionCollection PRIVATE python3.8)
target_link_libraries(pybSEAnesthesiaMachineActionCollection PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSEConditionManager PRIVATE python3.8)
target_link_libraries(pybSEConditionManager PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)



TARGET_LINK_LIBRARIES(pybSEEnvironmentActionCollection PRIVATE python3.8)
target_link_libraries(pybSEEnvironmentActionCollection PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSEInhalerActionCollection PRIVATE python3.8)
target_link_libraries(pybSEInhalerActionCollection PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPatientActionCollection PRIVATE python3.8)
target_link_libraries(pybSEPatientActionCollection PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEScenario PRIVATE python3.8)
target_link_libraries(pybSEScenario PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEScenarioAutoSerialization PRIVATE python3.8)
target_link_libraries(pybSEScenarioAutoSerialization PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEScenarioExec PRIVATE python3.8)
target_link_libraries(pybSEScenarioExec PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEScenarioInitialParameters PRIVATE python3.8)
target_link_libraries(pybSEScenarioInitialParameters PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESerializeState PRIVATE python3.8)
target_link_libraries(pybSESerializeState PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstance PRIVATE python3.8)
target_link_libraries(pybSESubstance PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceAerosolization PRIVATE python3.8)
target_link_libraries(pybSESubstanceAerosolization PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceClearance PRIVATE python3.8)
target_link_libraries(pybSESubstanceClearance PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceCompound PRIVATE python3.8)
target_link_libraries(pybSESubstanceCompound PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceConcentration PRIVATE python3.8)
target_link_libraries(pybSESubstanceConcentration PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSESubstanceFraction PRIVATE python3.8)
target_link_libraries(pybSESubstanceFraction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSESubstancePharmacodynamics PRIVATE python3.8)
target_link_libraries(pybSESubstancePharmacodynamics PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSESubstancePharmacokinetics PRIVATE python3.8)
target_link_libraries(pybSESubstancePharmacokinetics PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSESubstancePhysicochemicals PRIVATE python3.8)
target_link_libraries(pybSESubstancePhysicochemicals PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSESubstanceTissuePharmacokinetics PRIVATE python3.8)
target_link_libraries(pybSESubstanceTissuePharmacokinetics PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

# TARGET_LINK_LIBRARIES(pybSEBloodChemistrySystem PRIVATE python3.8)
# target_link_libraries(pybSEBloodChemistrySystem PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSECardiovascularSystem PRIVATE python3.8)
target_link_libraries(pybSECardiovascularSystem PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEPatientAction PRIVATE python3.8)
target_link_libraries(pybSEPatientAction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)

TARGET_LINK_LIBRARIES(pybSEAction PRIVATE python3.8)
target_link_libraries(pybSEAction PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)


TARGET_LINK_LIBRARIES(pybSESystem PRIVATE python3.8)
target_link_libraries(pybSESystem PRIVATE pybind11::module pybind11::embed pybind11::lto libbiogears libbiogears_common python3.8)
