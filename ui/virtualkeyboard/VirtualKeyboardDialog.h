#ifndef VIRTUALKEYBOARDDIALOG_H
#define VIRTUALKEYBOARDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMap>

class VirtualKeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VirtualKeyboardDialog(QWidget *parent = nullptr);
    ~VirtualKeyboardDialog() = default;

private:
    void setupUI();
    void createKeyboardLayout();
    QPushButton* createKeyButton(const QString& text, int keyCode, bool isModifier = false);

    // Row builders
    void addFunctionKeyRow(QGridLayout* layout, int row);
    void addNumberRow(QGridLayout* layout, int row);
    void addTabRow(QGridLayout* layout, int row);
    void addCapsRow(QGridLayout* layout, int row);
    void addShiftRow(QGridLayout* layout, int row);
    void addBottomRow(QGridLayout* layout, int row);
    void addNavigationRow(QGridLayout* layout, int row);

private slots:
    void onKeyClicked();
    void onModifierToggled(bool checked);

private:
    QVBoxLayout* mainLayout;
    QGridLayout* keyboardLayout;
    int currentModifiers;
    QMap<QPushButton*, int> modifierButtons;

    static const QString buttonStyle;
    static const QString modifierButtonStyle;
    static const QString pressedButtonStyle;
};

#endif // VIRTUALKEYBOARDDIALOG_H
