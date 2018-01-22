//Initialization script for SimulationMode1.pnl

main()
{
  dyn_string lasttype,lastnode,temp,ds;
  dyn_string temp2;
  dyn_dyn_string dp_final,lastnodebytype;
  int i,j,k=1,l=1,x,y,c;
  bool found; 
  c=0; 
  
  dpSet("datavalue.value2",0);
  dpConnect("dpCallBack","datavalue.value1");

  for (i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
      if (isLastNode(nodesGlobal[i][j])){
        lastnode[k]=nodesGlobal[i][j];
        if (dpExists(nodesGlobal[i][j])==1){
          lasttype[k]=dpTypeName(nodesGlobal[i][j]);        
        }
        else{
          lasttype[k]=dpTypeName(dpAliasToName(nodesGlobal[i][j]));        
        }
        k++;
      }
    }
  }
  
  temp[1]=lasttype[1];
  
  for (i=2;i<=dynlen(lasttype);i++){
      found = FALSE;
      for (j=1;j<=dynlen(temp);j++){
        if (lasttype[i] == temp[j]){
          found=TRUE;
        }      
      }
      if (!found){
        dynAppend(temp,lasttype[i]);}
  }
  
  
  for (i=1;i<=dynlen(lastnode);i++){
    for (j=1;j<=dynlen(temp);j++){
      if (lasttype[i]==temp[j]){
       dynAppend(lastnodebytype[j],lastnode[i]);
      }
    }
  }
  
  for (i=1;i<=dynlen(temp);i++){
    extractstructure(temp[i],dp_final);
    found=FALSE;
    for (j=1;j<=dynlen(dp_final);j++){
      if(j>1){
      for(k=1;k<=dynlen(fulldata);k++){
        if (fulldata[k][1]==strjoin(dp_final[j],"."))
        found=TRUE;      
      }
      }
      if (!found){
        fulldata[l][1]=strjoin(dp_final[j],".");
        DebugN(fulldata[l]);
        temp2[l]=fulldata[l][1];
        if (dpExists(lastnodebytype[i][1])==1){
          strreplace(temp2[l],temp[i],lastnodebytype[i][1]);l++;
        }
        else{
          strreplace(temp2[l],temp[i]+".",dpAliasToName(lastnodebytype[i][1]));l++;}
      }
    }
  }
 
  //for (i=1;i<=dynlen(fulldata);i++){
    //ds=makeDynString("$a:"+fulldata[i][1]);
    //x=20;y=100+30*c;
    //addSymbol(myModuleName(),myPanelName(),"Mode1.pnl","",ds,x,y,0,1,1,"");
    //c++;
 // }
  
  for (i=1;i<=dynlen(fulldata);i++){
    x=20;y=100+30*c;
    if (dpElementType(temp2[i])==DPEL_INT){
      ds=makeDynString("$a:"+fulldata[i][1],"$b:INTEGER");
      addSymbol(myModuleName(),myPanelName(),"Mode1.pnl","",ds,x,y,0,1,1,"");
      c++;}
    else if (dpElementType(temp2[i])==DPEL_STRING){
      ds=makeDynString("$a:"+fulldata[i][1],"$b:STRING");
      addSymbol(myModuleName(),myPanelName(),"Mode1.pnl","",ds,x,y,0,1,1,"");
      c++;}
    else if (dpElementType(temp2[i])==DPEL_BOOL){
      ds=makeDynString("$a:"+fulldata[i][1],"$b:BOOLEAN");
      addSymbol(myModuleName(),myPanelName(),"Mode1.pnl","",ds,x,y,0,1,1,"");
      c++;}
    else if (dpElementType(temp2[i])==DPEL_FLOAT){
      ds=makeDynString("$a:"+fulldata[i][1],"$b:FLOAT");
      addSymbol(myModuleName(),myPanelName(),"Mode1.pnl","",ds,x,y,0,1,1,"");
      c++;}
    else{
      ds=makeDynString("$a:"+fulldata[i][1],"$b:OTHER");
      addSymbol(myModuleName(),myPanelName(),"Mode1.pnl","",ds,x,y,0,1,1,"");
      c++;}
      
  }
  
  delay(2,0);
  for (i=1;i<=dynlen(fulldata);i++){
    for (j=1;j<=(dynlen(fulldata[i])-1);j++){
      Debug(fulldata[i][j]);
    }
    DebugN(fulldata[i][j]);
  }  
  
}

void dpCallBack(string dp, string value){
  int i,j;
  string temp;
  dyn_string temp2;
  for (i=1;i<=dynlen(fulldata);i++){
    if (value==fulldata[i][1]){
      dpGet("datavalue.value2",temp);
      temp2=strsplit(temp,",");
      for (j=2;j<=dynlen(fulldata[i]);j++){
        dynRemove(fulldata[i],2);     
      }
      for (j=1;j<=dynlen(temp2);j++){
        fulldata[i][j+1]=temp2[j];      
      }      
      DebugN(fulldata[i]);
      break;
    }
  }
}