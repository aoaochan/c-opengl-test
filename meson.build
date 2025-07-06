project(
  'c-opengl-test',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3','c_std=c23'],
)

compiler = meson.get_compiler('c')

project_include_dir = include_directories('includes')

exe = executable(
  'main',
  [
    'src/main.c',
    'src/glad/glad.c',
  ],
  include_directories: project_include_dir,
  dependencies: [
    compiler.find_library('glfw3dll', dirs: [meson.project_source_root() / 'lib'], required: true)
  ],
  install : true,
)

test('basic', exe)
