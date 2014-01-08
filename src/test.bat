for %%f in (test\parse\*.in) do (
  parseex -i test\parse\%%~nf.in -o test\parse\%%~nf.tmp
  fc test\parse\%%~nf.out test\parse\%%~nf.tmp
)