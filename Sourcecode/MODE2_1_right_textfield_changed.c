//Changed script for right textfield in MODE2_1.pnl

main()
{

  string test;
  string dp=$a;
  dyn_string test2;
  dyn_dyn_string element;
  dyn_dyn_int types;
  getValue("","text",test);
  test2=strsplit(test,",");
  if ((dpExists("datavalue"))==0){
    element[1]=makeDynString("combivalue","");
    element[2]=makeDynString("","value1");
    element[3]=makeDynString("","value2");
    types[1]=makeDynString(DPEL_STRUCT,0);
    types[2]=makeDynString(0,DPEL_STRING);
    types[3]=makeDynString(0,DPEL_STRING);
    dpTypeCreate(element,types);
    dpCreate("datavalue","combivalue");
  }
  dpSet("datavalue.value1",dp);
  dpSet("datavalue.value2",test);
  
}