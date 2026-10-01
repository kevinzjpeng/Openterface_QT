#include "VirtualKeyboardDialog.h"
#include "../../host/HostManager.h"
#include <QKeySequence>
#include <QDebug>

const QString VirtualKeyboardDialog::buttonStyle =
    "QPushButton { "
    "   border: 1px solid #888; "
    "   border-radius: 4px; "
    "   background-color: #f0f0f0; "
    "   color: #333; "
    "   padding: 8px; "
    "   margin: 2px; "
    "   min-width: 40px; "
    "   font-size: 12px; "
    "} "
    "QPushButton:hover { "
    "   background-color: #e0e0e0; "
    "} "
    "QPushButton:pressed { "
    "   background-color: #c0c0c0; "
    "}";

const QString VirtualKeyboardDialog::modifierButtonStyle =
    "QPushButton { "
    "   border: 1px solid #888; "
    "   border-radius: 4px; "
    "   background-color: #d0d0ff; "
    "   color: #333; "
    "   padding: 8px; "
    "   margin: 2px; "
    "   min-width: 50px; "
    "   font-size: 12px; "
    "} "
    "QPushButton:hover { "
    "   background-color: #c0c0ff; "
    "} "
    "QPushButton:checked { "
    "   background-color: #a0a0ff; "
    "   border: 2px solid #6666ff; "
    "}";

const QString VirtualKeyboardDialog::pressedButtonStyle =
    "QPushButton { "
    "   border: 1px solid #888; "
    "   border-radius: 4px; "
    "   background-color: #ffcc00; "
    "   color: #333; "
    "   padding: 8px; "
    "   margin: 2px; "
    "   min-width: 40px; "
    "   font-size: 12px; "
    "}";

VirtualKeyboardDialog::VirtualKeyboardDialog(QWidget *parent)
    : QDialog(parent)
    , currentModifiers(0)
{
    setWindowTitle(tr("Virtual Keyboard"));
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose, false);

    setupUI();
    createKeyboardLayout();
    adjustSize();
}

void VirtualKeyboardDialog::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(4);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    keyboardLayout = new QGridLayout();
    keyboardLayout->setSpacing(4);
    mainLayout->addLayout(keyboardLayout);

    setLayout(mainLayout);
}

void VirtualKeyboardDialog::createKeyboardLayout()
{
    int row = 0;

    // Row 0: Function keys
    addFunctionKeyRow(keyboardLayout, row++);

    // Row 1: Number row
    addNumberRow(keyboardLayout, row++);

    // Row 2: Tab row (QWERTY)
    addTabRow(keyboardLayout, row++);

    // Row 3: Caps row (ASDF)
    addCapsRow(keyboardLayout, row++);

    // Row 4: Shift row (ZXCV)
    addShiftRow(keyboardLayout, row++);

    // Row 5: Bottom row (Ctrl, Alt, Win, Space)
    addBottomRow(keyboardLayout, row++);
}

void VirtualKeyboardDialog::addFunctionKeyRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Esc key
    QPushButton* escBtn = createKeyButton("Esc", Qt::Key_Escape);
    layout->addWidget(escBtn, row, col++);

    // Spacing
    col++;

    // F1-F12
    for (int i = 0; i < 12; i++) {
        QPushButton* fBtn = createKeyButton(QString("F%1").arg(i + 1), Qt::Key_F1 + i);
        layout->addWidget(fBtn, row, col++);
        // Add spacing after F4 and F8
        if (i == 3 || i == 7) {
            col++;
        }
    }

    // Del key
    col++;
    QPushButton* delBtn = createKeyButton("Del", Qt::Key_Delete);
    layout->addWidget(delBtn, row, col++);
}

void VirtualKeyboardDialog::addNumberRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Backtick/tilde
    QPushButton* graveBtn = createKeyButton("`", Qt::Key_QuoteLeft);
    layout->addWidget(graveBtn, row, col++);

    // Number keys 1-0
    for (int i = 0; i < 10; i++) {
        int keyCode = (i == 9) ? Qt::Key_0 : (Qt::Key_1 + i);
        QPushButton* numBtn = createKeyButton(QString::number((i + 1) % 10), keyCode);
        layout->addWidget(numBtn, row, col++);
    }

    // Minus and equals
    QPushButton* minusBtn = createKeyButton("-", Qt::Key_Minus);
    layout->addWidget(minusBtn, row, col++);

    QPushButton* equalBtn = createKeyButton("=", Qt::Key_Equal);
    layout->addWidget(equalBtn, row, col++);

    // Backspace (wider)
    QPushButton* backspaceBtn = createKeyButton("Backspace", Qt::Key_Backspace);
    backspaceBtn->setMinimumWidth(80);
    layout->addWidget(backspaceBtn, row, col++, 1, 2);
}

void VirtualKeyboardDialog::addTabRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Tab key (wider)
    QPushButton* tabBtn = createKeyButton("Tab", Qt::Key_Tab);
    tabBtn->setMinimumWidth(60);
    layout->addWidget(tabBtn, row, col++, 1, 2);

    // QWERTYUIOP
    QString keys = "QWERTYUIOP";
    for (int i = 0; i < keys.length(); i++) {
        QChar key = keys[i];
        int keyCode = Qt::Key_A + (key.toLatin1() - 'A');
        QPushButton* keyBtn = createKeyButton(key, keyCode);
        layout->addWidget(keyBtn, row, col++);
    }

    // Bracket keys
    QPushButton* leftBracketBtn = createKeyButton("[", Qt::Key_BracketLeft);
    layout->addWidget(leftBracketBtn, row, col++);

    QPushButton* rightBracketBtn = createKeyButton("]", Qt::Key_BracketRight);
    layout->addWidget(rightBracketBtn, row, col++);

    // Backslash (wider)
    QPushButton* backslashBtn = createKeyButton("\\", Qt::Key_Backslash);
    backslashBtn->setMinimumWidth(60);
    layout->addWidget(backslashBtn, row, col++, 1, 2);
}

void VirtualKeyboardDialog::addCapsRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Caps Lock key (wider)
    QPushButton* capsBtn = createKeyButton("Caps", Qt::Key_CapsLock);
    capsBtn->setMinimumWidth(70);
    layout->addWidget(capsBtn, row, col++, 1, 2);

    // ASDFGHJKL
    QString keys = "ASDFGHJKL";
    for (int i = 0; i < keys.length(); i++) {
        QChar key = keys[i];
        int keyCode = Qt::Key_A + (key.toLatin1() - 'A');
        QPushButton* keyBtn = createKeyButton(key, keyCode);
        layout->addWidget(keyBtn, row, col++);
    }

    // Semicolon and apostrophe
    QPushButton* semicolonBtn = createKeyButton(";", Qt::Key_Semicolon);
    layout->addWidget(semicolonBtn, row, col++);

    QPushButton* apostropheBtn = createKeyButton("'", Qt::Key_Apostrophe);
    layout->addWidget(apostropheBtn, row, col++);

    // Enter key (wider)
    QPushButton* enterBtn = createKeyButton("Enter", Qt::Key_Return);
    enterBtn->setMinimumWidth(90);
    layout->addWidget(enterBtn, row, col++, 1, 2);
}

void VirtualKeyboardDialog::addShiftRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Left Shift key (wider)
    QPushButton* leftShiftBtn = createKeyButton("Shift", Qt::Key_Shift, true);
    leftShiftBtn->setMinimumWidth(90);
    leftShiftBtn->setCheckable(true);
    modifierButtons[leftShiftBtn] = Qt::ShiftModifier;
    connect(leftShiftBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(leftShiftBtn, row, col++, 1, 2);

    // ZXCVBNM
    QString keys = "ZXCVBNM";
    for (int i = 0; i < keys.length(); i++) {
        QChar key = keys[i];
        int keyCode = Qt::Key_A + (key.toLatin1() - 'A');
        QPushButton* keyBtn = createKeyButton(key, keyCode);
        layout->addWidget(keyBtn, row, col++);
    }

    // Comma, period, slash
    QPushButton* commaBtn = createKeyButton(",", Qt::Key_Comma);
    layout->addWidget(commaBtn, row, col++);

    QPushButton* periodBtn = createKeyButton(".", Qt::Key_Period);
    layout->addWidget(periodBtn, row, col++);

    QPushButton* slashBtn = createKeyButton("/", Qt::Key_Slash);
    layout->addWidget(slashBtn, row, col++);

    // Right Shift key (wider)
    QPushButton* rightShiftBtn = createKeyButton("Shift", Qt::Key_Shift, true);
    rightShiftBtn->setMinimumWidth(110);
    rightShiftBtn->setCheckable(true);
    modifierButtons[rightShiftBtn] = Qt::ShiftModifier;
    connect(rightShiftBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(rightShiftBtn, row, col++, 1, 2);
}

void VirtualKeyboardDialog::addBottomRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Left Ctrl
    QPushButton* leftCtrlBtn = createKeyButton("Ctrl", Qt::Key_Control, true);
    leftCtrlBtn->setCheckable(true);
    modifierButtons[leftCtrlBtn] = Qt::ControlModifier;
    connect(leftCtrlBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(leftCtrlBtn, row, col++);

    // Left Alt
    QPushButton* leftAltBtn = createKeyButton("Alt", Qt::Key_Alt, true);
    leftAltBtn->setCheckable(true);
    modifierButtons[leftAltBtn] = Qt::AltModifier;
    connect(leftAltBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(leftAltBtn, row, col++);

    // Left Win/Meta
    QPushButton* leftWinBtn = createKeyButton("Win", Qt::Key_Meta, true);
    leftWinBtn->setCheckable(true);
    modifierButtons[leftWinBtn] = Qt::MetaModifier;
    connect(leftWinBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(leftWinBtn, row, col++);

    // Space bar (wide)
    QPushButton* spaceBtn = createKeyButton("Space", Qt::Key_Space);
    spaceBtn->setMinimumWidth(250);
    layout->addWidget(spaceBtn, row, col++, 1, 5);

    // Right Win/Meta
    QPushButton* rightWinBtn = createKeyButton("Win", Qt::Key_Meta, true);
    rightWinBtn->setCheckable(true);
    modifierButtons[rightWinBtn] = Qt::MetaModifier;
    connect(rightWinBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(rightWinBtn, row, col++);

    // Right Alt
    QPushButton* rightAltBtn = createKeyButton("Alt", Qt::Key_Alt, true);
    rightAltBtn->setCheckable(true);
    modifierButtons[rightAltBtn] = Qt::AltModifier;
    connect(rightAltBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(rightAltBtn, row, col++);

    // Right Ctrl
    QPushButton* rightCtrlBtn = createKeyButton("Ctrl", Qt::Key_Control, true);
    rightCtrlBtn->setCheckable(true);
    modifierButtons[rightCtrlBtn] = Qt::ControlModifier;
    connect(rightCtrlBtn, &QPushButton::toggled, this, &VirtualKeyboardDialog::onModifierToggled);
    layout->addWidget(rightCtrlBtn, row, col++);
}

QPushButton* VirtualKeyboardDialog::createKeyButton(const QString& text, int keyCode, bool isModifier)
{
    QPushButton* button = new QPushButton(text, this);
    button->setStyleSheet(isModifier ? modifierButtonStyle : buttonStyle);
    button->setProperty("keyCode", keyCode);
    button->setProperty("isModifier", isModifier);

    if (!isModifier) {
        connect(button, &QPushButton::clicked, this, &VirtualKeyboardDialog::onKeyClicked);
    }

    return button;
}

void VirtualKeyboardDialog::onKeyClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int keyCode = button->property("keyCode").toInt();
    if (keyCode == 0) return;

    // Special case: Ctrl+Alt+Del
    if (keyCode == Qt::Key_Delete &&
        (currentModifiers & Qt::ControlModifier) &&
        (currentModifiers & Qt::AltModifier)) {
        HostManager::getInstance().sendCtrlAltDel();
        // Uncheck modifier buttons
        for (auto it = modifierButtons.begin(); it != modifierButtons.end(); ++it) {
            it.key()->setChecked(false);
        }
        currentModifiers = 0;
        return;
    }

    // Send the key with current modifiers
    HostManager::getInstance().handleFunctionKey(keyCode, currentModifiers);

    // Auto-release shift after key press (like a real keyboard)
    for (auto it = modifierButtons.begin(); it != modifierButtons.end(); ++it) {
        if (it.value() == Qt::ShiftModifier && it.key()->isChecked()) {
            it.key()->setChecked(false);
        }
    }
    currentModifiers &= ~Qt::ShiftModifier;
}

void VirtualKeyboardDialog::onModifierToggled(bool checked)
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int modifier = modifierButtons.value(button, 0);
    if (modifier == 0) return;

    if (checked) {
        currentModifiers |= modifier;
    } else {
        currentModifiers &= ~modifier;
    }

    // Sync all modifier buttons with the same modifier flag
    for (auto it = modifierButtons.begin(); it != modifierButtons.end(); ++it) {
        if (it.value() == modifier && it.key() != button) {
            it.key()->setChecked(checked);
        }
    }
}
