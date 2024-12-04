<<<<<<< HEAD
# Используем базовый образ Ubuntu 22.04
FROM ubuntu:22.04

# Устанавливаем переменные окружения
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Moscow
ENV QT_QPA_PLATFORM=xcb
ENV XDG_RUNTIME_DIR=/tmp/runtime-root
ENV DISPLAY=:99

# Обновляем систему и устанавливаем зависимости
RUN apt update && apt install -y --no-install-recommends \
    qt5-qmake \
    cmake \
    qtbase5-dev \
    qtchooser \
    qttools5-dev-tools \
    build-essential \
    libxcb1 \
    libx11-xcb1 \
    libxcb-glx0 \
    libxcb-keysyms1 \
    libxcb-image0 \
    libxcb-shm0 \
    libxcb-icccm4 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-shape0 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-render0 \
    libxcb-xinerama0 \
    libfontconfig1 \
    libxkbcommon-x11-0 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y xvfb
RUN apt-get install -y mesa-utils

# Копируем проект в контейнер
COPY . /MedHelperQt
WORKDIR /MedHelperQt
# Сборка проекта
RUN qmake MedHelperQt.pro && make

# Указание команды запус
CMD ["./MedHelperQt"]
=======
# Используем базовый образ Ubuntu 22.04
FROM ubuntu:22.04

# Устанавливаем переменные окружения
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Moscow
ENV QT_QPA_PLATFORM=xcb
ENV XDG_RUNTIME_DIR=/tmp/runtime-root
ENV DISPLAY=:99

# Обновляем систему и устанавливаем зависимости
RUN apt update && apt install -y --no-install-recommends \
    qt5-qmake \
    cmake \
    qtbase5-dev \
    qtchooser \
    qttools5-dev-tools \
    build-essential \
    libxcb1 \
    libx11-xcb1 \
    libxcb-glx0 \
    libxcb-keysyms1 \
    libxcb-image0 \
    libxcb-shm0 \
    libxcb-icccm4 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-shape0 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-render0 \
    libxcb-xinerama0 \
    libfontconfig1 \
    libxkbcommon-x11-0 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y xvfb
RUN apt-get install -y mesa-utils

# Копируем проект в контейнер
COPY . /MedHelperQt
WORKDIR /MedHelperQt
# Сборка проекта
RUN qmake MedHelperQt.pro && make

# Указание команды запус
CMD ["./MedHelperQt"]

>>>>>>> 8f3488f (Initial commit)
