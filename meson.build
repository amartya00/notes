project('sigabrt.io.notes', 'cpp',
        license: 'GPLV2')

add_global_arguments('--std=c++17', '-Werror', language : 'cpp')


inc = include_directories('headers')

qt5 = import('qt5')
qt5_deps = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'Sql'])

preprocessed = qt5.preprocess(
    moc_headers : [
        'headers/ui/wordprocessor.hpp',
        'headers/ui/notesidebar.hpp'
    ],
    qresources: 'resources.qrc'
)

subdir('headers')
subdir('lib')
subdir('src')




