#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QLabel label("Hello, World from QMake!");
    label.show();
    return app.exec();
}
