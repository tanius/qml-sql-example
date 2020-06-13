#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include <QObject>
#include <QDebug>

class MyDatabase : public QObject {
   Q_OBJECT

public:
    explicit MyDatabase (QObject* parent = 0) : QObject(parent) { }

    Q_INVOKABLE QString search(QString mInputText) {

        QSqlQuery query;
        query.prepare("SELECT name FROM people WHERE id = ?");
        // query.addBindValue(mInputText.toInt());
        query.addBindValue(QVariant(mInputText.toInt()));

        if(!query.exec())
            qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

        if(query.first())
            return QString(query.value(0).toString());
        else
            return QString("person not found");
    }
};

// We want to avoid defining the class above in a my_database.h file. That would let the MOC
// pre-processor find what it needs automatically, but we'd have another file in this demo.
// To avoid that, we have to include the .moc manually. See: https://stackoverflow.com/a/3005403
#include "main.moc"


// TODO: Make this a static function of class Database.
void databaseConnect() {
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(":memory:");

        if(!db.open())
            qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";
}


// TODO: Make this a static function of class Database.
void databaseInit() {
    QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");

    if(!query.isActive())
        qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();
}


// TODO: Make this a static function of class Database.
void databasePopulate() {
    QSqlQuery query;

    if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Gordon Ramsay')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Alan Sugar')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Dana Scully')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Lila Wolfe')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Ashley Williams')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Karen Bryant')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Jon Snow')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Linus Torvalds')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
    if(!query.exec("INSERT INTO people(name) VALUES('Hayley Moore')"))
        qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
}


int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication application(argc, argv);

    application.setApplicationName("Qt QML SQL example");

    databaseConnect();
    databaseInit();
    databasePopulate();

    qmlRegisterType<MyDatabase>("org.mydb", 1, 0, "MyDatabase");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        QCoreApplication::exit(-1);
    }
    return application.exec();
}
