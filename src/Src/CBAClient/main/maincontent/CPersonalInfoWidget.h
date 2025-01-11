//utf-8 文件
#ifndef CPERSONALINFOWIDGET_H
#define CPERSONALINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class CPersonalInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPersonalInfoWidget(QWidget *parent = nullptr);
    ~CPersonalInfoWidget();

public slots:
    void updateUserInfo();
    void onEditInfo();
    void onSaveInfo();

private:
    void setupUI();
    void setEditMode(bool edit);

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_emailEdit;
    QLineEdit* m_phoneEdit;
    QPushButton* m_editBtn;
    QPushButton* m_saveBtn;
    bool m_editMode;
};

#endif // CPERSONALINFOWIDGET_H 