//Clicked script for Simulation Button in Simulation.pnl

main(string id)
{
  dyn_string top_node,except,ds;
  bool stop=FALSE;
  int i=1;
  fwTree_getChildren("FSM",top_node,except);
  while (!(stop)){
    if (id == top_node[i]){  
        ds=makeDynString("$4:"+top_node[i]);
        ChildPanelOn("FSMList.pnl","FSM List",ds,0,0);  
        stop=TRUE;  
    }
    i++;
  }
}