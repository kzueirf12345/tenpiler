# Tenpiler - тензорный компилятор

Это учебный проект 4-го семестра по созданию собственного тензорного компилятора. Курс "Введение в тензорные компиляторы"

Авторы: 
-   Попов Владимир, Б01-411
-   Шелонин Арсений, Б01-411

## Зависимости

| Зависимость           | Минимальная версия    | Назначение                                    |
|-----------------------|-----------------------|-----------------------------------------------|
| **CMake**             | 3.26                  | Сборка проекта и зависимостей                 |
| **Protobuf**          | 3.12.4                | Десериализация ONNX-файлов                    |
| **ONNX (libonnx)**    | 1.14                  | Работа со структурой графа                    |
| **GCC / Clang**       | GCC 10 / Clang 11     | Компиляция C++20 кода                         |
| **Python3**           | 3.10                  | Кодогенерация                                 |
| **fmt**               | 8.32                  | Логгер и дамп графа                           |
| **Graphviz**          | 2.43                  | дамп графа                                    |

### Установка зависимостей (Ubuntu/Debian)

#### 1. Системные зависимости
```bash
sudo apt update
sudo apt install -y \
    build-essential \
    git \
    wget \
    libprotobuf-dev protobuf-compiler \
    snap \
    libfmt-dev \
    python3.10 python3.10-venv python3.10-dev
```

#### 2. CMake

```bash
sudo snap install cmake --classic
# Если уже есть cmake из apt, а он скорее всего слишком старый, то для использования нового из snap выполните
echo 'export PATH="/snap/bin:$PATH"' >> ~/.bashrc # или ~/.zshrc
source ~/.bashrc # или ~/.zshrc
```

#### 3. ONNX
```bash
# Клонируем репозиторий
git clone --recursive https://github.com/onnx/onnx.git ~/onnx
cd ~/onnx

# Собираем и устанавливаем
mkdir -p build && cd build
cmake .. \
  -DONNX_BUILD_TESTS=OFF \
  -DONNX_USE_PROTOBUF_SHARED_LIBS=ON \
  -DCMAKE_BUILD_TYPE=Release

make -j$(nproc)
sudo make install
sudo ldconfig # обновление кэша динамических библиотек
```

## Сборка проекта

```bash
git clone --recursive https://github.com/kzueirf12345/tenpiler
cd tenpiler

cmake -B build -DCMAKE_BUILD_TYPE=Release # -DSANITIZE=ON включение санитайзеров
cmake --build build -j$(nproc)

# Запуск
./build/tenpiler
```