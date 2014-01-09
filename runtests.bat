for %%f in (src\test\parse\*.in) do (
  parseex -i src\test\parse\%%~nf.in -o src\test\parse\%%~nf.tmp
  fc src\test\parse\%%~nf.out src\test\parse\%%~nf.tmp
)