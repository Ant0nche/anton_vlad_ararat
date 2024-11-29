#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Настройка базы данных
    setupDatabase();

    // Подключение кнопки авторизации
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginUser);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Настройка базы данных
void MainWindow::setupDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("medhelper.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
        return;
    }

    QSqlQuery query;

    // Создание таблицы пользователей
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE, "
                    "password TEXT)")) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу пользователей: " + query.lastError().text());
        return;
    }

    // Добавление тестового пользователя, если таблица пуста
    if (query.exec("SELECT COUNT(*) FROM users") && query.next() && query.value(0).toInt() == 0) {
        QString hashedPassword = QString(QCryptographicHash::hash("admin", QCryptographicHash::Sha256).toHex());
        if (!query.exec("INSERT INTO users (username, password) VALUES ('admin', '" + hashedPassword + "')")) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить тестового пользователя: " + query.lastError().text());
        } else {
            qDebug() << "Тестовый пользователь добавлен: admin / admin";
        }
    }

    QMessageBox::information(this, "Успех", "База данных готова к использованию.");
}

// Авторизация пользователя
void MainWindow::loginUser() {
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
        return;
    }

    // Хэшируем пароль
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (query.exec() && query.next()) {
        QMessageBox::information(this, "Успех", "Вы успешно вошли в систему!");
        // Здесь можно добавить логику перехода на новый экран или разблокировки интерфейса
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль.");
    }
}
