project('sigabrt.io.notes', 'cpp',
        license: 'GPLV2')

qt5 = import('qt5')
qt5_deps = dependency('qt5', modules: ['Core', 'Gui', 'Widgets'])

inc = include_directories('headers')

preprocessed = qt5.preprocess(qresources: 'resources.qrc')

subdir('headers')
subdir('src')
subdir('lib')



