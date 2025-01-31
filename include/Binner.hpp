#ifndef BINNER_HPP
#define BINNER_HPP

#include <QMainWindow>
#include <QString>
#include <QPlainTextEdit>
#include <Globals.hpp>

class Binner : public QMainWindow {
	protected:
		QPlainTextEdit *textEdit;
		QString filePath;
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
		void saveFileAs();
		QString selectOpenFile();
		void openFile();
};
#endif
