# find pandoc to convert md to html
find_program(PANDOC_EXECUTABLE pandoc)
if(NOT PANDOC_EXECUTABLE)
  message(FATAL_ERROR "pandoc executable not found.")
endif()

# Convert markdown files to a simple html page params-in: TARGETNAME        the name of the custom target params-in: PANDOC_ARGUMENTS  additional comandline arguments to pandoc params-in: LIST_MD_FILES     a list of markdown files relative to the current source dir
#
# Example usage: include(pandoc-helper) set(doc_resources index.md example.md)
#
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/style.css ${CMAKE_CURRENT_BINARY_DIR}/style.css COPYONLY) covert_md_to_html(mytarget "--css=style.css --include-after-body=${CMAKE_CURRENT_SOURCE_DIR}/resources/footer.html" "${doc_resources}") add_dependencies(doc mytarget)
function(covert_md_to_html TARGETNAME PANDOC_ARGUMENTS LIST_MD_FILES)
  separate_arguments(PANDOC_ARGUMENTS UNIX_COMMAND "${PANDOC_ARGUMENTS}")

  set(PANDOC_DOC_INCLUDE_DEPENDS)
  foreach(doc ${LIST_MD_FILES})
    string(REPLACE ".md" "" name ${doc})

    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${name}.html COMMAND ${PANDOC_EXECUTABLE} ${PANDOC_ARGUMENTS} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.md -o ${CMAKE_CURRENT_BINARY_DIR}/${name}.html MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${name}.md COMMENT "Generating ${CMAKE_CURRENT_SOURCE_DIR}/${name}.md as ${CMAKE_CURRENT_BINARY_DIR}/${name}.html")
    list(APPEND PANDOC_DOC_INCLUDE_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${name}.html)
  endforeach()

  add_custom_target(${TARGETNAME} DEPENDS ${PANDOC_DOC_INCLUDE_DEPENDS})
endfunction()
