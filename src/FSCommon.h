#pragma once

#include "configuration.h"

// Cross platform filesystem API

#if defined(ARCH_PORTDUINO)
// Portduino version
#include "PortduinoFS.h"
#define FSCom PortduinoFS
#define FSBegin() true
#define FILE_O_WRITE "w"
#define FILE_O_READ "r"
#endif

#if defined(ARCH_STM32WL)
#include "platform/stm32wl/InternalFileSystem.h" // STM32WL version
#define FSCom InternalFS
#define FSBegin() FSCom.begin()
using namespace LittleFS_Namespace;
#endif

#if defined(ARCH_APOLLO3)
// Apollo series 2 Kbytes (8 rows of 256 bytes)
#include <EEPROM.h>
#include <OSFS.h>

uint16_t OSFS::startOfEEPROM = 1;
uint16_t OSFS::endOfEEPROM = 2048;

// Useful consts
const OSFS::result noerr = OSFS::result::NO_ERROR;
const OSFS::result notfound = OSFS::result::FILE_NOT_FOUND;

// 3) How do I read from the medium?
void OSFS::readNBytes(uint16_t address, unsigned int num, byte *output)
{
    for (uint16_t i = address; i < address + num; i++) {
        *output = EEPROM.read(i);
        output++;
    }
}

// 4) How to I write to the medium?
void OSFS::writeNBytes(uint16_t address, unsigned int num, const byte *input)
{
    for (uint16_t i = address; i < address + num; i++) {
        EEPROM.update(i, *input);
        input++;
    }
}
#endif

#if defined(ARCH_RP2040)
// RP2040
#include "LittleFS.h"
#define FSCom LittleFS
#define FSBegin() FSCom.begin() // set autoformat
#define FILE_O_WRITE "w"
#define FILE_O_READ "r"
#endif

#if defined(ARCH_ESP32)
// ESP32 version
#include "LittleFS.h"
#define FSCom LittleFS
#define FSBegin() FSCom.begin(true) // format on failure
#define FILE_O_WRITE "w"
#define FILE_O_READ "r"
#endif

#if defined(ARCH_NRF52)
// NRF52 version
#include "InternalFileSystem.h"
#define FSCom InternalFS
#define FSBegin() FSCom.begin() // InternalFS formats on failure
using namespace Adafruit_LittleFS_Namespace;
#endif

void fsInit();
bool copyFile(const char *from, const char *to);
bool renameFile(const char *pathFrom, const char *pathTo);
void listDir(const char *dirname, uint8_t levels, bool del);
void rmDir(const char *dirname);
void setupSDCard();