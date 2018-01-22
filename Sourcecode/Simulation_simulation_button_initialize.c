//Initialization for Simulation Button in Simulation.pnl

main(){
  dyn_string top_node,except;
  int i;
  fwTree_getChildren("FSM",top_node,except);
  for (i=1;i<=dynlen(top_node);i++){
    CASCADE_BUTTON2.insertItemId("",0,-1,top_node[i],top_node[i]);
  }
}

