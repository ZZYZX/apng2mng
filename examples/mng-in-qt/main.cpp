#include <QApplication>
#include <QLabel>
#include <QMovie>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel label;
    QMovie movie(":/update_spinner.mng");

    label.setMovie(&movie);
    movie.start();
    label.setScaledContents(true);
    label.resize(128, 128);
    label.show();

    return app.exec();
}
