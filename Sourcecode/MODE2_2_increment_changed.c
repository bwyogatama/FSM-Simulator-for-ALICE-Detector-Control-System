//Changed script for INCREMENT textfield in MODE2.pnl

main()
{

  string increment;
  string dp=$a;
  dyn_string test2;
  dyn_dyn_string element;
  dyn_dyn_int types;
  getValue("","text",increment);
  if ((dpExists("datavalue2"))==0){
    element[1]=makeDynString("combivalue2","");
    element[2]=makeDynString("","value1");
    element[3]=makeDynString("","value2");
    element[4]=makeDynString("","value3");
    element[5]=makeDynString("","value4");
    types[1]=makeDynString(DPEL_STRUCT,0);
    types[2]=makeDynString(0,DPEL_STRING);
    types[3]=makeDynString(0,DPEL_STRING);
    types[4]=makeDynString(0,DPEL_STRING);
    types[5]=makeDynString(0,DPEL_STRING);
    dpTypeCreate(element,types);
    dpCreate("datavalue2","combivalue2");
  }
  dpSet("datavalue2.value1",dp);
  dpSet("datavalue2.value4",increment);
  
}