#include "KeyboardLayouts.h"
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QKeySequence>

Q_LOGGING_CATEGORY(log_keyboard_layouts, "opf.host.layouts")

const KeyboardLayoutConfig QWERTY_US("US QWERTY", false);
const KeyboardLayoutConfig QWERTY_UK("UK QWERTY", false);
const KeyboardLayoutConfig AZERTY_FR("French AZERTY", false);
const KeyboardLayoutConfig AZERTY_BE("Belgian AZERTY", false);
const KeyboardLayoutConfig QWERTZ_DE("German QWERTZ", false);
const KeyboardLayoutConfig QWERTY_DK("Danish QWERTY", false);
const KeyboardLayoutConfig QWERTY_SE("Swedish QWERTY", false);
const KeyboardLayoutConfig JAPANESE("Japanese", false);
const KeyboardLayoutConfig QWERTY_ES("Spanish QWERTY", false);

// Initialize all layouts
struct LayoutInitializer {
    LayoutInitializer() {
        // The initialization functions are removed as per the instructions
    }
} layoutInitializer;

QMap<QString, int> KeyboardLayoutConfig::keyNameToQt;

// Static method implementation
KeyboardLayoutConfig KeyboardLayoutConfig::fromJsonFile(const QString& filePath) {
    KeyboardLayoutConfig config;
    
    qCDebug(log_keyboard_layouts) << "Loading keyboard layout from file:" << filePath;
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open keyboard layout file:" << filePath;
        return config;
    }

    QByteArray data = file.readAll();
    qCDebug(log_keyboard_layouts) << "File contents:" << data;
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "Failed to parse JSON from file:" << filePath;
        return config;
    }

    QJsonObject json = doc.object();
    
    // Load basic properties
    config.name = json["name"].toString();
    config.isRightToLeft = json["right_to_left"].toBool(false);
    qCDebug(log_keyboard_layouts) << "Loading layout:" << config.name;

    // Create a mapping from key names to Qt key codes
    if (keyNameToQt.isEmpty()) {
        initializeKeyNameToQt(keyNameToQt);
    }

    // Load key map
    QJsonObject keyMap = json["key_map"].toObject();
    qCDebug(log_keyboard_layouts) << "Loading" << keyMap.size() << "key mappings";
    
    for (auto it = keyMap.begin(); it != keyMap.end(); ++it) {
        QString keyName = it.key();
        QString valueStr = it.value().toString();
        
        // Convert key name to Qt key code
        if (keyName.startsWith("Key_")) {
            keyName = keyName.mid(4); // Remove "Key_" prefix
        }
        
        // Get the Qt key code
        int qtKey = keyNameToQt.value(keyName, Qt::Key_unknown);
        qCDebug(log_keyboard_layouts) << "Converting key name:" << keyName 
                                    << "to Qt key code:" << qtKey 
                                    << "(original name:" << it.key() << ")";
        
        // Convert hex string to integer
        bool ok;
        uint8_t scanCode = valueStr.mid(2).toInt(&ok, 16);
        if (ok && qtKey != Qt::Key_unknown) {
            config.keyMap[qtKey] = scanCode;
            qCDebug(log_keyboard_layouts) << "Successfully mapped key" << keyName 
                                        << "(" << qtKey << ") to scancode 0x" + QString::number(scanCode, 16);
        } else{
            qCWarning(log_keyboard_layouts) << "Failed to map key" << keyName 
                                          << "value:" << valueStr 
                                          << "ok:" << ok 
                                          << "qtKey:" << qtKey;
        }
    }

    // Load char mapping. A value is either a key name ("Key_A"), a key name with
    // modifier prefixes ("AltGr+Key_E"), or an array of those for dead key sequences
    // (e.g. ["Key_Dead_Diaeresis", "Shift+Key_A"]).
    QJsonObject charMap = json["char_mapping"].toObject();
    for (auto it = charMap.begin(); it != charMap.end(); ++it) {
        QString charStr = it.key();
        if (charStr.size() != 1) {
            qCWarning(log_keyboard_layouts) << "Ignoring char_mapping key that is not a single character:" << charStr;
            continue;
        }
        QChar character = charStr[0];
        qCDebug(log_keyboard_layouts) << "Processing char:" << charStr;

        auto parseStep = [&](const QString& rawKey, KeyboardInputStep& step) -> bool {
            QString keyName = rawKey.trimmed();
            int modifiers = 0;
            while (true) {
                if (keyName.startsWith("Shift+")) {
                    modifiers |= Qt::ShiftModifier;
                    keyName = keyName.mid(6);
                } else if (keyName.startsWith("AltGr+")) {
                    modifiers |= Qt::GroupSwitchModifier;
                    keyName = keyName.mid(6);
                } else {
                    break;
                }
            }
            if (keyName.startsWith("Key_")) {
                keyName = keyName.mid(4);
            }
            int qtKey = keyNameToQt.value(keyName, Qt::Key_unknown);
            if (qtKey == Qt::Key_unknown) {
                qCWarning(log_keyboard_layouts) << "Unknown key name in char_mapping:" << rawKey << "for char:" << charStr;
                return false;
            }
            step = {qtKey, modifiers};
            return true;
        };

        QList<KeyboardInputStep> steps;
        const QJsonValue value = it.value();
        if (value.isArray()) {
            const QJsonArray stepArray = value.toArray();
            for (const QJsonValue& stepValue : stepArray) {
                KeyboardInputStep step;
                if (parseStep(stepValue.toString(), step)) {
                    steps.append(step);
                }
            }
        } else {
            KeyboardInputStep step;
            if (parseStep(value.toString(), step)) {
                steps.append(step);
            }
        }

        if (steps.isEmpty()) {
            continue;
        }
        if (steps.size() == 1 && steps.first().modifiers == 0) {
            config.charMapping[character.unicode()] = steps.first().keyCode;
            qCDebug(log_keyboard_layouts) << "Mapped char" << charStr << "to QtKey" << QString::number(steps.first().keyCode, 16);
        } else {
            config.charSequences[character.unicode()] = steps;
            qCDebug(log_keyboard_layouts) << "Mapped char" << charStr << "to sequence of" << steps.size() << "step(s)";
        }
    }

    QJsonObject unicodeMap = json["unicode_map"].toObject();
    qCDebug(log_keyboard_layouts) << "Loading" << unicodeMap.size() << "unicode mappings";
    
    for (auto it = unicodeMap.begin(); it != unicodeMap.end(); ++it) {
        QString unicodeStr = it.key();
        QString valueStr = it.value().toString();

        uint32_t unicodeValue;
        if (unicodeStr.startsWith("U+")) {
            bool ok;
            unicodeValue = unicodeStr.mid(2).toUInt(&ok, 16);
            if (!ok) {
                qCWarning(log_keyboard_layouts) << "Invalid Unicode key:" << unicodeStr;
                continue;
            }
        } else {
            bool ok;
            unicodeValue = unicodeStr.toUInt(&ok);
            if (!ok) {
                qCWarning(log_keyboard_layouts) << "Invalid Unicode key:" << unicodeStr;
                continue;
            }
        }

        bool ok;
        uint8_t scanCode = valueStr.mid(2).toInt(&ok, 16);
        if (ok) {
            config.unicodeMap[unicodeValue] = scanCode;
            qCDebug(log_keyboard_layouts) << "Mapped Unicode U+" << QString::number(unicodeValue, 16) 
                                        << "to scancode 0x" << QString::number(scanCode, 16);
        } else {
            qCWarning(log_keyboard_layouts) << "Failed to parse scancode for Unicode" 
                                          << unicodeStr << ":" << valueStr;
        }
    }

    // Load shift keys
    QJsonArray shiftKeys = json["need_shift_keys"].toArray();
    for (const QJsonValue& value : shiftKeys) {
        QString keyStr = value.toString();
        if (keyStr.length() == 1) {
            config.needShiftKeys.append(keyStr[0].unicode()); 
        } else {
            // Handle hex values for special characters
            config.needShiftKeys.append(keyStr.toInt(nullptr, 16));
        }
    }

    if (json.contains("need_altgr_keys")) {
        QJsonArray altGrKeys = json["need_altgr_keys"].toArray();
        for (const QJsonValue& value : altGrKeys) {
            QString keyStr = value.toString();
            if (keyStr.length() == 1) {
                config.needAltGrKeys.append(keyStr[0].unicode());
                qCDebug(log_keyboard_layouts) << "Added AltGr key:" << keyStr;
            } else {
                config.needAltGrKeys.append(keyStr.toInt(nullptr, 16));
                qCDebug(log_keyboard_layouts) << "Added AltGr key (hex):" << keyStr;
            }
        }
    }
    
    return config;
}

// Singleton implementation
KeyboardLayoutManager& KeyboardLayoutManager::getInstance() {
    static KeyboardLayoutManager instance;
    return instance;
}

void KeyboardLayoutManager::loadLayouts(const QString& configDir) {
    layouts.clear();
    qCDebug(log_keyboard_layouts) << "Loading keyboard layouts from directory:" << configDir;

    // Try loading from filesystem first
    QDir dir(configDir);
    if (dir.exists()) {
        QStringList filters;
        filters << "*.json";
        QFileInfoList files = dir.entryInfoList(filters, QDir::Files);
        
        qCDebug(log_keyboard_layouts) << "Found" << files.size() << "layout files in filesystem.";
        
        for (const QFileInfo& file : files) {
            qCDebug(log_keyboard_layouts) << "Processing file from filesystem:" << file.fileName();
            KeyboardLayoutConfig config = KeyboardLayoutConfig::fromJsonFile(file.absoluteFilePath());
            if (!config.name.isEmpty()) {
                layouts[config.name] = config;
                qCDebug(log_keyboard_layouts) << "Loaded layout from filesystem:" << config.name;
            }
        }
    }

    // Then try loading from resources
    QDir resourceDir(":/config/keyboards");
    if (resourceDir.exists()) {
        QStringList filters;
        filters << "*.json";
        QFileInfoList files = resourceDir.entryInfoList(filters, QDir::Files);
        
        qCDebug(log_keyboard_layouts) << "Found" << files.size() << "layout files in resources.";
        
        for (const QFileInfo& file : files) {
            qCDebug(log_keyboard_layouts) << "Processing file from resources:" << file.fileName();
            KeyboardLayoutConfig config = KeyboardLayoutConfig::fromJsonFile(file.absoluteFilePath());
            if (!config.name.isEmpty()) {
                layouts[config.name] = config;
                qCDebug(log_keyboard_layouts) << "Loaded layout from resources:" << config.name;
            }
        }
    }

    qCDebug(log_keyboard_layouts) << "Finished loading layouts. Total layouts loaded:" << layouts.size();
    if (layouts.isEmpty()) {
        qWarning() << "No keyboard layouts were loaded! Make sure the JSON files exist in either" 
                  << configDir << "or in the resources.";
    }
}

KeyboardLayoutConfig KeyboardLayoutManager::getLayout(const QString& name) const {
    return layouts.value(name);
}

QStringList KeyboardLayoutManager::getAvailableLayouts() const {
    return layouts.keys();
}
