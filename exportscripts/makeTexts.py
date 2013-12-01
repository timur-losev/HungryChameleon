#! /usr/bin/env python
  
import xlrd
import plistlib
import sys

def main(args):
    srcFile = args[1]
    destDir = args[2]

    book = xlrd.open_workbook(srcFile, encoding_override="cp1252")
    sheet = book.sheets()[0]

    langCols = range(sheet.ncols)[1:]
    langs = [sheet.cell_value(0, col).lower() for col in langCols]
    rows = range(sheet.nrows)[1:]

    texts = dict()
    for i in range(len(langs)):
        text = dict()
        for r in rows:
            text[sheet.cell_value(r, 0)] = sheet.cell_value(r, langCols[i])
        text
        plistlib.writePlist(text, destDir+langs[i]+".plist")

main(sys.argv)
