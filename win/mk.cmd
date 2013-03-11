@echo off
set vs=x:\com\vs10
:: ^-- change this to your VS2010 path
set vc=%vs%\vc
set PATH=%vc%\bin;%vs%\Common7\IDE
set INCLUDE=%vc%\include;..\include;%vs%\70a\include
set LIB=%vc%\lib;%vs%\70a\Lib
cl.exe -nologo libwinimage.cpp -c %*
cl.exe -nologo -w yaui.cpp -I .\cpp -I Y:\ksana\yaui\share gdi32.lib v8.lib user32.lib libwinimage.obj %*

