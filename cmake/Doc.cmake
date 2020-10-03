#
# SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
# License details at <https://github.com/kashirin-alex/swc-db/#license>

if(SWC_DOCUMENTATION) 

  find_package(Doxygen REQUIRED)

  execute_process(COMMAND mkdir -p ${CMAKE_BINARY_DIR}/doc/cpp/ )
  configure_file(${CMAKE_MODULE_PATH}/Doxyfile-cpp.doxy ${CMAKE_CURRENT_BINARY_DIR} @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-cpp.doxy)



  if(THRIFT_COMPILER_FOUND)

    add_custom_target(doc_thrift_html thrift -gen html
                      -o ${CMAKE_CURRENT_BINARY_DIR}/doc
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/thrift/swcdb/Service.thrift)
    add_custom_command(TARGET doc POST_BUILD COMMAND make doc_thrift_html)

    ## require - thrift t_markdown_generator
    #   https://github.com/apache/thrift/commit/330482b02e14955b7a760c59214de3e1b6d03dce
    ## add_custom_target(doc_thrift_md thrift -gen markdown:suffix=md
    ##                   -o ${CMAKE_CURRENT_BINARY_DIR}/doc
    ##                   ${CMAKE_CURRENT_SOURCE_DIR}/src/thrift/swcdb/Service.thrift)
    ## add_custom_command(TARGET doc POST_BUILD COMMAND make doc_thrift_md)

  endif ()


  add_custom_command(TARGET doc POST_BUILD COMMAND 
                     XZ_OPT=-e9 tar -cJf swc-db-doc-cpp-html.tar.xz doc/cpp/html/* )

  # add_custom_command(TARGET doc POST_BUILD COMMAND 
  #                   XZ_OPT=-e9 tar -cJf swc-db-thirft-html.tar.xz doc/gen-html/* )


endif ()