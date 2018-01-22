//Clicked script for Start Button in SimulationMode2.pnl

main(mapping event)
{
  dyn_string lastnode,lasttype,dpout_final,temp,temp2,temp3,save_value,dpout_test,temp4,dplist,assist1,assist4;
  dyn_dyn_string lastnodebytype,dp_final,dpout,LoopPossibility,loop,assist2;
  int i,j,k=1,l,n=0,parenttype;
  ulong sum;
  bool found;
  string type,parent,data,assist3;
  
  isLoop=FALSE;x=0;count2=0;globalCounter=1;LoopPossibility="";dynClear(LoopPossibility);counterloop=0;work=TRUE;workcombi="";done=FALSE;suspiciousloop=FALSE;
  treshold="";dynClear(treshold);count_combination=0;suspiciousnum=0;count_suspicious=0;multi=1;
  
  for (i=1;i<=dynlen(nodesGlobal);i++){
    count[i]=0;
  }

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
    for (j=1;j<=dynlen(lastnodebytype[i]);j++){
      saveDP(dp_final,lastnodebytype[i][j],temp2);   
      dynAppend(dpout_final,temp2);    
    }
  }
  

  for (i=1;i<=dynlen(fulldata);i++){
    assist2[i]=strsplit(fulldata[i][1],".");
    assist4[i]=assist2[i][1];
    dynRemove(assist2[i],1);
  }
  
  for (i=1;i<=dynlen(dpout_final);i++){
    assist1=strsplit(dpout_final[i],".");
    assist3=assist1[1];
    dynRemove(assist1,1);
    for (j=1;j<=dynlen(fulldata);j++){
      if ((dynlen(fulldata[j])>1)&&(assist1==assist2[j])&&(dpTypeName(assist3)==assist4[j])){
        dynAppend(dplist,dpout_final[i]);
        dynClear(assist1);
        break;
      }
    }
  }
  
  for (i=1;i<=dynlen(dplist);i++){
    DebugN(dplist[i]);
    delay(0,10);
  }
  
  for (i=1;i<=dynlen(fulldata);i++){
    DebugN(fulldata[i]);
    delay(0,10);
  }  
 
  
  dpout_test=dplist;
  for(i=1;i<=dynlen(dpout_test);i++){
    temp3=strsplit(dpout_test[i],".");
    assist3=temp3[1];
    dynRemove(temp3,1);
    for (j=1;j<=dynlen(fulldata);j++){
       if ((temp3==assist2[j])&&(dpTypeName(assist3)==assist4[j])){     
         x[i]=(dynlen(fulldata[j])-1);}
    }
    dynClear(temp3);  
  }
  dynClear(dpout_test);dynClear(assist2);dynClear(assist4);
  
  //DebugN(x);
  for (i=1;i<=dynlen(x);i++){
    multi=multi*x[i];
  }  
  
  for(i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
        fwCU_connectState("CheckLoopCB",nodesGlobal[i][j]);
        delay(0,10); 
      }  
  }
  
  dynClear(count);
  
  sum=1;

  simulate(dplist,n,sum,save_value,LoopPossibility);
  
  for(i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
        fwCU_disconnectState(nodesGlobal[i][j]);
        delay(0,10); 
      }  
  }  
  
  
  //DebugN(LoopPossibility);
  suspiciousnum=dynlen(LoopPossibility);
  
  for(i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
        fwCU_connectState("VerifyLoopCB",nodesGlobal[i][j]);
        delay(0,10); 
      }  
  }
  
 simulatefurther(dplist,LoopPossibility,loop);
  
  for(i=1;i<=dynlen(nodesGlobal);i++){
    for (j=1;j<=dynlen(nodesGlobal[i]);j++){
        fwCU_disconnectState(nodesGlobal[i][j]);
        delay(0,10); 
      }  
  }
  
  DebugN("Datapoints' order: ");
  DebugN(strjoin(dplist,", "));
  DebugN("The combinations of datapoints that can trigger loops:");
  DebugN(loop);
  
}

void CheckLoopCB(string node, string state){
 int i,j;
 counterloop=0;
 for (i=1;i<=dynlen(statepernode);i++){
     if (statepernode[i][1]==node){
       //DebugN(node+" : "+state);
       dynAppend(statepernode[i],state); 
       for (j=1;j<=(dynlen(statepernode[i])-1);j++){
         if (statepernode[i][j]==state){      
            counterloop++;
         }
       }
       
       if (counterloop>1) {suspiciousloop=TRUE;DebugN("Node: "+node+", Counter Loop: "+counterloop);}
       break;
     }
 }
}

void VerifyLoopCB(string node, string state){
 int i,j;
 counterloop=0;
 for (i=1;i<=dynlen(statepernode);i++){
     if (statepernode[i][1]==node){
       //DebugN(node+" : "+state);
       dynAppend(statepernode[i],state); 
       for (j=1;j<=(dynlen(statepernode[i])-1);j++){
         if (statepernode[i][j]==state){      
            counterloop++;
         }
       }
       if (counterloop>10) {isLoop=TRUE;}
       break;
     }
 }
    
}


void simulate(dyn_string dplist, int &n, ulong &sum, dyn_string &save_value, dyn_dyn_string &LoopPossibility){
  
int j,k;
dyn_string temp,temp2;
string temp3,temp4;
dyn_dyn_string currentstate;


if (n==(dynlen(dplist)))
{
   dynClear(statepernode);    
   SavePerNode();
   suspiciousloop=FALSE;
   count_combination++;
   DebugN("Count Combinatiosn : "+count_combination);
   DebugN("Set Values: "+strjoin(save_value,", "));
   for (j=1;j<=dynlen(save_value);j++){
     dpSet(dplist[j],save_value[j]);
   }
   delay(0,delay1);
   saveState(currentstate);
   DebugN("Current States: ");
   DebugN(currentstate);
   if (suspiciousloop) 
   {
     temp=save_value;
     DebugN("Loop Possibility: Yes"); dynAppend(LoopPossibility[globalCounter],temp); globalCounter++; work=FALSE;
   }
   else {work=TRUE;DebugN("Loop Possibility: No");}
   if (work & !(done)){workcombi=save_value;treshold=currentstate;done=TRUE;}   
   sum=1;
   for (j=dynlen(x);j>=2;j--){
     sum=sum*x[j];
     if ((count_combination%sum)==0){
       n--;
     }     
   }
   //DebugN("n :"+n);
}
else {
    n++;
    temp=strsplit(dplist[n],".");
    temp4=temp[1];
    dynRemove(temp,1);
    for (j=1;j<=dynlen(fulldata);j++){
      temp2=strsplit(fulldata[j][1],".");
      temp3=temp2[1];
      dynRemove(temp2,1);
      if ((temp==temp2)&&(dpTypeName(temp4)==temp3)){
        dynClear(temp);dynClear(temp2);
        for (k=2;k<=dynlen(fulldata[j]);k++){
           save_value[n]=fulldata[j][k];
           simulate(dplist,n,sum,save_value,LoopPossibility);
        }
        break;
      }
    }
    
  }
}

void simulatefurther(dyn_string dplist, dyn_dyn_string LoopPossibility, dyn_dyn_string &loop){
  int i,j,k=1;
  string temp;
  dyn_dyn_string currentstate;
  
  for (i=1;i<=dynlen(LoopPossibility);i++){
    dynClear(statepernode);    
    SavePerNode();
    isLoop=FALSE;
    count_suspicious++;
    DebugN("Total suspicious loops: "+suspiciousnum);
    DebugN("Count suspicious loops: "+count_suspicious);
    for(j=1;j<=dynlen(LoopPossibility[i]);j++){
      dpSet(dplist[j],LoopPossibility[i][j]);
    }
    delay(0,delay2);
    DebugN("Set Values: "+strjoin(LoopPossibility[i],", "));
    saveState(currentstate);
    DebugN("Current States : ");
    DebugN(currentstate);
    if (isLoop) {
      temp=LoopPossibility[i];
      dynAppend(loop[k],temp);
      k++;
      DebugN("IT'S A LOOOOOP!!!"); 
    }
    else DebugN("THIS ONE IS NOT A LOOP");
    DebugN("Loosp Detected so Far: "+(k-1));
    for(j=1;j<=dynlen(workcombi);j++){
      dpSet(dplist[j],workcombi[j]);
    }
    delay(0,delay2);
    //DebugN("workcombi:"+workcombi);
    saveState(currentstate);
    while (currentstate != treshold){
      for(j=1;j<=dynlen(workcombi);j++){
      dpSet(dplist[j],workcombi[j]);
      }
      saveState(currentstate);
    }
  }
}
