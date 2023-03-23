# Проверка файла на целостность
Требования: 
+ Компилятор: gcc;
+ Система сборки: make;
---
##### Взаимодействие с программой происходит путем передачи параметров командной строки программе.

```bash 
./prog_name file_name hash_value
```

Программа сравнивает хеш файла, который сама вычисляет и хеш, передаваемый в качестве аргумента.
Если они совпадают, то целостность файла сохранена.