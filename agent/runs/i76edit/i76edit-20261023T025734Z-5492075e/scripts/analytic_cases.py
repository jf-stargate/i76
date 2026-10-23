#!/usr/bin/env python3
"""13 synthetic native-branch illustrations. Not original executable emulation."""
import json
S=0x8000
def direct(mode,h,m,kind,geometry):
 if not geometry or (mode==4 and geometry!=2) or h!=S:return h,m
 return (123,0) if mode==2 else (h,kind)
def neighbor(mode,h,m,ns,kind):
 if h==S:
  if not ns:return h,m
  return (sum(ns)//len(ns),0) if mode==3 else (h,0)
 if 0<=m<6:return h,0 if mode==3 else kind
 return h,m
def test():
 cases=[
 (direct(2,S,6,2,2),(123,0)),(direct(2,777,6,2,2),(777,6)),
 (direct(4,S,0,3,2),(S,3)),(direct(4,123,0,3,2),(123,0)),
 (direct(4,S,0,3,1),(S,0)),
 (neighbor(3,S,7,[100,200],3),(150,0)),
 (neighbor(5,S,7,[100,200],3),(S,0)),(neighbor(3,S,7,[],3),(S,7)),
 (neighbor(3,100,3,[],3),(100,0)),(neighbor(5,100,0,[],3),(100,3)),
 (neighbor(3,100,6,[200],3),(100,6)),(neighbor(5,100,7,[200],3),(100,7)),
 (neighbor(5,100,-1,[200],3),(100,-1))]
 x={"test_count":len(cases),"passed_count":sum(a==b for a,b in cases),
    "original_code_executed":False}
 print(json.dumps(x,indent=2));assert x["passed_count"]==x["test_count"]
if __name__=="__main__":test()
