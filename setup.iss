[Setup]
AppName=Studentu programa
AppVersion=3.0
AppPublisher=Gvidas Kucinskas
AppPublisherURL=https://github.com/Gvidas09/1uzduotis
DefaultDirName={autopf}\StudentuPrograma
DefaultGroupName=Studentu programa
OutputDir=installer
OutputBaseFilename=StudentuPrograma_v3.0_setup
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "lithuanian"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Sukurti nuorodą darbalaukyje"; GroupDescription: "Papildomos nuorodos:"; Flags: unchecked

[Files]
Source: "build\Release\studentu_programa.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\Release\vektoriaus_testai.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\Release\studentu_testai.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "README.md"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Studentu programa"; Filename: "{app}\studentu_programa.exe"
Name: "{group}\Vector testai"; Filename: "{app}\vektoriaus_testai.exe"
Name: "{group}\Studentas testai"; Filename: "{app}\studentu_testai.exe"
Name: "{group}\{cm:UninstallProgram,Studentu programa}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\Studentu programa"; Filename: "{app}\studentu_programa.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\studentu_programa.exe"; Description: "{cm:LaunchProgram,Studentu programa}"; Flags: nowait postinstall skipifsilent
