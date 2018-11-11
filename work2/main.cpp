#include "LHYFileOp.h"


int main(){
   LHYFileOp *Opt=new LHYFileOp("LHYLinux2.txt");
   Opt->F_WRITE("LHYLinux2");

   Opt->F_WRITE(" LHY201822080309 LHY2018080309 ");
  

 Opt->F_READ(10,20);
   Opt->F_READ(30,40);
   Opt->F_READ(10,90);


}
  
