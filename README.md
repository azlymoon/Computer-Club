# Компьютерный клуб

В проекте реализован симулятор компьютерного клуба. Реализованы механизмы прихода/ухода посетителей, очередь за игровой стол, подсчет выручки в конце дня и подсчет занятости по времени каждого из столов. 

## Сборка проекта 

```sh
mkdir build
cd build
cmake ..
make
```

## Запуск 

```sh
# /your_dir/Computer-Club/build
./ComputerClub <input_file>
```

Пример входных данных из задания лежит в `/sample_input/example_input.txt`

## Запуск тестов

```sh
# /your_dir/Computer-Club/build
ctest
```



