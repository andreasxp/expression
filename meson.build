project('expression', 'cpp',
	default_options: ['cpp_std=c++2a'])

if meson.get_compiler('cpp').get_id() == 'clang'
  add_global_arguments('-fdiagnostics-absolute-paths', language : 'cpp')
endif

source_dir = include_directories('src')
executable('program', 'src/main.cpp', include_directories: source_dir, install: true)
