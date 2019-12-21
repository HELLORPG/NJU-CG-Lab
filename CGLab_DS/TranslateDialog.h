#ifndef TRANSLATEDIALOG_H
#define TRANSLATEDIALOG_H

#include <QDialog>
#include <ctime>

namespace Ui {
class TranslateDialog;
}

class TranslateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TranslateDialog(time_t uid, QWidget *parent = nullptr);
    ~TranslateDialog();
	void accept() override; // ���ȷ��֮��Ĳ�������
	void receive(const time_t uid, bool flag);

signals:
	void translate_data(const int id, const int dx, const int dy, const time_t uid); // ���ź����ڴ���ƽ�ƵĲ�����Ϣ

private:
    Ui::TranslateDialog *ui;
	time_t uid;
};

#endif // TRANSLATEDIALOG_H
