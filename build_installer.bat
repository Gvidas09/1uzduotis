@echo off
echo === Studentu programa v3.0 diegimo paketo kurimas ===
echo.

REM Surinkti Release versija
echo [1/3] Surenkama Release versija...
cmake --build build --config Release
if errorlevel 1 (
    echo KLAIDA: surinkimas nepavyko.
    exit /b 1
)

REM Sukurti installer kataloga
if not exist installer mkdir installer

REM Surinkti diegimo paketa naudojant Inno Setup
echo [2/3] Kuriamas diegimo paketas...
set ISCC_PATH=C:\Program Files (x86)\Inno Setup 6\ISCC.exe
if not exist "%ISCC_PATH%" (
    echo KLAIDA: Inno Setup nerastas: %ISCC_PATH%
    echo Idiekite Inno Setup is https://jrsoftware.org/isinfo.php
    exit /b 1
)

"%ISCC_PATH%" setup.iss
if errorlevel 1 (
    echo KLAIDA: diegimo paketo kurimas nepavyko.
    exit /b 1
)

echo [3/3] Baigta.
echo Diegimo failas: installer\StudentuPrograma_v3.0_setup.exe
