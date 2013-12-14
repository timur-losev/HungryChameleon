#! /usr/bin/env python
  
import xlrd, plistlib, sys
from optparse import OptionParser

def main(args):
    parser = OptionParser()
    
    parser.add_option("-d", "--destination", dest="destDir", help="sets destination direcotry")
    parser.add_option("-i", "--infile", dest="srcFile", help="sets input xls/xlsx file")
    (arguments, args) = parser.parse_args()

    srcFile = arguments.srcFile
    destDir = arguments.destDir

    book = xlrd.open_workbook(srcFile, encoding_override="cp1252")
    sheet = book.sheets()[0]

    langCols = range(sheet.ncols)[1:]
    langs = [sheet.cell_value(0, col).lower() for col in langCols]
    rows = range(sheet.nrows)[1:]

    print("\n******************************************")
    print("Started making texts.")
    print("******************************************\n")

    texts = dict()
    for i in range(len(langs)):
        text = dict()
        for r in rows:
            text[sheet.cell_value(r, 0)] = sheet.cell_value(r, langCols[i])
        text
        plistlib.writePlist(text, destDir+langs[i]+".plist")
        print(destDir+langs[i]+".plist")

    print("\n******************************************")
    print("Done making texts")
    print("******************************************\n")

main(sys.argv)
