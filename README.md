# FileTracker
Лабораторная работа по предмету "Технология разработки программного обеспечения"

## Техническое задание
Написать программу для слежения за состоянием выбранного файла, использовать синглтон при реализации.

Ограничимся  двумя характеристиками:
1. Существует файл или нет;
2. Каков размер файла.

Программа будет выводить на консоль уведомление о произошедших изменениях в файле.
Существует несколько ситуаций для наблюдаемого файла

1. Файл существует , файл не  пустой - на экран выводится факт существования файла и его  размер.
2. Файл существует, файл был изменен - на экран выводится факт существования файла, сообщение о том что файл был изменен и его размер.  
3. Файл не существует - на экран выводится информация о том что файл не существует.

## Решение
Пусть будет 3 класса:
1) `ListFormer` — формирует список из указанного источника(в нашем случае файл);
2) `FileStatesTracker` — для пути к файлу(-ам) возвращает их состояние;
3) `FileStatesConsoleNotifier` — выводит в консоль полученную информацию о состоянии файла.

Взаимодействие классов:
1) Привязываем обработчики(слоты, в нашем случае - методы класса `FileStatesConsoleNotifier`) к событиям(получение сигналов, формируемые методами класса `FileStatesTracker`);
2) Привязываем к истечению таймера формированию списка путей к отслеживанию файлов(`ListFormer`) и получение сводки по ним(класс `FileStatesTracker`);
3) Каждые 5 секунд(время истечения таймера) неявно вызываются методы `ListFormer->formFromFile` и `FileStatesTracker->trackFromList`, притом на сформированные `FileStatesTracker` сигналы неявно вызываются методы `FileStatesConsoleNotifier`, выводящие сводку о файлах в консоль.  

## Реализация паттернов
В данном случае речь пойдет об антипаттерне *singleton*. Шаблон проектирования был реализован классом `FileStatesConsoleNotifier`:
1) Скрываем конструктор(делаем его `private`);
2) Делегируем слежение за экземляром объекта(так как он может быть только один) статической функции `getInstance`
Теперь в системе может существовать только один объект класса `FileStatesConsoleNotifier`, так как все переменные при присваивании вида `someVariable = FileStatesConsoleNotifier::getInstance()` получают ссылку на один и тот же объект.

## Тестирование и эксплуатация
1) В корне проекта в файл `filesList.txt` вписываем пути к файлам, *каждый файл на отдельной строке*. 
2) Переходим в папку `bin` и запускаем `FileTracker.exe`. Каждые 5 секунд будет выводиться сводка по файлам.
