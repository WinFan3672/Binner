#ifndef TITLEINSERTER_HPP
#define TITLEINSERTER_HPP

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <Globals.hpp>

class TitleInserter : public QDialog {
	public:
		TitleInserter(QWidget *parent, QPlainTextEdit *text);
		QString center(QString text, int width);
	protected:
		void accept() override;
	private:
		QLineEdit *titleBox;
		QPlainTextEdit *textEdit;
		QVBoxLayout *central;
};

#endif
