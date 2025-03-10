#ifndef MS2109_H
#define MS2109_H

#include <QtGlobal>
#include <cstdint>

const std::string latest_ms2109_firmware_version = "19021B0D";

const unsigned char ms2109_firmware[] = { // version 19021B0D
    0xA5, 0x5A, 0x05, 0x79, 0x0B, 0x12, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x19, 0x02, 0x1B, 0x0D,
    0x0C, 0x4F, 0x70, 0x65, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0D, 0x4F, 0x70, 0x65, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x41, 0xFF, 0xFF, 0xFF,
    0x90, 0xDE, 0x1C, 0xEF, 0xF0, 0x12, 0xCC, 0x4A, 0x90, 0xDE, 0x1C, 0xE0, 0xFF, 0x02, 0xD0, 0x85,
    0x02, 0xCF, 0xF6, 0x90, 0xDE, 0x09, 0x12, 0xD1, 0x35, 0xA3, 0xEA, 0xF0, 0xA3, 0xE9, 0xF0, 0x12,
    0x55, 0x08, 0x22, 0xEF, 0x25, 0xE0, 0x24, 0x78, 0xF5, 0x82, 0xE4, 0x34, 0xC6, 0xF5, 0x83, 0x22,
    0x90, 0xDE, 0x18, 0xE0, 0x04, 0xF0, 0x90, 0xC7, 0x77, 0xE0, 0x04, 0xF0, 0x70, 0x06, 0x90, 0xC7,
    0x76, 0xE0, 0x04, 0xF0, 0x90, 0xF0, 0x05, 0xE4, 0xF0, 0x22, 0xEF, 0x12, 0xD1, 0x00, 0xCC, 0x79,
    0x00, 0xCC, 0xA1, 0x01, 0xCC, 0xD7, 0x02, 0xCD, 0xBA, 0x05, 0xCC, 0xCE, 0x08, 0xCD, 0x31, 0x0A,
    0xCC, 0xA1, 0x0B, 0xCD, 0x18, 0x0C, 0xCC, 0xA1, 0x0E, 0xCD, 0x38, 0x0F, 0xCD, 0x72, 0x10, 0xCD,
    0x88, 0x13, 0xCD, 0x7F, 0x14, 0x00, 0x00, 0xCD, 0xE3, 0x90, 0xC7, 0x81, 0x74, 0x04, 0xF0, 0xA3,
    0x74, 0x1C, 0xF0, 0xA3, 0x74, 0x20, 0xF0, 0x90, 0xF8, 0x0B, 0x74, 0xC1, 0xF0, 0x90, 0xF8, 0x14,
    0x74, 0x23, 0xF0, 0x90, 0xC6, 0x97, 0x74, 0x02, 0xF0, 0xE4, 0x90, 0xC7, 0x60, 0xF0, 0x02, 0xCD,
    0xDF, 0x90, 0xFE, 0x20, 0x74, 0x2A, 0xF0, 0x12, 0x60, 0x3C, 0x90, 0xF8, 0x14, 0x74, 0x33, 0xF0,
    0x14, 0xF0, 0x12, 0x58, 0x84, 0x90, 0xF9, 0x2C, 0x74, 0x20, 0xF0, 0x90, 0xE3, 0x3C, 0x74, 0xF5,
    0xF0, 0x74, 0x0F, 0x12, 0xD1, 0x63, 0x90, 0xF8, 0x05, 0xE0, 0x54, 0xFC, 0xF0, 0x22, 0x7B, 0xFF,
    0x7A, 0xCE, 0x79, 0xF6, 0x02, 0xD1, 0x26, 0x90, 0xF1, 0xF0, 0xE0, 0x70, 0x0F, 0xE5, 0x3B, 0x60,
    0x0B, 0x30, 0xE7, 0x05, 0xE4, 0xF5, 0x3B, 0x80, 0x03, 0x43, 0x3B, 0x80, 0x90, 0xF0, 0x02, 0xE0,
    0x60, 0x19, 0x90, 0xEF, 0xE0, 0xE0, 0x30, 0xE6, 0x12, 0x90, 0xEF, 0xE8, 0x74, 0x40, 0x12, 0xD1,
    0x64, 0xA3, 0xF0, 0x90, 0xC7, 0x76, 0xF0, 0xA3, 0x74, 0xC8, 0xF0, 0xE5, 0x9D, 0x64, 0x07, 0x70,
    0x03, 0x02, 0xCD, 0xE3, 0x75, 0x9D, 0x07, 0x22, 0x30, 0x00, 0x03, 0x12, 0xCD, 0xE4, 0x90, 0xF9,
    0xAF, 0x74, 0x22, 0xF0, 0x74, 0x02, 0xF0, 0xE5, 0x35, 0xF4, 0x54, 0x01, 0x90, 0xFE, 0x80, 0xF0,
    0x22, 0x90, 0xF9, 0xAF, 0x74, 0x22, 0xF0, 0x22, 0xE4, 0x90, 0xC5, 0x4F, 0xF0, 0x90, 0xEF, 0xD0,
    0xF0, 0x74, 0x30, 0x12, 0xD1, 0x63, 0x90, 0xE8, 0x00, 0x74, 0x10, 0xF0, 0xA3, 0x74, 0x4F, 0x12,
    0xD1, 0x64, 0x90, 0xFA, 0xB3, 0xE0, 0xB4, 0x55, 0x03, 0x74, 0x44, 0xF0, 0x90, 0xFA, 0xB5, 0xE0,
    0xB4, 0x55, 0x03, 0x74, 0x44, 0xF0, 0x90, 0xFA, 0xB7, 0xE0, 0x64, 0x55, 0x70, 0x75, 0x74, 0x44,
    0xF0, 0x22, 0x90, 0xE8, 0x00, 0x74, 0x10, 0xF0, 0xA3, 0x74, 0x5F, 0x12, 0xD1, 0x64, 0x22, 0x12,
    0xCD, 0xE4, 0x7F, 0xFF, 0x02, 0x69, 0xFB, 0x22, 0x90, 0xC7, 0x5B, 0xE0, 0x64, 0x07, 0x60, 0x1B,
    0x90, 0xE3, 0x61, 0xE0, 0x30, 0xE3, 0x14, 0x90, 0xE2, 0x68, 0xE0, 0x54, 0x0F, 0xFF, 0xBF, 0x0F,
    0x0A, 0x90, 0xE2, 0x54, 0x74, 0xCC, 0x12, 0xD1, 0x64, 0xA3, 0xF0, 0x90, 0xEF, 0xF0, 0x74, 0x10,
    0x12, 0xD1, 0x64, 0xA3, 0xF0, 0x7F, 0x01, 0x02, 0xD1, 0x5A, 0x12, 0xD1, 0x6F, 0x90, 0xDE, 0x19,
    0xEE, 0xF0, 0xA3, 0xEF, 0xF0, 0xC3, 0x94, 0xF4, 0xEE, 0x94, 0x01, 0x40, 0x0E, 0x90, 0xDE, 0x18,
    0xE0, 0x94, 0x0A, 0x40, 0x0E, 0x12, 0xD1, 0x6B, 0xE4, 0x80, 0x04, 0x12, 0xD1, 0x6B, 0xE4, 0x90,
    0xDE, 0x18, 0xF0, 0x22, 0x90, 0xF8, 0x06, 0x74, 0x30, 0xF0, 0x90, 0xC6, 0xC4, 0xE0, 0xFE, 0xA3,
    0xE0, 0xFF, 0x90, 0xC6, 0xAF, 0xE0, 0xFC, 0xA3, 0xE0, 0xFD, 0xC3, 0x9F, 0xEC, 0x9E, 0x50, 0x06,
    0xAE, 0x04, 0xAF, 0x05, 0x80, 0x00, 0xAD, 0x07, 0xAC, 0x06, 0x90, 0xC6, 0xC6, 0xE0, 0xFE, 0xA3,
    0xE0, 0xFF, 0xC3, 0x90, 0xC6, 0xB2, 0xE0, 0x9F, 0x90, 0xC6, 0xB1, 0xE0, 0x9E, 0x40, 0x24, 0x90,
    0xC6, 0xAA, 0xE0, 0x30, 0xE0, 0x1D, 0xE5, 0x36, 0x94, 0x03, 0x50, 0x24, 0xE5, 0x37, 0x94, 0x0A,
    0x40, 0x1E, 0x90, 0xC6, 0xB5, 0xE0, 0xD3, 0x94, 0x0B, 0x40, 0x15, 0x90, 0xF8, 0x06, 0x74, 0x20,
    0xF0, 0x80, 0x0D, 0xD3, 0xED, 0x94, 0xA0, 0xEC, 0x94, 0x05, 0x40, 0x04, 0x7C, 0x05, 0x7D, 0xA0,
    0x90, 0xF8, 0xE6, 0xED, 0xF0, 0xEC, 0xF9, 0xA3, 0xF0, 0xD3, 0x90, 0xC6, 0xB0, 0xE0, 0x9D, 0x90,
    0xC6, 0xAF, 0xE0, 0x9C, 0x50, 0x06, 0x90, 0xF8, 0xE1, 0x74, 0x47, 0xF0, 0x90, 0xC6, 0xAA, 0xE0,
    0x90, 0xF9, 0x26, 0x30, 0xE0, 0x11, 0x74, 0x0F, 0xF0, 0x90, 0xF9, 0x29, 0x74, 0x1F, 0xF0, 0x90,
    0xF9, 0x36, 0x74, 0x0F, 0xF0, 0x80, 0x0F, 0x74, 0x05, 0xF0, 0x90, 0xF9, 0x29, 0x74, 0x0B, 0xF0,
    0x90, 0xF9, 0x36, 0x74, 0x05, 0xF0, 0x90, 0xF9, 0x25, 0x74, 0xEF, 0xF0, 0x90, 0xF9, 0x28, 0x74,
    0xDE, 0xF0, 0x90, 0xF9, 0x35, 0x74, 0xEF, 0xF0, 0x90, 0xF9, 0x47, 0x74, 0x0C, 0xF0, 0x90, 0xF9,
    0x4A, 0x74, 0x12, 0xF0, 0xEC, 0xC3, 0x13, 0xED, 0x13, 0xFB, 0x90, 0xF9, 0x37, 0xF0, 0xEC, 0xC3,
    0x13, 0xFF, 0xA3, 0xF0, 0xA3, 0xEB, 0xF0, 0xA3, 0xEF, 0xF0, 0x90, 0xFD, 0x40, 0xED, 0xF0, 0xA3,
    0xE9, 0xF0, 0xAF, 0x05, 0xAE, 0x04, 0x90, 0xC6, 0xC4, 0xE0, 0xFC, 0xA3, 0xE0, 0xFD, 0xE4, 0xFB,
    0x12, 0xD1, 0x50, 0x90, 0xFD, 0x3B, 0xEF, 0xF0, 0xEE, 0xA3, 0xF0, 0x90, 0xF8, 0xE0, 0x74, 0x01,
    0xF0, 0x90, 0xFD, 0x00, 0xF0, 0x22, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x21, 0x57,
    0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x1D, 0x01, 0x04, 0x82, 0x46, 0x27, 0x78, 0x2A, 0xD9,
    0xB0, 0xA3, 0x57, 0x49, 0x9C, 0x25, 0x11, 0x49, 0x4B, 0x21, 0x08, 0x00, 0x71, 0x40, 0x81, 0xC0,
    0x81, 0x00, 0x81, 0x40, 0x81, 0x80, 0x95, 0x00, 0xA9, 0xC0, 0xB3, 0x00, 0x02, 0x3A, 0x80, 0x18,
    0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x00, 0x00,
    0x00, 0xFD, 0x00, 0x17, 0x55, 0x1E, 0x64, 0x1E, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0xF7, 0x00, 0x0A, 0x00, 0x40, 0xC6, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x48, 0x44, 0x20, 0x54, 0x4F, 0x20, 0x55, 0x53, 0x42,
    0x0A, 0x20, 0x20, 0x20, 0x01, 0x2A, 0x02, 0x03, 0x2C, 0xF1, 0x51, 0x01, 0x02, 0x03, 0x04, 0x11,
    0x12, 0x13, 0x1F, 0x20, 0x21, 0x22, 0x3C, 0x3D, 0x3E, 0x90, 0x5F, 0x64, 0x23, 0x09, 0x07, 0x07,
    0x83, 0x01, 0x00, 0x00, 0x67, 0x03, 0x0C, 0x00, 0x10, 0x00, 0xB8, 0x3C, 0xE5, 0x0E, 0x61, 0x60,
    0x66, 0x65, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E, 0x28, 0x55, 0x00, 0xC4, 0x8E,
    0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00,
    0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x8C, 0x0A, 0xD0, 0x90, 0x20, 0x40, 0x31, 0x20, 0x0C, 0x40,
    0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x4E, 0x1F, 0x00, 0x80, 0x51, 0x00, 0x1E, 0x30,
    0x40, 0x80, 0x37, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xE5, 0x0B, 0x64, 0x80, 0x70, 0x61, 0xE5, 0x0C, 0x64, 0x06,
    0x70, 0x5B, 0xE5, 0x10, 0x64, 0x09, 0x70, 0x04, 0xE5, 0x0F, 0x64, 0x04, 0x70, 0x4F, 0xE5, 0x0E,
    0x64, 0x03, 0x70, 0x04, 0xE5, 0x0D, 0x64, 0x03, 0x70, 0x43, 0x90, 0xC6, 0x76, 0x74, 0x12, 0xF0,
    0xA3, 0x74, 0x03, 0xF0, 0xE4, 0xFF, 0x74, 0x00, 0x2F, 0xF5, 0x82, 0xE4, 0x34, 0xDE, 0xF5, 0x83,
    0xE0, 0xFE, 0xC3, 0x94, 0x30, 0x40, 0x0D, 0xEE, 0xD3, 0x94, 0x39, 0x50, 0x07, 0x12, 0xCC, 0x23,
    0xEE, 0xF0, 0x80, 0x06, 0x12, 0xCC, 0x23, 0x74, 0x3F, 0xF0, 0xEF, 0x25, 0xE0, 0x24, 0x79, 0xF5,
    0x82, 0xE4, 0x34, 0xC6, 0xF5, 0x83, 0xE4, 0xF0, 0x0F, 0xEF, 0xB4, 0x08, 0xC9, 0x12, 0xD1, 0x73,
    0xE5, 0x0B, 0x30, 0xE5, 0x1F, 0xE5, 0x0C, 0xB4, 0x01, 0x1A, 0xAF, 0x10, 0xBF, 0x01, 0x15, 0xE5,
    0x0D, 0xFF, 0x64, 0x01, 0x60, 0x05, 0xEF, 0x64, 0x02, 0x70, 0x09, 0xE4, 0x90, 0xC0, 0x1C, 0xF0,
    0xA3, 0x74, 0x08, 0xF0, 0x22, 0xEF, 0x14, 0x60, 0x33, 0x14, 0x60, 0x41, 0x24, 0x02, 0x70, 0x40,
    0xE4, 0x90, 0xDF, 0x01, 0xF0, 0x90, 0xDE, 0x08, 0xF0, 0xD2, 0xB0, 0x43, 0xB1, 0x01, 0xA2, 0xA0,
    0x33, 0x90, 0xDF, 0x00, 0xF0, 0x90, 0xC6, 0x98, 0x74, 0x03, 0xF0, 0x7B, 0x01, 0x7A, 0xDE, 0x79,
    0x00, 0x7D, 0x08, 0x7C, 0x00, 0x7F, 0xC0, 0x7E, 0x07, 0x02, 0xCC, 0x13, 0x90, 0xF8, 0x0B, 0xE0,
    0x44, 0x01, 0xF0, 0xA3, 0xE0, 0x54, 0x0F, 0xF0, 0xE0, 0x44, 0x20, 0xF0, 0x22, 0x12, 0xD0, 0xD1,
    0x22, 0xA2, 0xA0, 0xE4, 0x33, 0xFF, 0x90, 0xDF, 0x00, 0xE0, 0x6F, 0x60, 0x05, 0xA2, 0xA0, 0xE4,
    0x33, 0xF0, 0x90, 0xDF, 0x01, 0xE0, 0xFF, 0x90, 0xDE, 0x08, 0xE0, 0x6F, 0x60, 0x11, 0xEF, 0xF0,
    0x90, 0xF8, 0x0C, 0x30, 0xE0, 0x05, 0xE0, 0x44, 0x10, 0xF0, 0x22, 0xE0, 0x54, 0xEF, 0xF0, 0x22,
    0xD0, 0x83, 0xD0, 0x82, 0xF8, 0xE4, 0x93, 0x70, 0x12, 0x74, 0x01, 0x93, 0x70, 0x0D, 0xA3, 0xA3,
    0x93, 0xF8, 0x74, 0x01, 0x93, 0xF5, 0x82, 0x88, 0x83, 0xE4, 0x73, 0x74, 0x02, 0x93, 0x68, 0x60,
    0xEF, 0xA3, 0xA3, 0xA3, 0x80, 0xDF, 0x90, 0xDE, 0x15, 0xEB, 0xF0, 0xA3, 0xEA, 0xF0, 0xA3, 0xE9,
    0xF0, 0x12, 0x63, 0x45, 0x22, 0xEE, 0xF0, 0xA3, 0xEF, 0xF0, 0xA3, 0xEC, 0xF0, 0xA3, 0xED, 0xF0,
    0xA3, 0xEB, 0xF0, 0x22, 0x78, 0xFF, 0xE4, 0xF6, 0xD8, 0xFD, 0x75, 0x81, 0x3C, 0x02, 0xD1, 0x77,
    0x90, 0xDE, 0x10, 0x12, 0xD1, 0x35, 0x12, 0x52, 0xDD, 0x22, 0x90, 0xDE, 0x1B, 0xEF, 0xF0, 0x12,
    0x69, 0xFB, 0x22, 0xA3, 0xF0, 0xA3, 0xE4, 0xF0, 0xA3, 0xF0, 0x22, 0x12, 0x30, 0x11, 0x22, 0x12,
    0x57, 0x1B, 0x22, 0x12, 0x2A, 0xD0, 0x22, 0x80, 0xFE, 0x17, 0x03, 0xA4, 0x98
};

const uint16_t ADDR_HDMI_CONNECTION_STATUS = 0xFA8C;
// 0xDF00 bit0: GPIO0 reads the hard switch status, 1 means switchable usb connects to the target, 0 means switchable usb connects to the host
const uint16_t ADDR_GPIO0 = 0xDF00;
// 0xDF01 bit5: SPDIFOUT reads the soft switch status, 1 means switchable usb connects to the target, 0 means switchable usb connects to the host
const uint16_t ADDR_SPDIFOUT = 0xDF01;

const uint16_t ADDR_EEPROM = 0x0000;

const uint16_t ADDR_FIRMWARE_VERSION_0 = 0xCBDC;
const uint16_t ADDR_FIRMWARE_VERSION_1 = 0xCBDD;
const uint16_t ADDR_FIRMWARE_VERSION_2 = 0xCBDE;
const uint16_t ADDR_FIRMWARE_VERSION_3 = 0xCBDF;

const uint16_t ADDR_WIDTH_H = 0xC738;
const uint16_t ADDR_WIDTH_L = 0xC739;

const uint16_t ADDR_HEIGHT_H = 0xC73A;
const uint16_t ADDR_HEIGHT_L = 0xC73B;

const uint16_t ADDR_FPS_H = 0xC73E;
const uint16_t ADDR_FPS_L = 0xC73F;

const quint8 CMD_XDATA_WRITE = 0xB6;
const quint8 CMD_XDATA_READ = 0xB5;

const quint8 CMD_EEPROM_WRITE = 0xE6;
const quint8 CMD_EEPROM_READ = 0xE5;

#endif // MS2109_H
