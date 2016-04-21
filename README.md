# Глава 1 (Системное программирование в UNIX. Общие сведения)

- Вычислительная система состоит из нескольких типов ресурсов (дисковая память, оперативная память, периферийные устройства и сетевые средства). Программы используют эти ресурсы для хранения, пересылки и обработки данных
- Ядро UNIX представляет собой программу, которая планирует исполнение программ и управляет доступом к ресурсам
- пользовательские программы обращаются к ядру за ресурсами

# Глава 2 (Пользователи, файлы и справочник)
- основные функции для работы с файлами: open(filename, how), creat(filename, mode), read(fd, buffer, amt), write(fd, buffer, amt), lseek(fd, distance, base), close(fd)
- каждый раз, когда выполняется системный вызов, программа переходит в режим ядра
- файловый дескриптор определяет связь между процессом и файлом
- можно сократить число системных вызовов, используя программные буферы
	 