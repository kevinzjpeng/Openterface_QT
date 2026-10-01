#include "VirtualKeyboardDialog.h"
#include "../../host/HostManager.h"
#include <QKeySequence>
#include <QDebug>
#include <QApplication>
#include <QPalette>

// Finger zone colors (MadTyping style)
// Left pinky: light blue, Left ring: light green, Left middle: light yellow, Left index: light orange
// Right index: light coral, Right middle: light pink, Right ring: light purple, Right pinky: light cyan
static const QString leftPinkyStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #d4e8ff, stop:0.5 #b8d4f0, stop:1 #9cc0e0); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0dcff, stop:0.5 #a8c8e8, stop:1 #90b8d8); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a8c8e8, stop:0.5 #90b8d8, stop:1 #78a8c8); }";

static const QString leftRingStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #d4ffd4, stop:0.5 #b8e8b8, stop:1 #9cd09c); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0f0c0, stop:0.5 #a8d8a8, stop:1 #90c890); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a8d8a8, stop:0.5 #90c890, stop:1 #78b878); }";

static const QString leftMiddleStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #ffffd4, stop:0.5 #f0e8b8, stop:1 #e0d09c); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #fff0c0, stop:0.5 #e8d8a8, stop:1 #d8c890); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8d8a8, stop:0.5 #d8c890, stop:1 #c8b878); }";

static const QString leftIndexStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #ffe8d4, stop:0.5 #f0d0b8, stop:1 #e0b89c); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffd8c0, stop:0.5 #e8c0a8, stop:1 #d8a890); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8c0a8, stop:0.5 #d8a890, stop:1 #c89878); }";

static const QString rightIndexStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #ffd4d4, stop:0.5 #f0b8b8, stop:1 #e09c9c); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc0c0, stop:0.5 #e8a8a8, stop:1 #d89090); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8a8a8, stop:0.5 #d89090, stop:1 #c87878); }";

static const QString rightMiddleStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #ffd4e8, stop:0.5 #f0b8d0, stop:1 #e09cb8); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffc0d8, stop:0.5 #e8a8c0, stop:1 #d890a8); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8a8c0, stop:0.5 #d890a8, stop:1 #c87890); }";

static const QString rightRingStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #e8d4ff, stop:0.5 #d0b8f0, stop:1 #b89ce0); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d8c0ff, stop:0.5 #c0a8e8, stop:1 #a890d8); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0a8e8, stop:0.5 #a890d8, stop:1 #9078c8); }";

static const QString rightPinkyStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #d4ffff, stop:0.5 #b8e8e8, stop:1 #9cd0d0); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0f0f0, stop:0.5 #a8d8d8, stop:1 #90c8c8); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a8d8d8, stop:0.5 #90c8c8, stop:1 #78b8b8); }";

static const QString thumbStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #f0f0f0, stop:0.5 #e0e0e0, stop:1 #d0d0d0); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 38px; min-height: 38px; font-size: 13px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8e8e8, stop:0.5 #d8d8d8, stop:1 #c8c8c8); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d0d0d0, stop:0.5 #c0c0c0, stop:1 #b0b0b0); }";

static const QString modifierKeyStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #f5f5f5, stop:0.5 #e0e0e0, stop:1 #cccccc); "
    "   color: #222; padding: 6px 8px; margin: 1px; "
    "   min-width: 50px; min-height: 38px; font-size: 12px; font-weight: 600; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:0.5 #d8d8d8, stop:1 #c0c0c0); } "
    "QPushButton:checked { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d0e8ff, stop:0.5 #a0c8ff, stop:1 #80b0ff); border: 2px solid #4a90d9; color: #1a3a5c; } "
    "QPushButton:checked:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0dfff, stop:0.5 #90c0ff, stop:1 #70a8ff); }";

static const QString functionKeyStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #f0f0f0, stop:0.5 #e0e0e0, stop:1 #d0d0d0); "
    "   color: #444; padding: 4px 6px; margin: 1px; "
    "   min-width: 36px; min-height: 30px; font-size: 11px; font-weight: 500; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8e8e8, stop:0.5 #d8d8d8, stop:1 #c8c8c8); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d0d0d0, stop:0.5 #c0c0c0, stop:1 #b0b0b0); }";

static const QString navigationKeyStyle =
    "QPushButton { "
    "   border: 1px solid #999; border-radius: 4px; "
    "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
    "       stop:0 #e8e8e8, stop:0.5 #d8d8d8, stop:1 #c8c8c8); "
    "   color: #333; padding: 4px 6px; margin: 1px; "
    "   min-width: 36px; min-height: 30px; font-size: 11px; font-weight: 600; "
    "} "
    "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e0e0e0, stop:0.5 #d0d0d0, stop:1 #c0c0c0); } "
    "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c8c8c8, stop:0.5 #b8b8b8, stop:1 #a8a8a8); }";

const QString VirtualKeyboardDialog::buttonStyle = thumbStyle;
const QString VirtualKeyboardDialog::modifierButtonStyle = modifierKeyStyle;
const QString VirtualKeyboardDialog::pressedButtonStyle = navigationKeyStyle;

VirtualKeyboardDialog::VirtualKeyboardDialog(QWidget *parent)
    : QDialog(parent)
    , currentModifiers(0)
{
    setWindowTitle(tr("Openterface Keyboard"));
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose, false);

    setupUI();
    createKeyboardLayout();
    adjustSize();
}

void VirtualKeyboardDialog::setupUI()
{
    // Set dialog background color for keyboard-like appearance
    setStyleSheet(
        "QDialog { "
        "   background-color: #e5e5e5; "
        "   border: 1px solid #999; "
        "   border-radius: 8px; "
        "} "
        "QLabel#titleLabel { "
        "   color: #333; "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "   padding: 4px 8px; "
        "   background-color: transparent; "
        "}"
    );

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(3);
    mainLayout->setContentsMargins(10, 6, 10, 10);

    // Header with title
    QHBoxLayout* headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    QLabel* titleLabel = new QLabel(tr("Openterface Keyboard"), this);
    titleLabel->setObjectName("titleLabel");
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    mainLayout->addLayout(headerLayout);

    // Keyboard container with darker background for depth
    QWidget* keyboardContainer = new QWidget(this);
    keyboardContainer->setStyleSheet(
        "QWidget { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #d0d0d0, stop:0.1 #e0e0e0, stop:0.9 #d8d8d8, stop:1 #c0c0c0); "
        "   border: 2px solid #888; "
        "   border-radius: 6px; "
        "}"
    );

    keyboardLayout = new QGridLayout(keyboardContainer);
    keyboardLayout->setSpacing(2);
    keyboardLayout->setContentsMargins(6, 6, 6, 6);

    mainLayout->addWidget(keyboardContainer);

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

    // Row 6: Navigation keys (arrows, Home, End, PageUp, PageDown)
    addNavigationRow(keyboardLayout, row++);
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

void VirtualKeyboardDialog::addNavigationRow(QGridLayout* layout, int row)
{
    int col = 0;

    // Insert key (wider)
    QPushButton* insertBtn = createKeyButton("Insert", Qt::Key_Insert);
    insertBtn->setMinimumWidth(70);
    layout->addWidget(insertBtn, row, col++, 1, 2);

    // Home key (wider)
    QPushButton* homeBtn = createKeyButton("Home", Qt::Key_Home);
    homeBtn->setMinimumWidth(60);
    layout->addWidget(homeBtn, row, col++, 1, 2);

    // Page Up key (wider)
    QPushButton* pageUpBtn = createKeyButton("PgUp", Qt::Key_PageUp);
    pageUpBtn->setMinimumWidth(60);
    layout->addWidget(pageUpBtn, row, col++, 1, 2);

    // Delete key
    QPushButton* delBtn = createKeyButton("Del", Qt::Key_Delete);
    layout->addWidget(delBtn, row, col++);

    // End key (wider)
    QPushButton* endBtn = createKeyButton("End", Qt::Key_End);
    endBtn->setMinimumWidth(60);
    layout->addWidget(endBtn, row, col++, 1, 2);

    // Page Down key (wider)
    QPushButton* pageDownBtn = createKeyButton("PgDn", Qt::Key_PageDown);
    pageDownBtn->setMinimumWidth(60);
    layout->addWidget(pageDownBtn, row, col++, 1, 2);

    // Arrow keys: Up, Left, Down, Right
    QPushButton* upBtn = createKeyButton("↑", Qt::Key_Up);
    upBtn->setMinimumWidth(40);
    layout->addWidget(upBtn, row, col++, 1, 1);

    // Left arrow
    QPushButton* leftBtn = createKeyButton("←", Qt::Key_Left);
    leftBtn->setMinimumWidth(40);
    layout->addWidget(leftBtn, row, col++, 1, 1);

    // Down arrow
    QPushButton* downBtn = createKeyButton("↓", Qt::Key_Down);
    downBtn->setMinimumWidth(40);
    layout->addWidget(downBtn, row, col++, 1, 1);

    // Right arrow
    QPushButton* rightBtn = createKeyButton("→", Qt::Key_Right);
    rightBtn->setMinimumWidth(40);
    layout->addWidget(rightBtn, row, col++, 1, 1);
}

QPushButton* VirtualKeyboardDialog::createKeyButton(const QString& text, int keyCode, bool isModifier)
{
    QPushButton* button = new QPushButton(text, this);

    // Apply finger zone colors based on key (MadTyping style)
    if (isModifier) {
        button->setStyleSheet(modifierKeyStyle);
    } else {
        // Map keys to finger zones
        switch (keyCode) {
            // Left pinky: 1, Q, A, Z, Tab, CapsLock, Backspace
            case Qt::Key_1:
            case Qt::Key_Q:
            case Qt::Key_A:
            case Qt::Key_Z:
            case Qt::Key_Tab:
            case Qt::Key_CapsLock:
            case Qt::Key_Backspace:
                button->setStyleSheet(leftPinkyStyle);
                break;

            // Left ring: 2, W, S, X
            case Qt::Key_2:
            case Qt::Key_W:
            case Qt::Key_S:
            case Qt::Key_X:
                button->setStyleSheet(leftRingStyle);
                break;

            // Left middle: 3, E, D, C
            case Qt::Key_3:
            case Qt::Key_E:
            case Qt::Key_D:
            case Qt::Key_C:
                button->setStyleSheet(leftMiddleStyle);
                break;

            // Left index: 4,5,R,T,F,G,V,B
            case Qt::Key_4:
            case Qt::Key_5:
            case Qt::Key_R:
            case Qt::Key_T:
            case Qt::Key_F:
            case Qt::Key_G:
            case Qt::Key_V:
            case Qt::Key_B:
                button->setStyleSheet(leftIndexStyle);
                break;

            // Right index: 6,7,Y,U,H,J,N,M
            case Qt::Key_6:
            case Qt::Key_7:
            case Qt::Key_Y:
            case Qt::Key_U:
            case Qt::Key_H:
            case Qt::Key_J:
            case Qt::Key_N:
            case Qt::Key_M:
                button->setStyleSheet(rightIndexStyle);
                break;

            // Right middle: 8,I,K,,
            case Qt::Key_8:
            case Qt::Key_I:
            case Qt::Key_K:
            case Qt::Key_Comma:
                button->setStyleSheet(rightMiddleStyle);
                break;

            // Right ring: 9,O,L,.
            case Qt::Key_9:
            case Qt::Key_O:
            case Qt::Key_L:
            case Qt::Key_Period:
                button->setStyleSheet(rightRingStyle);
                break;

            // Right pinky: 0,-,=,P,[,],\,;,',/,Enter,Right Shift
            case Qt::Key_0:
            case Qt::Key_Minus:
            case Qt::Key_Equal:
            case Qt::Key_P:
            case Qt::Key_BracketLeft:
            case Qt::Key_BracketRight:
            case Qt::Key_Backslash:
            case Qt::Key_Semicolon:
            case Qt::Key_Apostrophe:
            case Qt::Key_Slash:
            case Qt::Key_Return:
            case Qt::Key_Shift: // Right Shift - handled separately in layout
                button->setStyleSheet(rightPinkyStyle);
                break;

            // Default to standard style for space and other keys
            default:
                button->setStyleSheet(thumbStyle);
                break;
        }
    }

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
