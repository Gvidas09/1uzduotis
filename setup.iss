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
PrivilegesRequired=admin

[Languages]
Name: "lithuanian"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Sukurti nuoroda darbalaukyje"; GroupDescription: "Papildomos nuorodos:"

[Files]
Source: "main.exe"; DestDir: "{app}"; DestName: "studentu_programa.exe"; Flags: ignoreversion
Source: "README.md"; DestDir: "{app}"; Flags: ignoreversion
Source: "studentai10000.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "studentai100000.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Studentu programa"; Filename: "{app}\studentu_programa.exe"
Name: "{group}\{cm:UninstallProgram,Studentu programa}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\Studentu programa"; Filename: "{app}\studentu_programa.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\studentu_programa.exe"; Description: "{cm:LaunchProgram,Studentu programa}"; Flags: nowait postinstall skipifsilent