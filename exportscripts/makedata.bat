@echo off

set outdir=../_build_win32_debug

python makeTexts.py  --infile ../resources/texts.xlsx --destination ../export/
python packDB.py --outfile %outdir%/asset.db --folder ../export --ignore .pyc/.db
rem python makedata.py

pause