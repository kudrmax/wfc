# Wave Function Collapse Simulation

![Function Collapse Simulation](images/wfc.gif)

## Описание

Это проект на `C++`, использующий библиотеку `SFML` для создания симуляции алгоритма Wave Function Collapse (WFC), который используется для создания уникальных случайно сгенерированных паттернов.

## Технологии

- `С++`
- `SFML`

## Установка

1. Убедитесь, что у вас установлен `C++` компилятор и `SFML` библиотека.
2. Клонируйте репозиторий:

   ```bash
   git clone https://github.com/your-username/fave-function-collapse.git
   ```

3. Перейдите в директорию проекта:

   ```bash
   cd fave-function-collapse
   ```

4. Соберите проект:

   ```bash
   g++ -o fave_function_collapse main.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

5. Запустите приложение:

   ```bash
   ./fave_function_collapse
   ```

## Использование

- Для запуска или паузы генерации нажмите `SPACE`. 
- Для сброса сгенерированного паттерна нажмите `R`.
- Для изменения настроек проекта редактируйте файл `config.h`.

## Конфигурация

Файл `config.h` содержит параметры для настройки генерации изображения. Вы можете настроить размер окна, количество фрагментов разбиения и выбрать изображения для генерации паттернов.

```c++
{
  "width": 800,
  "height": 600,
  "fragmentSize": 20,
  "numFragments": 100,
  "ruleSet": "default",
  "outputFile": "output.png"
}
```

## Пример

![Function Collapse Example](images/example.png)

## Лицензия

Этот проект распространяется под лицензией MIT. См. файл [LICENSE](LICENSE) для получения дополнительной информации.

---

**Примечание:** Изображения и GIF используются только в демонстрационных целях и могут отличаться в зависимости от версии проекта.