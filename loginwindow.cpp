#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    // Подключение к базе данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("medhelper.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    } else {
        setupDatabase();
    }
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::setupDatabase() {
    QSqlQuery query;

    // Создание таблицы пользователей
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE, "
                    "password TEXT)")) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу пользователей: " + query.lastError().text());
    }

    // Предварительное добавление тестового пользователя (для тестирования)
    if (!query.exec("INSERT OR IGNORE INTO users (username, password) "
                    "VALUES ('admin', 'admin')")) {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить тестового пользователя: " + query.lastError().text());
    }
}

void LoginWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
        return;
    }

    // Хэширование пароля перед отправкой в запрос
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (query.exec() && query.next()) {
        QMessageBox::information(this, "Успех", "Вход выполнен.");
        accept();  // Закрываем окно авторизации и продолжаем работу
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
    }
}
