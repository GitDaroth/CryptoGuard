#include <QApplication>
#include "UI/MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	MainWindow mainWindow;
	mainWindow.resize(800, 600);
	mainWindow.show();

	return application.exec();
}