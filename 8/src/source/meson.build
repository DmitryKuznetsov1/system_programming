myproject_src = files([
	'main.cpp',
	'MergeSort.h',
	'MergeSortThreads.h'
])


threads = dependency('threads')

executable(
	'myproject', # название исполняемого файла
	include_directories: src, # где ищутся заголовочные файлы
	sources: myproject_src, # список исходный файлов
	dependencies: [threads], # зависимости проекта (если имеются)
	install: true # устанавливать ли файл
)

