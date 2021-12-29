#include "node.h"
#include <iostream>
using namespace std;
#define FOR(a, b) for (int a = 0; a < b; a++)
#define ECOMPARE(a,b) if(a==b)
#define EQUATE(a,b) a=b
#define ACOMPARE(a,b) a<b
int i,j,k,k3=0;
void printRT(vector<RoutingNode*> nd){
	for (int i = 0; i < nd.size(); i++) {
	  nd[i]->printTable();}}

void routingAlgo(vector<RoutingNode*> nd){
  //Your code here
  int num(nd.size());
  bool nc(false);
  
  vector<struct routingtbl> rtb;
  int num2(0);
  while(true)
  {
  	nc=true;
  	//set true only if tables are same 
  	
  	rtb.clear();
    FOR(j,num)
  	{
  		rtb.push_back(nd[j]->getTable());
  	}
  	//sending messages to all the other nodes there
  	FOR(i,num)
  	{
  		nd[i]->sendMsg();
  		
  	}
  	FOR(k,num)
  	{
  		if(rtb[k].tbl.size()!=(nd[k]->getTable()).tbl.size())
  		{
  			nc=false;
  			break;
  		}
  		//comparing the tables
  		FOR(k3,(nd[k]->getTable()).tbl.size())
  		{
  			
  			ECOMPARE(rtb[k].tbl[k3].nexthop,(nd[k]->getTable()).tbl[k3].nexthop)
  			{
  				ECOMPARE(rtb[k].tbl[k3].ip_interface,(nd[k]->getTable()).tbl[k3].ip_interface)
  				continue;
  				else 
  				{
  					EQUATE(nc,false);
  					break;}}
  			else
  			{
  				EQUATE(nc,false);
  				break;}}}
  	if(nc)
  	break; }
//routing algo converges 
  printRT(nd);
}
void RoutingNode::recvMsg(RouteMsg *msg) {
  //your code here
  int n(mytbl.tbl.size());
  i=0,j=0;
  int k(msg->mytbl->tbl.size());
  bool efound(false);
  while(ACOMPARE(j,k))
  {
  	mytbl.tbl.push_back(msg->mytbl->tbl[j]);
    mytbl.tbl[mytbl.tbl.size()-1].cost=mytbl.tbl[mytbl.tbl.size()-1].cost+1;
  	EQUATE(mytbl.tbl[mytbl.tbl.size()-1].nexthop,msg->from);  			
  	EQUATE(mytbl.tbl[mytbl.tbl.size()-1].ip_interface,msg->recvip);
  	efound=false;
  	FOR(i,n)
  	{
  		int rip=0;
  		ECOMPARE((((msg->mytbl->tbl[j]).dstip)),(mytbl.tbl[i].dstip))	
  		{
  			efound=true;
  			int mn=msg->mytbl->tbl[j].cost+1; 
  			if(mn<mytbl.tbl[i].cost) 
  			{
  				if(isMyInterface(msg->mytbl->tbl[j].nexthop)) 
  				{
  					break;
  					//ignored path
  				}
  				else
  				{
  					EQUATE(mytbl.tbl[i].nexthop,msg->from);
  					EQUATE(mytbl.tbl[i].ip_interface,msg->recvip);
  					EQUATE(mytbl.tbl[i].cost,msg->mytbl->tbl[j].cost+1;)
  					break;
  				}}}}
  	if(efound)
  	{
  		mytbl.tbl.pop_back();
  	}j=j+1;}}

