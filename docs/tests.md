# Сборка тестов

Пример включение теста из файла `tests/GraphTarjansBridges_tests/empty_graph_test.cpp` 
в сборку осуществляется следующими командами в файле `CMakeLists.txt`:

```
add_executable(empty_graph_test tests/GraphTarjansBridges_tests/empty_graph_test.cpp)   # Добавить исполняемую цель
target_link_libraries(empty_graph_test graphlib)    # Подключить библиотеку с графом
add_test(EmptyGraphTest empty_graph_test)           # Собственно, добавить тест
```

`empty_graph_test` - имя цели сборки (можно выбрать любым);
`EmptyGraphTest` - имя теста, которое будет отображаться при запуске тестирования (в принципе, тоже может быть любым, но лучше осмысленным)


Для более навороченных вариантов тестирования (добавление свойств, например), лучше погуглить.

# Запуск тестов

Для запуска в CLion нужно нажать Run->Run->All CTest.

Также можно запустить и из консоли:
```bash
cd cmake-build-debug
ctest .
```

Но оно не запуститься если в папке `cmake-build-debug` нет следующих файлов (ну у меня по крайней мере):
```
libgcc_s_seh-1.dll
libstdc++-6.dll
libwinpthread-1.dll
```