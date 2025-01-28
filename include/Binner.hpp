#ifndef BINNER_HPP
#define BINNER_HPP

#include <QMainWindow>
#include <QString>
#include <QPlainTextEdit>
#include <Globals.hpp>

class Binner : public QMainWindow {
	protected:
		QPlainTextEdit *textEdit;
		std::string filePath;
	private:
		QAction *wordWrap;
	public:
		Binner();
		void newAction();
		void insertTitle();
		void insertSeparator();
		void aboutBinner();
		void toggleWordWrap();
		void saveFile();
		QString selectSaveFile();
};
#endif
