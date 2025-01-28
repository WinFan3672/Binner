#include <iostream>
#include <fstream>
#include <QApplication>
#include <Binner.hpp>
#include <Globals.hpp>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Binner binner;
	binner.show();
	return app.exec();
}
