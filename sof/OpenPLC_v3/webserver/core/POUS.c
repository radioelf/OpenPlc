void TEST_OPENPLC_init__(TEST_OPENPLC *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_0,data__->INT1,retain)
  __INIT_LOCATED_VALUE(data__->INT1,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_1,data__->INT2,retain)
  __INIT_LOCATED_VALUE(data__->INT2,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_2,data__->INT3,retain)
  __INIT_LOCATED_VALUE(data__->INT3,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_3,data__->INT4,retain)
  __INIT_LOCATED_VALUE(data__->INT4,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_4,data__->INT5,retain)
  __INIT_LOCATED_VALUE(data__->INT5,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_5,data__->INT6,retain)
  __INIT_LOCATED_VALUE(data__->INT6,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_6,data__->INT7,retain)
  __INIT_LOCATED_VALUE(data__->INT7,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__IX0_7,data__->INT8,retain)
  __INIT_LOCATED_VALUE(data__->INT8,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_0,data__->OUT1,retain)
  __INIT_LOCATED_VALUE(data__->OUT1,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_1,data__->OUT2,retain)
  __INIT_LOCATED_VALUE(data__->OUT2,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_2,data__->OUT3,retain)
  __INIT_LOCATED_VALUE(data__->OUT3,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_3,data__->OUT4,retain)
  __INIT_LOCATED_VALUE(data__->OUT4,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_4,data__->OUT5,retain)
  __INIT_LOCATED_VALUE(data__->OUT5,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_5,data__->OUT6,retain)
  __INIT_LOCATED_VALUE(data__->OUT6,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_6,data__->OUT7,retain)
  __INIT_LOCATED_VALUE(data__->OUT7,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_7,data__->OUT8,retain)
  __INIT_LOCATED_VALUE(data__->OUT8,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(UINT,__IW100,data__->INTAN1,retain)
  __INIT_LOCATED_VALUE(data__->INTAN1,0)
  __INIT_LOCATED(UINT,__IW101,data__->INTAN2,retain)
  __INIT_LOCATED_VALUE(data__->INTAN2,0)
  __INIT_LOCATED(UINT,__IW102,data__->INTAN3,retain)
  __INIT_LOCATED_VALUE(data__->INTAN3,0)
  __INIT_LOCATED(UINT,__IW103,data__->INTAN4,retain)
  __INIT_LOCATED_VALUE(data__->INTAN4,0)
  __INIT_LOCATED(UINT,__IW104,data__->INTAN5,retain)
  __INIT_LOCATED_VALUE(data__->INTAN5,0)
  __INIT_LOCATED(UINT,__IW105,data__->INTAN6,retain)
  __INIT_LOCATED_VALUE(data__->INTAN6,0)
  __INIT_LOCATED(UINT,__IW106,data__->INTAN7,retain)
  __INIT_LOCATED_VALUE(data__->INTAN7,0)
  __INIT_LOCATED(UINT,__IW107,data__->INTAN8,retain)
  __INIT_LOCATED_VALUE(data__->INTAN8,0)
  __INIT_LOCATED(UINT,__QW100,data__->OUTAN1,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN1,0)
  __INIT_LOCATED(UINT,__QW101,data__->OUTAN2,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN2,0)
  __INIT_LOCATED(UINT,__QW102,data__->OUTAN3,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN3,0)
  __INIT_LOCATED(UINT,__QW103,data__->OUTAN4,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN4,0)
  __INIT_LOCATED(UINT,__QW104,data__->OUTAN5,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN5,0)
  __INIT_LOCATED(UINT,__QW105,data__->OUTAN6,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN6,0)
  __INIT_LOCATED(UINT,__QW106,data__->OUTAN7,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN7,0)
  __INIT_LOCATED(UINT,__QW107,data__->OUTAN8,retain)
  __INIT_LOCATED_VALUE(data__->OUTAN8,0)
  __INIT_LOCATED(BOOL,__M0_0,data__->MARCA1,retain)
  __INIT_LOCATED_VALUE(data__->MARCA1,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__M0_1,data__->MARCA2,retain)
  __INIT_LOCATED_VALUE(data__->MARCA2,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->GT51_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->GT56_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->GT57_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->GT62_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void TEST_OPENPLC_body__(TEST_OPENPLC *data__) {
  // Initialise TEMP variables

  __SET_LOCATED(data__->,MARCA1,,((!(__GET_LOCATED(data__->MARCA2,)) && (__GET_LOCATED(data__->MARCA1,) || !(__GET_LOCATED(data__->OUT1,)))) && __GET_LOCATED(data__->INT1,)));
  __SET_LOCATED(data__->,MARCA2,,((!(__GET_LOCATED(data__->MARCA1,)) && (__GET_LOCATED(data__->MARCA2,) || __GET_LOCATED(data__->OUT1,))) && __GET_LOCATED(data__->INT1,)));
  __SET_LOCATED(data__->,OUT1,,(!(__GET_LOCATED(data__->MARCA2,)) && (__GET_LOCATED(data__->MARCA1,) || __GET_LOCATED(data__->OUT1,))));
  __SET_LOCATED(data__->,OUT2,,__GET_LOCATED(data__->INT2,));
  __SET_LOCATED(data__->,OUT3,,__GET_LOCATED(data__->INT3,));
  __SET_LOCATED(data__->,OUT4,,__GET_LOCATED(data__->INT4,));
  __SET_LOCATED(data__->,OUT5,,__GET_LOCATED(data__->INT5,));
  __SET_LOCATED(data__->,OUT6,,__GET_LOCATED(data__->INT6,));
  __SET_LOCATED(data__->,OUT7,,__GET_LOCATED(data__->INT7,));
  __SET_LOCATED(data__->,OUT8,,__GET_LOCATED(data__->INT8,));
  __SET_LOCATED(data__->,OUTAN1,,__GET_LOCATED(data__->INTAN1,));
  __SET_LOCATED(data__->,OUTAN2,,__GET_LOCATED(data__->INTAN2,));
  __SET_LOCATED(data__->,OUTAN3,,__GET_LOCATED(data__->INTAN3,));
  __SET_LOCATED(data__->,OUTAN4,,__GET_LOCATED(data__->INTAN4,));
  __SET_VAR(data__->,GT51_OUT,,GT__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_LOCATED(data__->INTAN5,),
    (UINT)1000));
  __SET_LOCATED(data__->,OUT5,,(!(__GET_LOCATED(data__->INT5,)) && __GET_VAR(data__->GT51_OUT,)));
  __SET_VAR(data__->,GT56_OUT,,GT__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_LOCATED(data__->INTAN6,),
    (UINT)1000));
  __SET_LOCATED(data__->,OUT6,,(!(__GET_LOCATED(data__->INT6,)) && __GET_VAR(data__->GT56_OUT,)));
  __SET_VAR(data__->,GT57_OUT,,GT__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_LOCATED(data__->INTAN7,),
    (UINT)1000));
  __SET_LOCATED(data__->,OUT7,,(!(__GET_LOCATED(data__->INT7,)) && __GET_VAR(data__->GT57_OUT,)));
  __SET_VAR(data__->,GT62_OUT,,GT__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_LOCATED(data__->INTAN8,),
    (UINT)1000));
  __SET_LOCATED(data__->,OUT8,,(!(__GET_LOCATED(data__->INT8,)) && __GET_VAR(data__->GT62_OUT,)));

  goto __end;

__end:
  return;
} // TEST_OPENPLC_body__() 





