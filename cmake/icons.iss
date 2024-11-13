[Icons]
Name: "{group}\Louis Work"; Filename: "{app}\bin\louis.exe";

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType:string; ValueName:"ESPEAK_DATA_PATH"; ValueData:"{app}\espeak-ng-data"; Flags: preservestringtype
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType:string; ValueName:"LOUIS_DATA_PATH"; ValueData:"{app}"; Flags: preservestringtype
