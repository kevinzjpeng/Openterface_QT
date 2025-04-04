; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Openterface Mini-KVM"
; #define MyAppExeName "openterfaceQT.exe"

#pragma message "AppVersion: " + MyAppVersion
#pragma message "MyAppPublisher: " + MyAppPublisher
#pragma message "MyAppURL: " + MyAppURL

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{4200459F-8F27-46C4-BFB2-65C1447AE912}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
VersionInfoProductTextVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
AppCopyright=Copyright © All rights reserved. 2024 TechxArtisan Limited
LicenseFile={#SourcePackage}\LICENSE
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
VersionInfoVersion={#MyAppVersion}
VersionInfoDescription={#MyAppName} {#MyAppVersion} Installer
VersionInfoCompany={#MyAppPublisher}
VersionInfoCopyright=Copyright © {#MyAppPublisher} {#MyAppVersion}
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
; OutputBaseFilename=setup
OutputDir={#OutputDir}
OutputBaseFilename={#OutputBaseFileName}
Compression=lzma2/max
SolidCompression=yes
WizardStyle=modern
SetupLogging=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "{#SourcePackage}\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#SourcePackage}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#SourcePackage}\driver\windows\CH341SER.INF"; DestDir: {app}\driver;
Source: "{#SourcePackage}\driver\windows\CH341S64.SYS"; DestDir: {app}\driver;


; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; \
    Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; \
    Flags: nowait postinstall skipifsilent; \
    Parameters: "/silent"
Filename: {sys}\pnputil.exe; \
    Parameters: "/add-driver CH341SER.INF /install"; \
    WorkingDir: {app}\driver; Flags: 64bit runhidden;