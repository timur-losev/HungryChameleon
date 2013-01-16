#! /usr/bin/env python

if __name__ == '__main__':
  import makedata
  raise SystemExit(makedata.main())
  
import os
import shutil

def main():
    srcDir = os.getcwd() + "/../export/"
    destDir = os.getcwd() + "/../_build_win32/data"
    if not os.path.exists(destDir):
        os.makedirs(destDir)
    print srcDir
    dirList = os.listdir(srcDir)
    for files in dirList:
        shutil.copy(srcDir + files, destDir)
