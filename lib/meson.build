backend_files = [
    'backend/notesdao.cc'
]

backend_lib = static_library(
    'backend',
    backend_files,
    include_directories: inc,
    dependencies: qt5_deps
)

ui_files = [
    'ui/actionbay.cc',
    'ui/wordprocessor.cc',
    'ui/notesmainwindow.cc',
    'ui/textbox.cc',
    'ui/itemlist.cc',
    'ui/notesidebar.cc'
]

ui_lib = static_library(
    'ui',
    ui_files,
    include_directories: inc,
    dependencies: qt5_deps
)
