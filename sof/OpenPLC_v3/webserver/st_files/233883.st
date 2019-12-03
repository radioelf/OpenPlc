PROGRAM test_OpenPLC
  VAR
    Int1 AT %IX0.0 : BOOL;
    Int2 AT %IX0.1 : BOOL;
    Int3 AT %IX0.2 : BOOL;
    Int4 AT %IX0.3 : BOOL;
    Int5 AT %IX0.4 : BOOL;
    Int6 AT %IX0.5 : BOOL;
    Int7 AT %IX0.6 : BOOL;
    Int8 AT %IX0.7 : BOOL;
    Out1 AT %QX0.0 : BOOL;
    Out2 AT %QX0.1 : BOOL;
    Out3 AT %QX0.2 : BOOL;
    Out4 AT %QX0.3 : BOOL;
    Out5 AT %QX0.4 : BOOL;
    Out6 AT %QX0.5 : BOOL;
    Out7 AT %QX0.6 : BOOL;
    Out8 AT %QX0.7 : BOOL;
    IntAn1 AT %IW100 : INT;
    IntAn2 AT %IW101 : INT;
    IntAn3 AT %IW102 : INT;
    IntAn4 AT %IW103 : INT;
    IntAn5 AT %IW104 : INT;
    IntAn6 AT %IW105 : INT;
    IntAn7 AT %IW106 : INT;
    IntAn8 AT %IW107 : INT;
    OutAn1 AT %QW100 : INT;
    OutAn2 AT %QW101 : INT;
    OutAn3 AT %QW102 : INT;
    OutAn4 AT %QW103 : INT;
    OutAn5 AT %QW104 : INT;
    OutAn6 AT %QW105 : INT;
    OutAn7 AT %QW106 : INT;
    OutAn8 AT %QW107 : INT;
    Marca1 AT %M0.0 : BOOL;
    Marca2 AT %M0.1 : BOOL;
  END_VAR

  Marca1 := NOT(Marca2) AND (Marca1 OR NOT(Out1)) AND Int1;
  Marca2 := NOT(Marca1) AND (Marca2 OR Out1) AND Int1;
  Out1 := NOT(Marca2) AND (Marca1 OR Out1);
  Out2 := Int2;
  Out3 := Int3;
  Out4 := Int4;
  Out5 := Int5;
  Out6 := Int6;
  Out7 := Int7;
  Out8 := Int8;
  OutAn1 := IntAn1;
  OutAn2 := IntAn2;
  OutAn3 := IntAn3;
  OutAn4 := IntAn4;
  OutAn5 := IntAn5;
  OutAn6 := IntAn6;
  OutAn7 := IntAn7;
  OutAn8 := IntAn8;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : test_OpenPLC;
  END_RESOURCE
END_CONFIGURATION
