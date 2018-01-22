//ScopeLib for FSMList.pnl


global dyn_dyn_string statepernode,fulldata,fulldatapoint,treshold;
global bool work,suspiciousloop,done,isLoop;
global dyn_string workcombi,AllStates;
global int globalCounter,counterloop;
global dyn_int count,count2,x;

bool isLastNode(string node){
dyn_string temp,except;
  fwTree_getChildren(node,temp,except);
  if (temp == ""){
    return(1);  
  }
  else return(0);
}

void printSymbolInOrder(dyn_string ds, int &ix, int i, int j)
{
    ix=20;iy[i][j]=150+30*ic;ic++;
    addSymbol(myModuleName(),myPanelName(),"Panel1.pnl","",ds,ix,iy[i][j],0,1,1,""); 
}

void changestructure(dyn_dyn_string oldstructure, dyn_dyn_string &finalstructure, dyn_dyn_string &finaltypestructure){
dyn_dyn_string nodesx;
int i,j,parent_type;
bool check,isLast;
string parent_node;

  for(i=1;i<=dynlen(oldstructure);i++){
    for(j=1;j<=dynlen(oldstructure[i]);j++){
      if (isLastNode(oldstructure[i][j])){
        dynAppend(nodesx,oldstructure[i][j]);      
      } 
    }  
  }
  
  for (i=1;i<=dynlen(nodesx);i++){
    j=1;
    check=TRUE;
    while (check){
    parent_node = fwCU_getParent(parent_type,nodesx[i][j]);
        if (parent_node != ""){
          dynAppend(nodesx[i],parent_node);
          j++; 
        }
        else check=FALSE;
    }
  }
  
  for (i=1;i<=dynlen(nodesx);i++){
    for (j=dynlen(nodesx[i]);j>=1;j--){
      finalstructure[i][dynlen(nodesx[i])-j+1]=nodesx[i][j];
    }   
  }
  
  for (i=1;i<=dynlen(finalstructure);i++){
    for(j=1;j<=dynlen(finalstructure[i]);j++){
      fwCU_getType(finalstructure[i][j],finaltypestructure[i][j]);
    }
  }
}

void extractstructure(string datapointtype, dyn_dyn_string &final){
  dyn_dyn_string dpstructure,dpstructure2,temp;
  string temp2,temp4;
  int count=0,j,gaps,k,l,m,i,n,regreturn;
  dyn_int temp3;
  dyn_dyn_int number,helps;
  dpTypeGet(datapointtype,dpstructure,number,TRUE);
  
  for (i=1;i<=(dynlen(number));i++){
    for(j=1;j<=dynlen(number[i]);j++)
    {
      if ((number[i][j] != 1)&&(number[i][j] != 0)&&(number[i][j] != 41)){
          temp4=dpstructure[i][j];
          dynAppend(temp,temp4);
          count++;
          dynAppend(helps,i);
      }
    }
  }
  
  
  for (i=1;i<=count;i++){
    j=1;
    while (temp[i][j] != dpstructure[1][1]){
      getdpparents(temp[i][j],dpstructure,number,temp2,helps[i][j],regreturn);
      dynAppend(temp[i],temp2); dynAppend(helps[i],regreturn);
      j++;
    }  
  }
  

  final=temp;
  
  for (i=1;i<=dynlen(temp);i++){
    for (j=dynlen(temp[i]);j>=1;j--){
      final[i][dynlen(temp[i])-j+1]=temp[i][j];
    }   
  }
  
}

void getdpparents(string temp, dyn_dyn_string dpstructure, dyn_dyn_int number, string &parents,int reg, int &regreturn)
{
  int k=1,i,j,a,b,l=1; 
  bool check =TRUE;
  
    
    for(j=1;j<=dynlen(number[reg]);j++)
    { 
      if ((dpstructure[reg][j]==temp)){
           a = reg;b = j;
      }
    }
  
  

  while (check){
      if (number[a-k][b-l] == 41)
      { 
        l++; k++;
      }  
      else if (dpstructure[a-k][b-l] != ""){
        parents = dpstructure[a-k][b-l];
        regreturn = a-k;
        check = FALSE; l=1;   
      }
      else k++;
    }
}



void getstructure(string top_node, dyn_dyn_string &nodes, dyn_dyn_string &type){
  dyn_string temp,except;
  int i=1,j;
  bool stopping = FALSE, stop, prev_stop;
       
  nodes[i]=top_node;
  
  while (!(stopping)){
    stop = TRUE;

    for (j=1;j<=dynlen(nodes[i]);j++)
      {
        prev_stop = stop;
        fwCU_getType(nodes[i][j],type[i][j]);  
        fwTree_getChildren(nodes[i][j],temp,except);
        if (temp != "")
        {    
          dynAppend(nodes[i+1],temp);
          stop = FALSE;
        }
        else{
          stop = TRUE; 
          }
         stopping = stop && prev_stop;
      }
    i++;
  }
}

void printstructure(){
  dyn_dyn_string dp_final;
  dyn_string states,temp,temp2,ds,str2,except;
  string str,currentstate,statecolor,dp;
  int i=1,j,k,ix;
  
  for (i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++)
      { 
        fwTree_getChildren(nodesGlobal[i][j],temp,except);
        if (temp != "")
        {    
          fwFsm_getObjectStates(typeGlobal[i][j],states);
          fwCU_getState(nodesGlobal[i][j],currentstate);
          fwCU_getStateColor(nodesGlobal[i][j],currentstate,statecolor);
          ds=makeDynString("$1:"+nodesGlobal[i][j],"$2:"+typeGlobal[i][j],"$3:"+strjoin((states),", "),"$5:"+currentstate,"$6:"+statecolor);
          printSymbolInOrder(ds,ix,i,j);
        }
        else{
          if (dpExists(nodesGlobal[i][j])==1){
            extractstructure(dpTypeName(nodesGlobal[i][j]),dp_final);
          }
          else 
          {
            extractstructure(dpTypeName(dpAliasToName(nodesGlobal[i][j])),dp_final);
          }
          saveDP(dp_final,nodesGlobal[i][j],str2);
          fwCU_getState(nodesGlobal[i][j],currentstate);
          fwCU_getStateColor(nodesGlobal[i][j],currentstate,statecolor);
          ds=makeDynString("$1:"+nodesGlobal[i][j],"$2:"+typeGlobal[i][j],"$3:"+strjoin((states),", ")+" || "+strjoin((str2),", "),"$5:"+currentstate,"$6:"+statecolor);       
          printSymbolInOrder(ds,ix,i,j);     
          dynClear(str2);
         }
      }
    ic++;
  }
}

printStateCB(string node, string state){
   dyn_dyn_string dp_final;
   dyn_string ds,str2,states;   
   string statecolor,type,str,dp;
   int ix=20,i,j;
   
   fwCU_getStateColor(node,state,statecolor);
   fwFsm_getObjectStates(type,states);
   if (isLastNode(node)){
     fwCU_getDp(node,dp,"");
     DebugN(dpTypeName(dp));
     extractstructure(dpTypeName(dp),dp_final);
     for (i=1;i<=dynlen(dp_final);i++){
         str=strjoin(dp_final[i],".");
         strreplace(str,dp_final[i][1],node);
         str2[i]=str;
     }
     ds=makeDynString("$1:"+node,"$2:"+type,"$3:"+strjoin((states),", ")+" || "+strjoin((str2),", "));
     dynClear(str2);     
   }
   else{
     ds=makeDynString("$1:"+node,"$2:"+type,"$3:"+strjoin((states),", "));
   }
   for (i=1;i<=dynlen(nodesGlobal);i++){
     for (j=1;j<=dynlen(nodesGlobal[i]);j++){
       if (nodesGlobal[i][j]==node){
          addSymbol(myModuleName(),myPanelName(),"Panel1.pnl","",ds,ix,iy[i][j],0,1,1,"");
        }
     }
   }   
}

void saveDP(dyn_dyn_string dp_final, string node, dyn_string &output){
  int i;
  string str;
  for (i=1;i<=dynlen(dp_final);i++){
    str=strjoin(dp_final[i],"."); 
    if (dpExists(node)==1)
      strreplace(str,dp_final[i][1],node);
    else 
      strreplace(str,dp_final[i][1]+".",dpAliasToName(node));
    output[i]=str;
  }
}

void saveState(dyn_dyn_string &states){
  int i,j;
  for (i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
      fwCU_getState(nodesGlobal[i][j],states[i][j]);
    }
  }
}

void SavePerNode(){
  int i,j,l=1; string temp,temp2;
  for (i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
      temp2=nodesGlobal[i][j];
      dynAppend(statepernode[l],temp2);l++;
    }
  }
}