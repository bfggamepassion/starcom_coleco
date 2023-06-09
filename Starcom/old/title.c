#include <coleco.h>

const byte TITLE_NAMERLE[] = {
  0x81, 0x5C, 0x03, 0x65, 0x5C, 0x5C, 0x72, 0x84, 0x5C, 0x00, 0x8F, 0x85, 0x5C, 0x00, 0x89,
  0x85, 0x5C, 0x02, 0x98, 0x5C, 0xD8, 0x85, 0x5C, 0x00, 0x66, 0x86, 0x5C, 0x02, 0x88, 0x5C, 0x94,
  0x87, 0x5C, 0x00, 0x6C, 0x87, 0x5C, 0x00, 0x6B, 0x91, 0x5C, 0x00, 0x9E, 0x84, 0x5C, 0x06, 0xC7,
  0x5C, 0x5C, 0x64, 0x5C, 0x5C, 0x71, 0x86, 0x5C, 0x05, 0x73, 0x5C, 0x73, 0x5C, 0x5C, 0x89, 0x91,
  0x5C, 0x00, 0x75, 0x82, 0x5C, 0x40, 0x5F, 0x67, 0x67, 0x6D, 0x74, 0x76, 0x79, 0x7F, 0x84, 0x8A,
  0x90, 0x95, 0x99, 0x9F, 0xA3, 0x5C, 0xAB, 0x95, 0xB5, 0xBA, 0xBF, 0xC4, 0x8A, 0xCB, 0x95, 0xD3,
  0x90, 0xDE, 0xE2, 0xE9, 0x5C, 0x5C, 0x60, 0x68, 0x68, 0x6E, 0x69, 0x77, 0x7A, 0x80, 0x85, 0x8B,
  0x91, 0x96, 0x9A, 0xA0, 0xA4, 0xA8, 0xAC, 0xB1, 0xB6, 0xBB, 0xC0, 0x5C, 0x5C, 0xCC, 0xD0, 0xD4,
  0xD9, 0xDF, 0xE3, 0xEA, 0x5C, 0x5C, 0x61, 0x83, 0x69, 0x1B, 0x77, 0x7B, 0x81, 0x86, 0x8C, 0x5C,
  0x97, 0x9B, 0xA1, 0xA5, 0xA9, 0xAD, 0xB2, 0xB7, 0xBC, 0xC1, 0xC5, 0xC8, 0xCD, 0xD1, 0xD5, 0xDA,
  0xE0, 0xE4, 0xEB, 0xEF, 0x5C, 0x62, 0x83, 0x6A, 0x18, 0x78, 0x7C, 0x82, 0x87, 0x8D, 0x5C, 0x87,
  0x9C, 0xA2, 0x5C, 0xAA, 0xAE, 0xB3, 0xB8, 0xBD, 0xC2, 0x87, 0xC9, 0xCE, 0x87, 0xD6, 0xDB, 0x9C,
  0xE5, 0xEC, 0x92, 0x5C, 0x00, 0xB4, 0x89, 0x5C, 0x00, 0x63, 0x85, 0x5C, 0x00, 0x6F, 0x86, 0x5C,
  0x00, 0x98, 0x86, 0x5C, 0x00, 0x64, 0x8B, 0x5C, 0x00, 0x63, 0x84, 0x5C, 0x00, 0x7D, 0x8E, 0x5C,
  0x00, 0x93, 0x82, 0x5C, 0x03, 0xDC, 0xE1, 0x73, 0xED, 0x8F, 0x5C, 0x00, 0x83, 0x82, 0x5C, 0x00,
  0xB9, 0x90, 0x5C, 0x00, 0x75, 0x83, 0x5C, 0x03, 0x75, 0x5C, 0x5C, 0x9D, 0x8E, 0x5C, 0x05, 0xE6,
  0xEE, 0x5C, 0x5D, 0x5C, 0x6B, 0x8D, 0x5C, 0x00, 0xAF, 0x83, 0x5C, 0x00, 0xC6, 0xBC, 0x5C, 0x00,
  0x83, 0x88, 0x5C, 0x03, 0xCA, 0x5C, 0x5C, 0x64, 0x85, 0x5C, 0x00, 0x6C, 0x84, 0x5C, 0x03, 0x98,
  0x5C, 0x5C, 0xB0, 0x8A, 0x5C, 0x00, 0xE7, 0x98, 0x5C, 0x03, 0x89, 0x5C, 0x5C, 0xD7, 0x82, 0x5C,
  0x00, 0xC7, 0x84, 0x5C, 0x00, 0x70, 0x84, 0x5C, 0x00, 0x8E, 0x83, 0x5C, 0x05, 0xA6, 0x5C, 0x5C,
  0xA7, 0x5C, 0xBE, 0x8C, 0x5C, 0x00, 0x6C, 0x84, 0x5C, 0x03, 0x83, 0x5C, 0x5C, 0x92, 0x8E, 0x5C,
  0x00, 0x94, 0x9B, 0x5C, 0x01, 0xCF, 0xD2, 0x82, 0x5C, 0x03, 0xE8, 0x5C, 0x5C, 0x5E, 0x82, 0x5C,
  0x00, 0x71, 0x87, 0x5C, 0x00, 0x9E, 0x84, 0x5C, 0x02, 0x75, 0x5C, 0xC3, 0x84, 0x5C, 0x00, 0xDD,
  0x8A, 0x5C, 0x00, 0x7E, 0x82, 0x5C, 0x00, 0x93, 0x82, 0x5C, 0x00, 0xA7, 0x86, 0x5C, 0x00, 0xCA,
  0x85, 0x5C, 0x00, 0x6F, 0xA0, 0x5C, 0xFF};

const byte TITLE_PATTERNRLE[] = {
  0xFE, 0x00, 0xFE, 0x00, 0x89, 0x00, 0x83, 0x1C, 0x03, 0x00, 0x1C, 0x1C, 0x00, 0x82, 0x77,
  0x84, 0x00, 0x81, 0x36, 0x20, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00, 0x08, 0x3F, 0x68, 0x3E, 0x0B,
  0x7E, 0x08, 0x00, 0x73, 0x77, 0x0E, 0x1C, 0x38, 0x77, 0x67, 0x00, 0x3C, 0x66, 0x3C, 0x38, 0x67,
  0x66, 0x3F, 0x00, 0x1C, 0x1C, 0x38, 0x84, 0x00, 0x01, 0x0E, 0x1C, 0x82, 0x38, 0x04, 0x1C, 0x0E,
  0x00, 0x38, 0x1C, 0x82, 0x0E, 0x08, 0x1C, 0x38, 0x00, 0x00, 0x36, 0x1C, 0x7F, 0x1C, 0x36, 0x82,
  0x00, 0x81, 0x1C, 0x02, 0x7F, 0x1C, 0x1C, 0x86, 0x00, 0x81, 0x1C, 0x00, 0x38, 0x82, 0x00, 0x00,
  0x7F, 0x88, 0x00, 0x81, 0x1C, 0x12, 0x00, 0x03, 0x07, 0x0E, 0x1C, 0x38, 0x70, 0x60, 0x00, 0x3E,
  0x63, 0x67, 0x6B, 0x73, 0x63, 0x3E, 0x00, 0x0C, 0x1C, 0x83, 0x0C, 0x11, 0x1E, 0x00, 0x3E, 0x67,
  0x06, 0x0C, 0x18, 0x30, 0x7F, 0x00, 0x3E, 0x63, 0x03, 0x0E, 0x03, 0x63, 0x3E, 0x00, 0x82, 0x63,
  0x00, 0x3F, 0x82, 0x03, 0x14, 0x00, 0x7F, 0x60, 0x60, 0x7E, 0x03, 0x03, 0x7E, 0x00, 0x3E, 0x60,
  0x60, 0x7E, 0x63, 0x63, 0x3E, 0x00, 0x7F, 0x03, 0x06, 0x0C, 0x82, 0x18, 0x16, 0x00, 0x3E, 0x63,
  0x63, 0x3E, 0x63, 0x63, 0x3E, 0x00, 0x3E, 0x63, 0x63, 0x3F, 0x03, 0x03, 0x3E, 0x00, 0x00, 0x1C,
  0x1C, 0x00, 0x1C, 0x1C, 0x82, 0x00, 0x81, 0x1C, 0x0B, 0x00, 0x1C, 0x1C, 0x38, 0x00, 0x0E, 0x1C,
  0x38, 0x70, 0x38, 0x1C, 0x0E, 0x82, 0x00, 0x02, 0x7F, 0x00, 0x7F, 0x82, 0x00, 0x29, 0x70, 0x38,
  0x1C, 0x0E, 0x1C, 0x38, 0x70, 0x00, 0x3E, 0x77, 0x07, 0x0E, 0x1C, 0x00, 0x1C, 0x00, 0x3C, 0x66,
  0x6E, 0x6E, 0x60, 0x62, 0x3C, 0x00, 0x1C, 0x36, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x00, 0x7C, 0x66,
  0x66, 0x7E, 0x63, 0x63, 0x7E, 0x00, 0x1E, 0x33, 0x82, 0x60, 0x04, 0x33, 0x1E, 0x00, 0x7C, 0x66,
  0x82, 0x63, 0x0E, 0x66, 0x7C, 0x00, 0x7F, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7F, 0x00, 0x7F, 0x60,
  0x60, 0x7C, 0x82, 0x60, 0x08, 0x00, 0x1E, 0x33, 0x60, 0x67, 0x63, 0x33, 0x1E, 0x00, 0x82, 0x63,
  0x00, 0x7F, 0x82, 0x63, 0x01, 0x00, 0x3C, 0x84, 0x18, 0x02, 0x3C, 0x00, 0x0F, 0x83, 0x06, 0x0A,
  0x66, 0x3C, 0x00, 0x63, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0x63, 0x00, 0x85, 0x60, 0x05, 0x7F, 0x00,
  0x77, 0x7F, 0x6B, 0x6B, 0x82, 0x63, 0x09, 0x00, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x63, 0x63, 0x00,
  0x3E, 0x84, 0x63, 0x05, 0x3E, 0x00, 0x7E, 0x63, 0x63, 0x7E, 0x82, 0x60, 0x01, 0x00, 0x3E, 0x83,
  0x63, 0x13, 0x3E, 0x0F, 0x00, 0x7E, 0x63, 0x63, 0x7E, 0x6C, 0x66, 0x63, 0x00, 0x3F, 0x60, 0x60,
  0x3E, 0x03, 0x03, 0x7E, 0x00, 0x7E, 0x85, 0x18, 0x00, 0x00, 0x85, 0x63, 0x01, 0x3F, 0x00, 0x82,
  0x63, 0x81, 0x36, 0x81, 0x1C, 0x02, 0x00, 0x63, 0x63, 0x82, 0x6B, 0x0E, 0x7F, 0x36, 0x00, 0x63,
  0x77, 0x3E, 0x1C, 0x3E, 0x77, 0x63, 0x00, 0x63, 0x63, 0x77, 0x3E, 0x82, 0x1C, 0x09, 0x00, 0x7F,
  0x07, 0x0E, 0x1C, 0x38, 0x70, 0x7F, 0x00, 0x3E, 0x84, 0x38, 0x01, 0x3E, 0x00, 0x88, 0xFF, 0x02,
  0xFD, 0xF8, 0xFD, 0x87, 0xFF, 0x04, 0xF7, 0xE3, 0xF7, 0xFF, 0xFF, 0x99, 0xFE, 0x8A, 0xFF, 0x00,
  0xFB, 0x85, 0xFF, 0x00, 0xDF, 0x88, 0xFF, 0x02, 0xBF, 0xE0, 0xBF, 0x87, 0xFF, 0x0A, 0xAA, 0xFF,
  0xAA, 0xFF, 0xAA, 0xFF, 0xAA, 0xFF, 0xAA, 0xFF, 0xAA, 0x99, 0xFF, 0x02, 0xF7, 0xFF, 0xDF, 0x86,
  0xFF, 0x8D, 0x80, 0x86, 0xFF, 0x00, 0xEF, 0x83, 0xFF, 0x00, 0xFE, 0x86, 0xFF, 0x00, 0x80, 0x86,
  0xFF, 0x00, 0xFD, 0x84, 0xFF, 0x00, 0xFD, 0x93, 0xFF, 0x02, 0xBF, 0xFF, 0xFF, 0x91, 0xF8, 0x87,
  0xFF, 0x00, 0xFE, 0x82, 0xFC, 0x83, 0xF8, 0x82, 0xFC, 0x00, 0xFE, 0x84, 0xFF, 0x86, 0xF8, 0x86,
  0xFF, 0x00, 0xBF, 0x86, 0xFF, 0x00, 0xEF, 0x85, 0xFF, 0x00, 0xC0, 0x85, 0xFF, 0x02, 0xFC, 0xF8,
  0xF8, 0x84, 0xFF, 0x00, 0xC0, 0x8A, 0xFF, 0x00, 0xF7, 0x88, 0xFF, 0x00, 0xFD, 0x91, 0xFF, 0x02,
  0xF8, 0xFC, 0xFC, 0x8D, 0xFF, 0x02, 0xBF, 0xE0, 0xBF, 0x87, 0xFF, 0x00, 0xF7, 0x82, 0xFF, 0x86,
  0xFC, 0x83, 0xFF, 0x04, 0xC0, 0xF0, 0xF0, 0xF8, 0xF8, 0x84, 0xFC, 0x81, 0xF8, 0x02, 0xF0, 0xE0,
  0xC0, 0x84, 0xFF, 0x00, 0xBF, 0x88, 0xFF, 0x00, 0x80, 0x88, 0xFF, 0x86, 0x80, 0x88, 0xFF, 0x00,
  0xFB, 0x83, 0xFF, 0x00, 0x80, 0x88, 0xFF, 0x00, 0xBF, 0xA0, 0xFF, 0x00, 0xEF, 0x85, 0xFF, 0x86,
  0xFE, 0x85, 0xFF, 0x82, 0xFE, 0x03, 0xFC, 0xF8, 0xF8, 0xF0, 0x82, 0xE0, 0x88, 0xFF, 0x00, 0xF7,
  0x83, 0xFF, 0x00, 0xBF, 0x89, 0xFF, 0x0B, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0,
  0xC0, 0x80, 0x80, 0x83, 0xFF, 0x06, 0xFE, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0x88, 0xFF, 0x81,
  0xFE, 0x88, 0xFF, 0x08, 0xCF, 0x8F, 0x8F, 0xF8, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0x86, 0xFF, 0x01,
  0xBF, 0xFD, 0x86, 0xFF, 0x81, 0x80, 0x81, 0xC0, 0x81, 0xE0, 0x81, 0xF0, 0x81, 0xF8, 0x81, 0xFC,
  0x82, 0xFE, 0x82, 0xFF, 0x00, 0x80, 0x88, 0xFF, 0x86, 0xF0, 0x81, 0xFF, 0x8B, 0xF0, 0x81, 0x8F,
  0x86, 0xFF, 0x00, 0xFD, 0x87, 0xFF, 0x00, 0xDF, 0x90, 0xFF, 0x02, 0xE3, 0xE1, 0xE1, 0x82, 0xE0,
  0x8A, 0xFF, 0x00, 0xF7, 0x84, 0xFF, 0x01, 0xF8, 0xFE, 0x84, 0xFF, 0x81, 0xE0, 0x84, 0xFF, 0x08,
  0xFE, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFF, 0x80, 0xC0, 0x86, 0xFF, 0x02, 0xEF, 0xC7, 0xEF, 0x88,
  0xFF, 0x02, 0xFE, 0x83, 0xC3, 0x82, 0xC7, 0x83, 0xCF, 0x00, 0x87, 0x82, 0xF8, 0x81, 0xFC, 0x04,
  0xFE, 0xFF, 0x80, 0x80, 0xC0, 0x8B, 0xFF, 0x04, 0xFD, 0xFF, 0xF8, 0xC0, 0x80, 0x83, 0xFF, 0x03,
  0xFE, 0xFC, 0xF8, 0xF8, 0x83, 0xF0, 0x81, 0xF8, 0x01, 0xFC, 0xFE, 0x83, 0xFF, 0x02, 0x80, 0xC0,
  0xF0, 0x84, 0xFF, 0x00, 0xEF, 0x86, 0xFF, 0x00, 0xF7, 0x8F, 0xFF, 0x00, 0xEF, 0x86, 0xFF, 0x00,
  0xF7, 0x89, 0xFF, 0x86, 0xFC, 0x88, 0xFF, 0x00, 0xEF, 0x86, 0xFF, 0x03, 0xF8, 0xE0, 0x80, 0x80,
  0x83, 0xFF, 0x86, 0xFE, 0x83, 0xFF, 0x81, 0x80, 0x02, 0xC0, 0xE0, 0xEF, 0x88, 0xFF, 0x00, 0xFE,
  0x84, 0xFF, 0x01, 0xFC, 0xFE, 0x84, 0xFF, 0x01, 0xFE, 0xFC, 0x87, 0xFF, 0x02, 0x80, 0xC0, 0x80,
  0x84, 0xFF, 0x04, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0x8C, 0xFE, 0x81, 0xFC, 0x02, 0xF8, 0xF0, 0xE0,
  0x85, 0xFF, 0x02, 0xBF, 0xE0, 0xBF, 0x8A, 0xFF, 0x00, 0xFB, 0x87, 0x80, 0x8A, 0x81, 0x89, 0xFF,
  0x02, 0xFE, 0xFC, 0xFE, 0x83, 0xFF, 0x00, 0xBF, 0x86, 0xFF, 0x81, 0xE0, 0x83, 0xF0, 0x81, 0xF8,
  0x02, 0xFC, 0xFD, 0xFD, 0x82, 0xFF, 0x81, 0x80, 0x83, 0xC0, 0x85, 0xFF, 0x00, 0x80, 0x84, 0xFF,
  0x81, 0xC0, 0x82, 0x80, 0x86, 0xFF, 0x82, 0xF7, 0x83, 0xE7, 0x81, 0xC7, 0x81, 0x87, 0x84, 0xFF,
  0x00, 0xDF, 0x8A, 0xFF, 0x00, 0x80, 0x89, 0xFF, 0x00, 0xEF, 0x83, 0xFF, 0x96, 0xF0, 0x8A, 0xFF,
  0x00, 0x80, 0x86, 0xFF, 0x00, 0xFE, 0x87, 0xFF, 0x00, 0xDF, 0xFC, 0x00, 0x82, 0x00, 0xFF};

const byte TITLE_COLORRLE[] = {
  0xFE, 0x41, 0xFE, 0x41, 0x89, 0x41, 0xFE, 0xF1, 0xFE, 0xF1, 0xFE, 0xF1, 0xDA, 0xF1, 0x88,
  0x10, 0x82, 0x1E, 0x87, 0x10, 0x82, 0x1E, 0x81, 0x10, 0x8D, 0x14, 0x81, 0x1F, 0x81, 0x18, 0x81,
  0x1F, 0x81, 0x18, 0x81, 0x1F, 0x81, 0x18, 0x8A, 0x10, 0x00, 0x1F, 0x85, 0x10, 0x00, 0x1F, 0x88,
  0x10, 0x02, 0x1E, 0xE1, 0x1E, 0x86, 0x10, 0x19, 0x40, 0xF4, 0x40, 0x4F, 0x40, 0xF4, 0x40, 0x4F,
  0x40, 0xF4, 0x40, 0x4F, 0x40, 0x40, 0xF0, 0xF0, 0x80, 0x80, 0xF0, 0xF0, 0x80, 0x80, 0xF0, 0xF0,
  0x80, 0x80, 0x8B, 0x10, 0x02, 0x1F, 0x10, 0x1F, 0x86, 0x10, 0x81, 0x48, 0x81, 0x4F, 0x81, 0x48,
  0x81, 0x4F, 0x81, 0x48, 0x81, 0x4F, 0x81, 0x48, 0x00, 0xF0, 0x85, 0x10, 0x00, 0x1F, 0x83, 0x10,
  0x00, 0x1F, 0x86, 0x10, 0x00, 0xF1, 0x86, 0x10, 0x00, 0x1F, 0x84, 0x10, 0x00, 0x1F, 0x86, 0x10,
  0x81, 0x80, 0x81, 0xF0, 0x81, 0x80, 0x00, 0xF0, 0x85, 0x10, 0x14, 0x1F, 0x10, 0x10, 0x81, 0x81,
  0xF1, 0xF1, 0x81, 0x81, 0xF1, 0xF1, 0x81, 0x81, 0xF1, 0xF1, 0x81, 0x81, 0xF1, 0xF1, 0x81, 0x81,
  0x87, 0x10, 0x83, 0x15, 0x07, 0x14, 0x15, 0x15, 0x14, 0x15, 0x15, 0x14, 0x14, 0x84, 0x10, 0x86,
  0x14, 0x86, 0x10, 0x00, 0x1F, 0x86, 0x10, 0x00, 0x1F, 0x85, 0x10, 0x00, 0x15, 0x84, 0x50, 0x09,
  0x40, 0x51, 0x51, 0x41, 0x50, 0x50, 0x40, 0x40, 0x50, 0x14, 0x82, 0x10, 0x86, 0x40, 0x01, 0x10,
  0x1F, 0x88, 0x10, 0x02, 0x1F, 0x10, 0x10, 0x85, 0x50, 0x00, 0x40, 0x82, 0x10, 0x81, 0x50, 0x81,
  0x40, 0x04, 0x50, 0x40, 0x14, 0x15, 0x14, 0x86, 0x40, 0x86, 0x10, 0x02, 0x1E, 0xE1, 0x1E, 0x87,
  0x10, 0x00, 0x1F, 0x82, 0x10, 0x85, 0x51, 0x00, 0x41, 0x83, 0x10, 0x06, 0x51, 0x41, 0x41, 0x51,
  0x41, 0x41, 0x51, 0x87, 0x41, 0x84, 0x10, 0x00, 0x1F, 0x88, 0x10, 0x00, 0xF1, 0x88, 0x10, 0x82,
  0x15, 0x03, 0x14, 0x15, 0x15, 0x14, 0x88, 0x10, 0x00, 0x1F, 0x83, 0x10, 0x00, 0xF1, 0x88, 0x10,
  0x00, 0x1F, 0x87, 0x10, 0x82, 0x50, 0x0B, 0x40, 0x50, 0x50, 0x40, 0x50, 0x50, 0x40, 0x40, 0x50,
  0x40, 0x40, 0x50, 0x84, 0x40, 0x84, 0x10, 0x00, 0x1F, 0x85, 0x10, 0x82, 0x51, 0x03, 0x41, 0x51,
  0x51, 0x41, 0x85, 0x10, 0x01, 0x14, 0x15, 0x87, 0x14, 0x88, 0x10, 0x00, 0x1F, 0x83, 0x10, 0x00,
  0x1F, 0x89, 0x10, 0x82, 0x15, 0x0C, 0x14, 0x15, 0x15, 0x14, 0x15, 0x15, 0x14, 0x14, 0x15, 0x40,
  0x40, 0x50, 0x40, 0x86, 0x41, 0x88, 0x10, 0x81, 0x51, 0x0C, 0x50, 0x40, 0x50, 0x50, 0x40, 0x50,
  0x50, 0x40, 0x40, 0x51, 0x41, 0x41, 0x15, 0x84, 0x14, 0x86, 0x10, 0x81, 0x1F, 0x86, 0x10, 0x81,
  0x51, 0x08, 0x41, 0x51, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x83, 0x41, 0x82, 0x40, 0x00,
  0x14, 0x88, 0x10, 0x82, 0x15, 0x0B, 0x14, 0x15, 0x15, 0x14, 0x10, 0x10, 0x14, 0x14, 0x15, 0x14,
  0x14, 0x15, 0x85, 0x14, 0x81, 0x41, 0x86, 0x10, 0x00, 0x1F, 0x87, 0x10, 0x00, 0x1F, 0x83, 0x10,
  0x81, 0x50, 0x0A, 0x40, 0x10, 0x10, 0x40, 0x40, 0x50, 0x40, 0x40, 0x50, 0x40, 0x40, 0x85, 0x41,
  0x8A, 0x10, 0x00, 0x1F, 0x84, 0x10, 0x81, 0x51, 0x0C, 0x50, 0x40, 0x50, 0x50, 0x40, 0x15, 0x15,
  0x40, 0x40, 0x50, 0x40, 0x40, 0x51, 0x83, 0x41, 0x81, 0x40, 0x81, 0x14, 0x86, 0x10, 0x82, 0x1E,
  0x88, 0x10, 0x0C, 0x15, 0x41, 0x51, 0x51, 0x41, 0x51, 0x51, 0x41, 0x41, 0x51, 0x41, 0x14, 0x15,
  0x83, 0x14, 0x00, 0x10, 0x82, 0x41, 0x8B, 0x10, 0x01, 0x1F, 0x10, 0x82, 0x15, 0x82, 0x50, 0x0C,
  0x40, 0x51, 0x51, 0x41, 0x51, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x41, 0x83, 0x40, 0x82,
  0x14, 0x84, 0x10, 0x00, 0x1F, 0x86, 0x10, 0x00, 0x1F, 0x85, 0x50, 0x00, 0x40, 0x83, 0x10, 0x83,
  0x40, 0x01, 0x10, 0x1F, 0x86, 0x10, 0x00, 0x1F, 0x89, 0x10, 0x86, 0x41, 0x88, 0x10, 0x00, 0x1F,
  0x86, 0x10, 0x82, 0x15, 0x0B, 0x14, 0x50, 0x50, 0x40, 0x50, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41,
  0x51, 0x83, 0x40, 0x83, 0x14, 0x00, 0x1F, 0x88, 0x10, 0x07, 0x1E, 0x10, 0x10, 0x50, 0x50, 0x40,
  0x15, 0x15, 0x84, 0x10, 0x01, 0x15, 0x14, 0x83, 0x40, 0x83, 0x10, 0x82, 0xE1, 0x84, 0x10, 0x82,
  0x51, 0x0B, 0x41, 0x51, 0x51, 0x41, 0x51, 0x51, 0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x87, 0x41,
  0x85, 0x10, 0x02, 0x1E, 0xE1, 0x1E, 0x8A, 0x10, 0x0B, 0x1F, 0x15, 0x15, 0x14, 0x15, 0x15, 0x14,
  0x14, 0x15, 0x14, 0x14, 0x15, 0x87, 0x14, 0x89, 0x10, 0x82, 0x1E, 0x83, 0x10, 0x00, 0x1F, 0x86,
  0x10, 0x82, 0x51, 0x0B, 0x41, 0x51, 0x51, 0x41, 0x51, 0x51, 0x41, 0x41, 0x50, 0x40, 0x40, 0x15,
  0x84, 0x14, 0x85, 0x10, 0x00, 0xE1, 0x84, 0x10, 0x82, 0x15, 0x0B, 0x14, 0x15, 0x50, 0x40, 0x50,
  0x50, 0x40, 0x40, 0x50, 0x41, 0x41, 0x51, 0x87, 0x41, 0x84, 0x10, 0x00, 0x1F, 0x8A, 0x10, 0x00,
  0xF1, 0x89, 0x10, 0x00, 0x1F, 0x83, 0x10, 0x82, 0x51, 0x0B, 0x41, 0x51, 0x51, 0x41, 0x51, 0x51,
  0x41, 0x41, 0x51, 0x41, 0x41, 0x51, 0x87, 0x41, 0x8A, 0x10, 0x00, 0xF1, 0x86, 0x10, 0x00, 0x1F,
  0x87, 0x10, 0x00, 0x1F, 0xFC, 0x00, 0x82, 0x00, 0xFF};