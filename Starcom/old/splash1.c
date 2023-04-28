#include <coleco.h>

const byte SPLASH1_NAMERLE[] = {
  0x99, 0x5C, 0x03, 0xC8, 0xD4, 0xDF, 0xEA, 0x99, 0x5C, 0x05, 0xB9, 0xBE, 0xC9, 0xD5, 0xE0,
  0xEB, 0x9A, 0x5C, 0x04, 0xBF, 0xCA, 0xD6, 0xE1, 0xEC, 0x83, 0x5C, 0x02, 0x61, 0x67, 0x6D, 0x82,
  0x5C, 0x02, 0x7B, 0x81, 0x85, 0x82, 0x5C, 0x03, 0x90, 0x99, 0x9F, 0xA5, 0x86, 0x5C, 0x04, 0xC0,
  0xCB, 0xD7, 0xE2, 0xED, 0x82, 0x5C, 0x10, 0x5D, 0x62, 0x68, 0x6E, 0x73, 0x5C, 0x77, 0x7C, 0x65,
  0x86, 0x8B, 0x5C, 0x90, 0x94, 0x9A, 0xA0, 0xA6, 0x86, 0x5C, 0x04, 0xC1, 0xCC, 0xD8, 0xE3, 0xEE,
  0x82, 0x5C, 0x11, 0x5E, 0x63, 0x69, 0x6F, 0x74, 0x5C, 0x78, 0x7D, 0x82, 0x87, 0x8C, 0x5C, 0x91,
  0x95, 0x9B, 0xA1, 0xA7, 0xAB, 0x85, 0x5C, 0x04, 0xC2, 0xCD, 0xD9, 0xE4, 0xEF, 0x82, 0x5C, 0x11,
  0x5F, 0x64, 0x6A, 0x70, 0x75, 0x5C, 0x79, 0x7E, 0x7D, 0x88, 0x8D, 0x5C, 0x92, 0x96, 0x9C, 0xA2,
  0xA8, 0xAC, 0x85, 0x5C, 0x04, 0xC3, 0xCE, 0xDA, 0xE5, 0xF0, 0x82, 0x5C, 0x11, 0x60, 0x65, 0x6B,
  0x71, 0x76, 0x5C, 0x7A, 0x7F, 0x83, 0x89, 0x8E, 0x5C, 0x93, 0x97, 0x9D, 0xA3, 0xA9, 0xAA, 0x86,
  0x5C, 0x0A, 0xCF, 0xDB, 0xE6, 0xF1, 0xF6, 0xFB, 0x5C, 0x5C, 0x66, 0x6C, 0x72, 0x82, 0x5C, 0x09,
  0x80, 0x84, 0x8A, 0x8F, 0x5C, 0x5C, 0x98, 0x9E, 0xA4, 0xAA, 0x84, 0x5C, 0x08, 0xB5, 0xBA, 0xC4,
  0xD0, 0xDC, 0xE7, 0xF2, 0xF7, 0xFC, 0x94, 0x5C, 0x0A, 0xAF, 0xB2, 0xB6, 0xBB, 0xC5, 0xD1, 0xDD,
  0xE8, 0xF3, 0xF8, 0xFD, 0x93, 0x5C, 0x0B, 0xAD, 0xB0, 0xB3, 0xB7, 0xBC, 0xC6, 0xD2, 0xDE, 0xE9,
  0xF4, 0xF9, 0xFE, 0x93, 0x5C, 0x0B, 0xAE, 0xB1, 0xB4, 0xB8, 0xBD, 0xC7, 0xD3, 0x5C, 0x5C, 0xF5,
  0xFA, 0xFF, 0xFE, 0x5C, 0xFE, 0x5C, 0xFE, 0x5C, 0x82, 0x5C, 0xFF};

const byte SPLASH1_PATTERNRLE[] = {
  0xFE, 0x00, 0xFE, 0x00, 0x89, 0x00, 0x07, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00, 0x18, 0x00,
  0x82, 0x66, 0x84, 0x00, 0x81, 0x66, 0x20, 0xFF, 0x66, 0xFF, 0x66, 0x66, 0x00, 0x18, 0x3E, 0x60,
  0x3C, 0x06, 0x7C, 0x18, 0x00, 0xFF, 0x81, 0xB9, 0xA5, 0xB9, 0xA5, 0x81, 0xFF, 0x3C, 0x66, 0x3C,
  0x38, 0x67, 0x66, 0x3F, 0x00, 0x06, 0x0C, 0x18, 0x84, 0x00, 0x01, 0x0C, 0x18, 0x82, 0x30, 0x04,
  0x18, 0x0C, 0x00, 0x30, 0x18, 0x82, 0x0C, 0x08, 0x18, 0x30, 0x00, 0x00, 0x66, 0x3C, 0xFF, 0x3C,
  0x66, 0x82, 0x00, 0x81, 0x18, 0x02, 0x7E, 0x18, 0x18, 0x85, 0x00, 0x81, 0x18, 0x00, 0x30, 0x83,
  0x00, 0x00, 0x7E, 0x88, 0x00, 0x81, 0x18, 0x81, 0x00, 0x09, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0,
  0x00, 0xFE, 0xC6, 0xC6, 0x82, 0xE6, 0x03, 0xFE, 0x00, 0x38, 0x38, 0x82, 0x18, 0x81, 0x3C, 0x2C,
  0x00, 0xFE, 0x06, 0x06, 0xFE, 0xC0, 0xC0, 0xFE, 0x00, 0xFC, 0x0C, 0x0C, 0x7E, 0x0E, 0x0E, 0xFE,
  0x00, 0xC0, 0xC0, 0xC6, 0xC6, 0xFE, 0x06, 0x06, 0x00, 0xFE, 0xC0, 0xC0, 0xFE, 0x06, 0x06, 0xFE,
  0x00, 0xFC, 0xCC, 0xC0, 0xFE, 0xC6, 0xC6, 0xFE, 0x00, 0xFE, 0xC6, 0x0C, 0x18, 0x82, 0x38, 0x0C,
  0x00, 0x7E, 0x66, 0x66, 0xFE, 0xE6, 0xE6, 0xFE, 0x00, 0xFE, 0xC6, 0xC6, 0xFE, 0x82, 0x0E, 0x82,
  0x00, 0x03, 0x18, 0x00, 0x00, 0x18, 0x83, 0x00, 0x0C, 0x18, 0x00, 0x00, 0x18, 0x30, 0x00, 0x0C,
  0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x82, 0x00, 0x02, 0x7E, 0x00, 0x7E, 0x82, 0x00, 0x0E, 0x30,
  0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x00, 0x3C, 0x66, 0x06, 0x0C, 0x18, 0x00, 0x18, 0x88, 0x00,
  0x03, 0x7E, 0x66, 0x66, 0x7E, 0x82, 0xE6, 0x11, 0x00, 0xFC, 0xCC, 0xCC, 0xFE, 0xC6, 0xC6, 0xFE,
  0x00, 0xFE, 0xCE, 0xCE, 0xC0, 0xC0, 0xC6, 0xFE, 0x00, 0xFC, 0x84, 0xE6, 0x0D, 0xFC, 0x00, 0xFE,
  0xC0, 0xC0, 0xF8, 0xE0, 0xE0, 0xFE, 0x00, 0xFE, 0xE0, 0xE0, 0xF8, 0x82, 0x60, 0x08, 0x00, 0xFE,
  0xC6, 0xC0, 0xC0, 0xCE, 0xC6, 0xFE, 0x00, 0x82, 0xC6, 0x00, 0xFE, 0x82, 0xE6, 0x00, 0x00, 0x82,
  0x18, 0x83, 0x38, 0x0C, 0x00, 0x3E, 0x0C, 0x0C, 0x0E, 0xCE, 0xCE, 0xFE, 0x00, 0xC6, 0xCC, 0xD8,
  0xFE, 0x82, 0xE6, 0x00, 0x00, 0x82, 0x60, 0x82, 0xE0, 0x05, 0xFE, 0x00, 0xC6, 0xEE, 0xFE, 0xD6,
  0x82, 0xC6, 0x04, 0x00, 0xE6, 0xF6, 0xDE, 0xCE, 0x82, 0xE6, 0x03, 0x00, 0xFE, 0xC6, 0xC6, 0x82,
  0xCE, 0x05, 0xFE, 0x00, 0xFE, 0xC6, 0xC6, 0xFE, 0x82, 0xE0, 0x01, 0x00, 0xFE, 0x83, 0xC6, 0x06,
  0xCE, 0xFE, 0x0F, 0xFC, 0xE6, 0xE6, 0xFC, 0x82, 0xCE, 0x0B, 0x00, 0xFE, 0xC6, 0xC0, 0xFE, 0x06,
  0xE6, 0xFE, 0x00, 0x7E, 0x18, 0x18, 0x83, 0x38, 0x00, 0x00, 0x82, 0xC6, 0x82, 0xCE, 0x01, 0xFE,
  0x00, 0x84, 0xC6, 0x02, 0x6C, 0x38, 0x00, 0x83, 0xC6, 0x0E, 0xD6, 0xFE, 0xEE, 0x00, 0xC6, 0xC6,
  0x6C, 0x38, 0x6C, 0xC6, 0xC6, 0x00, 0xC6, 0xC6, 0x6C, 0x83, 0x38, 0x07, 0x00, 0xFE, 0xCC, 0x18,
  0x30, 0x60, 0xC6, 0xFE, 0x88, 0x00, 0x89, 0xFF, 0x04, 0xFE, 0xFC, 0xF8, 0xF0, 0xF0, 0x82, 0xC0,
  0x83, 0x80, 0x03, 0xFE, 0xF0, 0xF0, 0xFE, 0x84, 0x80, 0x81, 0xC0, 0x00, 0xE0, 0x82, 0xF0, 0x82,
  0xFE, 0x85, 0xFF, 0x02, 0xF8, 0xE0, 0x80, 0x88, 0xFF, 0x03, 0xF3, 0xF8, 0xF8, 0xF0, 0x83, 0xFF,
  0x03, 0xF0, 0xF8, 0xF0, 0xF3, 0x89, 0xFF, 0x02, 0xC0, 0xE0, 0xFE, 0x8B, 0xFF, 0x82, 0xEF, 0x82,
  0xC7, 0x00, 0xC3, 0x82, 0x83, 0x81, 0xFC, 0x89, 0xFF, 0x81, 0xFC, 0x82, 0x83, 0x02, 0xC3, 0xC7,
  0xC7, 0x82, 0xEF, 0x8D, 0xFF, 0x03, 0x80, 0xF0, 0xFC, 0xFE, 0x87, 0xFF, 0x0B, 0xC0, 0x80, 0x80,
  0xC0, 0xFE, 0xFF, 0xFF, 0xFE, 0xC0, 0x80, 0xC0, 0xC0, 0x87, 0xFF, 0x81, 0xFE, 0x01, 0xF0, 0xE0,
  0x87, 0xFF, 0x05, 0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0xF0, 0x82, 0xF8, 0x83, 0xFC, 0x81, 0xC0, 0x84,
  0xFC, 0x82, 0xF8, 0x03, 0xF0, 0xE0, 0xC0, 0xC0, 0x86, 0xFF, 0x81, 0xFE, 0x01, 0xFC, 0xF8, 0x84,
  0xF0, 0x81, 0xE0, 0x83, 0xF8, 0x81, 0xE0, 0x83, 0xF0, 0x03, 0xF8, 0xFC, 0xFC, 0xFE, 0x89, 0xFF,
  0x03, 0xFC, 0xF0, 0xC0, 0xC0, 0x91, 0xFF, 0x02, 0xE1, 0xC1, 0xC0, 0x84, 0xFF, 0x04, 0xFE, 0xF8,
  0xC0, 0xE0, 0xFC, 0x8A, 0xFF, 0x0D, 0xFB, 0x80, 0xFF, 0x80, 0xC0, 0xE0, 0xC0, 0xBF, 0xBF, 0x9F,
  0xDF, 0x80, 0xC0, 0x80, 0x92, 0xFF, 0x02, 0xC0, 0xF8, 0xFE, 0x86, 0xFF, 0x81, 0xE0, 0x81, 0xC0,
  0x03, 0xE0, 0x9F, 0x9F, 0xBF, 0x85, 0xFF, 0x81, 0xF0, 0x0A, 0xE0, 0xC0, 0xC0, 0xE0, 0xF0, 0xF0,
  0xFC, 0xF8, 0xF0, 0xF8, 0xF0, 0x85, 0xFF, 0x03, 0x80, 0xC0, 0xE0, 0xF0, 0x82, 0xF8, 0x00, 0xF0,
  0x83, 0xF8, 0x87, 0xFC, 0x0B, 0xF8, 0x87, 0x87, 0xE7, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x80,
  0x80, 0x8D, 0xFF, 0x00, 0xFE, 0x84, 0xFC, 0x86, 0xF8, 0x84, 0xFC, 0x86, 0xFF, 0x02, 0xF8, 0xF0,
  0xC0, 0x82, 0x80, 0x02, 0xF9, 0xFC, 0xFE, 0x8A, 0xFF, 0x81, 0xFE, 0x03, 0xFC, 0xF8, 0xF0, 0xF0,
  0x82, 0x80, 0x03, 0xE0, 0xF0, 0xF0, 0xFE, 0x8B, 0xFF, 0x01, 0xF8, 0x80, 0x88, 0xFF, 0x11, 0xC0,
  0xF0, 0x87, 0xC3, 0xC0, 0xC0, 0xF0, 0xF0, 0xC0, 0xFF, 0xC1, 0xC1, 0xFF, 0xFB, 0xF3, 0xE0, 0xC0,
  0xC0, 0x87, 0xFF, 0x00, 0xF0, 0x89, 0xFF, 0x01, 0xE0, 0xFE, 0x87, 0xFF, 0x13, 0xFE, 0xFC, 0xF8,
  0xE1, 0xC3, 0x83, 0xFC, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xFF, 0xFF, 0x9F, 0xF8, 0xFC, 0xFC,
  0xFE, 0x85, 0xFF, 0x01, 0xFE, 0xF0, 0x8B, 0xFF, 0x02, 0x80, 0xE0, 0xF0, 0x82, 0xFC, 0x03, 0xBF,
  0x9F, 0xC0, 0x80, 0x8B, 0xFF, 0x81, 0x80, 0x05, 0xE0, 0xF0, 0xE0, 0x80, 0xFE, 0xFC, 0x82, 0xF0,
  0x00, 0x80, 0x86, 0xFF, 0x00, 0x80, 0x8D, 0xC0, 0x00, 0x80, 0x82, 0xFF, 0x07, 0xFE, 0xFC, 0xFC,
  0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0x86, 0xFF, 0x01, 0xFE, 0xFF, 0x82, 0xFC, 0x06, 0xF0, 0xE2, 0x86,
  0xFD, 0xFD, 0xFF, 0xFD, 0x8A, 0xFF, 0x03, 0xFC, 0x81, 0xFE, 0xFE, 0x82, 0xFC, 0x07, 0xFD, 0xF2,
  0xE8, 0xA3, 0xF8, 0x87, 0xF8, 0xF0, 0x82, 0xF1, 0x8B, 0xFF, 0x09, 0xFE, 0xC6, 0x84, 0xFB, 0xF7,
  0x8E, 0xD2, 0xE3, 0x9C, 0xC0, 0x82, 0xFF, 0x06, 0xFD, 0xE1, 0xD2, 0xDE, 0xF1, 0xF1, 0xEF, 0x88,
  0xFF, 0x82, 0xFE, 0x85, 0xFF, 0x09, 0xE4, 0x84, 0xF7, 0xE7, 0xEF, 0xEF, 0xE9, 0xEE, 0x9F, 0x80,
  0x82, 0xFF, 0x08, 0xFB, 0x9B, 0xEC, 0x8C, 0xFC, 0xC8, 0xD8, 0xE8, 0xE8, 0x84, 0xFF, 0x0E, 0xFE,
  0xF8, 0xE0, 0x80, 0xFF, 0xAC, 0xC3, 0x93, 0xB8, 0xF9, 0xF9, 0xFF, 0xE7, 0xC0, 0xC0, 0x82, 0x80,
  0x81, 0xC0, 0x07, 0xE0, 0xC0, 0xF0, 0xFF, 0x87, 0x83, 0xC9, 0xE3, 0x86, 0xE0, 0x02, 0xF0, 0xF8,
  0xF8, 0x82, 0xFC, 0x82, 0xFE, 0x85, 0xFF, 0x12, 0xF3, 0xA6, 0xF3, 0xF7, 0xF7, 0xED, 0xEF, 0xCD,
  0xE4, 0xA8, 0xE0, 0xE8, 0xE2, 0xC3, 0xC2, 0xC2, 0xC0, 0xE4, 0xF4, 0x84, 0xF8, 0x00, 0xF9, 0x8A,
  0xFF, 0x1A, 0xC0, 0x80, 0xFF, 0xF9, 0xFE, 0xFA, 0xE3, 0xFC, 0x9F, 0xE2, 0xC2, 0xF8, 0xF0, 0xC0,
  0xC3, 0xD1, 0xB9, 0x8D, 0x86, 0xCF, 0xC5, 0x93, 0x8F, 0xFE, 0xF0, 0xAF, 0xAF, 0x82, 0x80, 0x10,
  0x8F, 0xAF, 0xDF, 0xDF, 0xCF, 0xCF, 0x8F, 0xFF, 0xDF, 0xDF, 0x8A, 0x9B, 0xDF, 0xDD, 0xEF, 0xE0,
  0xE0, 0x82, 0x80, 0x82, 0xC0, 0x06, 0xE0, 0xF0, 0xF8, 0xF0, 0xD0, 0x90, 0xEF, 0x82, 0xF0, 0x82,
  0xE0, 0x0C, 0x9F, 0xDF, 0xEF, 0xE0, 0x83, 0xB8, 0xC3, 0xCB, 0xFB, 0x9D, 0xE0, 0x81, 0x87, 0x82,
  0xFC, 0x02, 0xF8, 0xF0, 0xF8, 0x88, 0xFF, 0x47, 0xF8, 0x80, 0xFF, 0xBF, 0xBF, 0x80, 0x80, 0xFC,
  0xE0, 0xFF, 0xF6, 0xFF, 0xC0, 0x8F, 0xF7, 0x9C, 0xE0, 0x98, 0xB8, 0xA0, 0x80, 0xE3, 0x8F, 0xFB,
  0xE0, 0xFF, 0x80, 0xC3, 0xE3, 0x98, 0x87, 0xE0, 0xBC, 0xF7, 0xF6, 0x8D, 0xC0, 0xC1, 0xE1, 0xC0,
  0xBF, 0xAF, 0xB9, 0x8E, 0x82, 0xF3, 0xFE, 0xE8, 0xF7, 0xFF, 0xFF, 0x80, 0xFC, 0xFE, 0xDC, 0x87,
  0xFC, 0xFC, 0xED, 0xFC, 0xFD, 0xFD, 0xD3, 0xD2, 0xD6, 0xBF, 0xEF, 0xFF, 0xFE, 0xB9, 0x87, 0x80,
  0x87, 0xFF, 0x00, 0x80, 0x87, 0xFF, 0x81, 0xF8, 0x03, 0xC0, 0x80, 0xFF, 0x80, 0x82, 0xFF, 0x03,
  0xA0, 0xF8, 0xFC, 0xC3, 0x86, 0xE3, 0x08, 0xFC, 0xE8, 0xF0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFF, 0xFF,
  0x82, 0x80, 0x04, 0xE0, 0x9F, 0xBF, 0xC0, 0x80, 0x83, 0xC0, 0x81, 0x80, 0x04, 0xBF, 0x80, 0xBF,
  0x80, 0x80, 0x82, 0xFF, 0x1C, 0xF3, 0xC7, 0xFC, 0xFC, 0xF8, 0xF8, 0xB8, 0xF8, 0xF8, 0xFE, 0xFD,
  0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x80, 0x80, 0xBF, 0xDF, 0xCF, 0xEF, 0xE7, 0xF7, 0xFA, 0xF8, 0xF8,
  0xE0, 0x80, 0x89, 0xFF, 0x06, 0x80, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0x8C, 0xFC, 0x83, 0xF8,
  0x0C, 0xD8, 0xB0, 0xB0, 0xF0, 0xF0, 0xE0, 0xF0, 0xF0, 0xF8, 0xD8, 0x9C, 0xCC, 0xCC, 0x82, 0xE4,
  0x87, 0xE0, 0x0A, 0xF0, 0xF4, 0xF8, 0xF8, 0xFC, 0xF8, 0xF0, 0xE0, 0xBF, 0xC0, 0xDF, 0x82, 0xFF,
  0x08, 0xFE, 0xFC, 0xF8, 0xD8, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x86, 0xFF, 0x83, 0xFE, 0x01, 0xFC,
  0xFE, 0x86, 0xFF, 0x00, 0xFE, 0x82, 0xFF, 0x07, 0xBE, 0xF4, 0xF9, 0xF0, 0xE7, 0x9F, 0xE0, 0xE8,
  0x88, 0xFF, 0x0B, 0xF0, 0xE0, 0xF8, 0xA4, 0xF7, 0xEF, 0xFE, 0xF3, 0xEF, 0xFF, 0xDE, 0xD6, 0x89,
  0xFF, 0x0A, 0xEF, 0x8F, 0xF0, 0x8F, 0xF0, 0xD0, 0xE0, 0xE0, 0xC0, 0xD0, 0xF0, 0x86, 0xFF, 0x82,
  0xF0, 0x08, 0xE0, 0xF0, 0xDF, 0xF0, 0xC0, 0xF0, 0xF0, 0xB0, 0x8F, 0x84, 0xFF, 0xFF};

const byte SPLASH1_COLORRLE[] = {
  0xFE, 0x00, 0xFC, 0x00, 0x83, 0x00, 0x87, 0xF0, 0xFE, 0xF1, 0xFE, 0xF1, 0xFE, 0xF1, 0xD2,
  0xF1, 0x87, 0xF0, 0x89, 0x10, 0x8B, 0x14, 0x83, 0x4F, 0x8D, 0x14, 0x85, 0x10, 0x82, 0x14, 0x88,
  0x40, 0x83, 0x4F, 0x83, 0xF0, 0x83, 0x4F, 0x89, 0x40, 0x82, 0x14, 0x8A, 0x10, 0x00, 0x40, 0x89,
  0x4F, 0x81, 0xF4, 0x89, 0xF0, 0x81, 0xF4, 0x88, 0x4F, 0x82, 0x40, 0x8A, 0x10, 0x83, 0x41, 0x87,
  0x40, 0x84, 0xF4, 0x81, 0xF0, 0x84, 0xF4, 0x87, 0x40, 0x83, 0x41, 0x87, 0x10, 0x8C, 0x41, 0x81,
  0xF4, 0x8B, 0x41, 0x86, 0x10, 0x83, 0x14, 0x86, 0x15, 0x83, 0x1A, 0x86, 0x15, 0x82, 0x14, 0x89,
  0x10, 0x83, 0x14, 0x84, 0x40, 0x8C, 0xA0, 0x82, 0xA4, 0x84, 0x40, 0x81, 0x4A, 0x81, 0x15, 0x00,
  0x14, 0x8A, 0x10, 0x81, 0x14, 0x00, 0x40, 0x83, 0xA4, 0x83, 0xA5, 0x82, 0x4A, 0x85, 0xA0, 0x81,
  0x40, 0x8A, 0x10, 0x82, 0x41, 0x86, 0x40, 0x84, 0x4A, 0x82, 0xA4, 0x85, 0xA0, 0x8A, 0xA4, 0x81,
  0x41, 0x85, 0x10, 0x86, 0x41, 0x8D, 0xA4, 0x82, 0x4A, 0x87, 0x41, 0x8D, 0x10, 0x91, 0x18, 0x86,
  0x10, 0x84, 0x18, 0x00, 0x19, 0x82, 0x8A, 0x8A, 0x80, 0x85, 0x8A, 0x86, 0x18, 0x8B, 0x10, 0x81,
  0x18, 0x88, 0x80, 0x81, 0xA8, 0x86, 0x8A, 0x03, 0xA0, 0x8A, 0x8A, 0xA0, 0x84, 0xA8, 0x87, 0x80,
  0x00, 0x18, 0x89, 0x10, 0x81, 0x81, 0x87, 0x80, 0x85, 0x8A, 0x86, 0xA8, 0x81, 0xA0, 0x00, 0xA8,
  0x83, 0x8A, 0x85, 0x80, 0x81, 0x81, 0x8B, 0x10, 0x85, 0x81, 0x81, 0x8A, 0x81, 0xA8, 0x8B, 0x80,
  0x85, 0xA8, 0x85, 0x81, 0x86, 0x10, 0x8F, 0x81, 0x82, 0x10, 0x87, 0x1E, 0x86, 0x10, 0x01, 0x1E,
  0x10, 0x85, 0x1E, 0x81, 0xE1, 0x01, 0xE0, 0xE1, 0x84, 0xE0, 0x85, 0x10, 0x81, 0x1E, 0x87, 0xE1,
  0x02, 0x1E, 0xE1, 0x1E, 0x84, 0xE1, 0x8B, 0x10, 0x82, 0x1E, 0x81, 0xE1, 0x00, 0x1E, 0x83, 0xE1,
  0x82, 0x10, 0x81, 0x1E, 0x82, 0xE1, 0x01, 0x1E, 0xE1, 0x88, 0x10, 0x82, 0x1B, 0x85, 0x10, 0x81,
  0x1E, 0x85, 0xE1, 0x01, 0x1E, 0xE1, 0x82, 0x10, 0x81, 0x1E, 0x86, 0xE1, 0x84, 0x10, 0x07, 0x1A,
  0x1B, 0x1B, 0xAB, 0xB0, 0xAB, 0xA1, 0xB1, 0x82, 0x1A, 0x04, 0x10, 0x18, 0x16, 0x19, 0x18, 0x83,
  0x19, 0x07, 0x16, 0x18, 0x19, 0x10, 0x18, 0x18, 0x1A, 0x16, 0x88, 0x19, 0x06, 0x16, 0x19, 0x18,
  0x18, 0x19, 0x19, 0x16, 0x85, 0x10, 0x81, 0x1E, 0x85, 0xE1, 0x90, 0x1E, 0x8A, 0x10, 0x81, 0x1B,
  0x0C, 0xB0, 0xBA, 0xB1, 0xB1, 0xBA, 0xBA, 0xAB, 0xA1, 0xA1, 0x16, 0x18, 0x18, 0x69, 0x82, 0x96,
  0x00, 0x69, 0x83, 0x96, 0x81, 0x91, 0x81, 0x69, 0x02, 0x16, 0x18, 0x16, 0x86, 0x69, 0x06, 0x60,
  0x81, 0x96, 0x69, 0x69, 0x96, 0x61, 0x82, 0x96, 0x00, 0x69, 0x85, 0x19, 0x81, 0x16, 0x82, 0x19,
  0x00, 0x91, 0x85, 0xE6, 0x82, 0x91, 0x81, 0xE1, 0x00, 0x1E, 0x83, 0xE1, 0x82, 0x1E, 0x85, 0xE1,
  0x88, 0x10, 0x0E, 0x1B, 0xAB, 0xB0, 0xBA, 0xBA, 0xAB, 0xAB, 0xBA, 0xBA, 0xA0, 0xA1, 0x10, 0x16,
  0x69, 0x69, 0x85, 0x96, 0x81, 0x69, 0x81, 0x61, 0x06, 0x10, 0x16, 0x61, 0x91, 0x19, 0x96, 0x69,
  0x82, 0x96, 0x84, 0x69, 0x82, 0x96, 0x08, 0x69, 0x96, 0x69, 0x96, 0x69, 0x96, 0x90, 0x90, 0x69,
  0x82, 0x96, 0x82, 0x69, 0x81, 0x96, 0x81, 0x91, 0x84, 0x96, 0x04, 0x90, 0x91, 0x91, 0xE1, 0x1E,
  0x87, 0xE0, 0x00, 0x1E, 0x87, 0x10, 0x81, 0xB1, 0x81, 0xBA, 0x01, 0xA0, 0xBA, 0x82, 0xA0, 0x82,
  0x1A, 0x87, 0x91, 0x00, 0x6A, 0x85, 0x61, 0x81, 0x60, 0x83, 0x96, 0x81, 0x69, 0x87, 0x96, 0x04,
  0x69, 0x96, 0x69, 0x96, 0x96, 0x82, 0x60, 0x81, 0x69, 0x86, 0x96, 0x00, 0x61, 0x82, 0x91, 0x04,
  0xB1, 0xE1, 0xE1, 0x1E, 0x1E, 0x8A, 0xE1, 0x89, 0x10, 0x92, 0xA1, 0x00, 0x91, 0x9F, 0x61, 0x83,
  0x6E, 0x02, 0xE1, 0x1E, 0xE1, 0x82, 0xE0, 0x88, 0xE1, 0x86, 0x10, 0x85, 0x1E, 0x86, 0x10, 0x00,
  0xE1, 0x82, 0xE0, 0x85, 0xE1, 0x81, 0x1E, 0x88, 0x10, 0x83, 0x1E, 0x84, 0xE1, 0x02, 0xE0, 0xE1,
  0xE1, 0x89, 0x10, 0x81, 0x1E, 0x01, 0xE1, 0x1E, 0x86, 0xE1, 0x86, 0x10, 0x84, 0xE1, 0x00, 0x1E,
  0x84, 0xE1, 0x00, 0x1E, 0x84, 0x10, 0xFF};
