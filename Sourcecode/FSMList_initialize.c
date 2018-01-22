//Initialization for FSMList.pnl

main()
{
  dyn_dyn_string nodes,type,nodes_final,type_final;
  string top_node=$4;
  int i,j;
  bool START=TRUE;

  addGlobal("nodesGlobal",DYN_DYN_STRING_VAR); addGlobal("typeGlobal",DYN_DYN_STRING_VAR);
  addGlobal("iy",DYN_DYN_INT_VAR); addGlobal("ic",INT_VAR);
  ic=0;iy=0;
  getstructure(top_node,nodes,type);  
  changestructure(nodes,nodes_final,type_final);
  nodesGlobal=nodes; typeGlobal=type;
  printstructure();
  
}