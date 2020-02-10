project(
	'myproject', # название проекта
	'cpp', # язык
	version: '0.1.0', # версия кода
	meson_version: '>=0.45', # минимально поддерживаемая версия Meson
	default_options: ['cpp_std=c++11'] # используемый стандарт C++
)
subdir('src')

doxygen = find_program('doxygen')
if doxygen.found()
    run_target('doc', command: [doxygen])
endif
