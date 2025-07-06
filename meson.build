project(
  'c-opengl-test',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.0.1',
  default_options : ['warning_level=3','c_std=c23'],
)

exe = executable(
  'main',
  [
    'src/main.c',
    'src/glad/glad.c',
    'src/shader.c',
  ],
  include_directories: include_directories('includes'),
  dependencies: [
    meson.get_compiler('c').find_library('glfw3dll', dirs: [meson.project_source_root() / 'lib'], required: true)
  ],
  install : true,
)

test('basic', exe)

configure_file(
  input: 'lib/glfw3.dll',
  output: 'glfw3.dll',
  copy: true
)

subdir('shaders')