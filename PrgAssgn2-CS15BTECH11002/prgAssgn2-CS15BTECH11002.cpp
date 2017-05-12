
#include <iostream>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <fstream>
#include<ctype.h>
using namespace std;

void init_reg_file();
void getabc();
void getab();
void display();
void init_function();
void jump();
void geta();
void getao();

struct reg 						//Structure which stores register names ($t1, $t2...etc)and their corresponding values
{
	char alt_name[5];			
	int value;
};

struct array 					//Structure which stores arraynames and its corresponding simulated starting address 
{
	string aname;
	int addvalue;
};
	string x,str,arrayname,ls;				
	string d=",";
	int a ,b,c,y;
	fstream  afile	;
	int offset;
	string num,reg,section;
	int temp,count,checker,pre_count;		
	int *a1=(int *)malloc(900);		//Array to store continuously all array values defined

	int mode,immediate;				


 struct array arr[32];					//Store max 32 arrays for implementation 
 int struct_arraycount=0;
 int variableaddress=94151269;			//Variable Address to  Increase the count to 4 and store next element 
 int startaddress=94151269;				//Starting simulated address


 struct reg reg_file[32];				
 
int main(int argc, char *args[])
{
	 init_reg_file();				   // To initialise the register file 
	string funct[18]={"add","addi","sub","mul","and","andi","or","ori","nor","slt","slti","lw","sw","beq","bne","j","halt","la"};

	afile.open(args[1],ios::in );		//Open file in read mode 

     cout<<"PRess 1 for EXECUTION-MODE or 2 for Step-by-Step Mode\n ";
     cin>>mode;

      
    while (!afile.eof())
    {
    	afile>>x;										//Load string from file untill space  
    	for (int i = 0; i < 18; i++)
    	{
    		if(x==funct[i]){							// Find for instructions like add, addi etc..
    				y=i;
    				break;
    			}
    		else if(*x.rbegin()==':'){					//Jumps to next word if its a label
    			y=19;
    			arrayname=x;
    			break;}
    		
    		else if(x==".word"){						// If array is intitialised store the array and its values till the end
    			 arrayname= arrayname.substr(0, arrayname.size()-1);
    			arr[struct_arraycount].aname=arrayname;
    			arr[struct_arraycount].addvalue=variableaddress;
    			variableaddress=variableaddress-4;
    			struct_arraycount++;
    			afile>>x;
    			while(*x.rbegin()==','){
    				x = x.substr(0, x.size()-1);
    				temp=atoi( x.c_str() );
    				a1[count]=temp;
    				count++;
    				variableaddress=variableaddress+4;
    				afile>>x;
    			}
    			temp=atoi( x.c_str() );
    			a1[count]=temp;
    			count++;	
    			variableaddress=variableaddress+8;  
    			pre_count=count;			
    			y=19;
    			break;

    		}
    		else if (x==".data"||x==".text"){
    			y=19;
    			break;
    		}
    		
    	}
	 switch(y)
   		{
   		case 0 :								//Case for add
   			afile>>x;
   			 getabc();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 reg_file[a].value=reg_file[b].value+reg_file[c].value;
   			 if(mode==2){
   			 	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
			 break;
   		case 1 :								//Case for addi
   			afile>>x;
   			 getab();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 immediate=0;
   			 afile>>immediate;
   			if(immediate==0) {
   			 	cout<<"SYNTAX Error"<<endl;
   			 	exit(0);
   			 }
   			 reg_file[a].value=reg_file[b].value+immediate;
   			 if(mode==2){
   			 	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
   			break;
  		case 2 :								//Case for sub
  			afile>>x;
  			 getabc();
  			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 reg_file[a].value=reg_file[b].value-reg_file[c].value;
   			 if(mode==2){
   			 	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
     		break;
   		case 3 :								//Case for mul
   			afile>>x;
   			 getabc();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 reg_file[a].value=reg_file[b].value*reg_file[c].value;
   			 if(mode==2){
   			 	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	        break;
   		case 4 :								//Case for and
   			afile>>x;
   			 getabc();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 reg_file[a].value=reg_file[b].value&&reg_file[c].value;
   			 if(mode==2){
   			 	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
			break;
	    case 5 :							//Case for andi
   			afile>>x;
   			 getab();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 immediate=0;
   			 afile>>immediate;
   			if(immediate==0) {
   			 	cout<<"SYNTAX Error"<<endl;
   			 	exit(0);
   			 }
   			reg_file[a].value=reg_file[b].value&&immediate;
   			if(mode==2){
   				cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;
	    case 6 :							//Case for or
	    	afile>>x;
   			 getabc();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 reg_file[a].value=reg_file[b].value||reg_file[c].value;
   			 if(mode==2){
   			 	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;
	    case 7 :						//Case for ori
	    	 afile>>x;
   			 getab();
   			 if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			 immediate=0;
   			 afile>>immediate;
   			if(immediate==0) {
   			 	cout<<"SYNTAX Error"<<endl;
   			 	exit(0);
   			 }
   			reg_file[a].value=reg_file[b].value||immediate;
   			if(mode==2){
   				cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;	
	    case 8 :							//Case for nor
	    	afile>>x;
   			getabc();
   			if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			reg_file[a].value=!(reg_file[b].value||reg_file[c].value);
	    	if(mode==2){
	    		cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	    	break;
	    case 9 :							//Case for slt
	    	afile>>x;
   			getabc();
   			if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			
   			if (reg_file[b].value<reg_file[c].value)
   			{
   				reg_file[a].value=1;
   			}
   			else{
   				reg_file[a].value=0;
   			}
   			if(mode==2){
   				cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;
	    case 10 :							//Case for slti
	    	afile>>x;
   			getab();
   			if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
   			immediate=0;
   			 afile>>immediate;
   			if(immediate==0) {
   			 	cout<<"SYNTAX Error"<<endl;
   			 	exit(0);
   			 }
   			if (reg_file[b].value<immediate)
   			{
   				reg_file[a].value=1;
   			}
   			else{
   				reg_file[a].value=0;
   			}
   			if(mode==2){
   				cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;
	    case 11 :							//Case for lw
	    	afile>>x;
	    	getao();
	    	if(a==0||b==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
            temp=reg_file[b].value;
            temp=	temp+offset;
            reg_file[a].value= a1[(temp-startaddress)/4];
            if(mode==2){
            	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
			break;
	    case 12 :							//Case for sw
	    	afile>>x;
	    	getao();
	    	if(a==0||b==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
			temp=reg_file[b].value;
	    	//cout<<temp-reg_file[b].value<<"im x"<<endl;
           	temp=temp+offset;
            a1[(temp-startaddress)/4] =reg_file[a].value;
            if(mode==2){
            	cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
			break;
	    case 13 :							//Case for beq
	    	afile>>x;
	    	getab();
	    	if (reg_file[a].value==reg_file[b].value)
	    	{
	    		jump();
	    	}
	    	else{
	    		afile>>x;
	    	}
	    	if(mode==2){
	    		cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;	
	    case 14 :							//Case for bne
	    	afile>>x;
	    	getab();
	    	if (reg_file[a].value!=reg_file[b].value)
	    	{	
	    		jump();
	    	}
	    	else{
	    		afile>>x;
	    	}
	    	if(mode==2){
	    		cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;
	    case 15 :							//Case for jump label
	    	jump();
	    	if(mode==2){
	    		cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
	       break;
	    case 16 :							//CAse for halt
	    	afile>>x;
	    	cout<<"The final status of registers are"<<endl;
	       display();
	       break;
	     case 17:							//CAse for Load array address
	     	afile>>x;
			geta();
			if(a==0){
   			 	cout<<"Error $zero cant be modified"<<endl;
   			 	exit(0);
   			 }
	     	afile>>x;
	     	for (int i = 0; i < 32; i++)
	     	{
	     		if(x==arr[i].aname){
	     			reg_file[a].value=arr[i].addvalue;
	     			break;
	     		}
	     		else if(i==31){
	     			cout<<"SYNTAX ERROR ARRAY NAME NOT FOUND"<<endl;
	     			exit(0);
	     		}

	     	}
	     	
	     	if(mode==2){
	     		cout<<"The status of registers are"<<endl;
   			 	display();
   			 }
			break;
      	case 19:								//IF label found skip it and jump to next word
	     	break;
	    default:								//Print Error if instruction is invalid
      		cout << "SYNTAX Error"<<endl;
      		exit (0);	
      		break;
   }
    }
	afile.close();
	return 0;
}


void display(){											//Function to display registers and its values 
	for(int i=0;i<32;i++){
		cout<<reg_file[i].alt_name<<":"<<reg_file[i].value<<endl;
	}
	if (arr[0].addvalue==0)
	{
		cout<< "-----------No memory is allocated for anything------"<<endl;
	}
	else{
	cout<<"----------The CURRENT state of Memory is----------"<<endl;
	for (int i = startaddress; i <variableaddress; i=i+4){
		cout<<"address--"<<i<<"        value stored--"<<a1[(i-startaddress)/4]<<endl;
	}
	}


}

void getabc(){											//GEt register indices a,b,c for add, sub etc...
	for (int i = 0; i < 32;i++)
	{
		if(x==(reg_file[i].alt_name+d)){
			a=i;
			afile>>x;
			for (int i = 0; i < 32;i++){
				if(x==((reg_file[i].alt_name+d))){
					b=i;
					afile>>x;
					for (int i = 0; i < 32;i++){
							if(x==(reg_file[i].alt_name)){
							c=i;
							break;
							}
						else if(i==31){
								cout<<"SYNTAX Error"<<endl;
								exit (0);
								break;
						}
						}
					break;
					}

		else if(i==31){

			cout<<"SYNTAX Error"<<endl;
			exit (0);
			break;
		}
	}
	break;
		}
	else if(i==31){
			cout<<"SYNTAX Error"<<endl;
			exit (0);
			break;
		}
	}
}

void getab(){										//GEt register indices a,b for addi, andi etc...
	for (int i = 0; i < 32;i++)
	{
		//cout <<"is \n";
		

		if(x==(reg_file[i].alt_name+d)){
			a=i;
			afile>>x;
			
			//cout<<a<<"a is \n";
			for (int i = 0; i < 32;i++){
				if(x==(reg_file[i].alt_name+d)){
					b=i;
					//cout<<b<<"b is \n";
					break;
				}
			else if(i==31){
				cout<<"SYNTAX Error"<<endl;
				exit (0);
				break;
		}
	}
	break;
		}
	else if(i==31){
			cout<<"SYNTAX Error"<<endl;
			exit (0);
			break;
		}
	}
}
void geta(){													//GEt register index 'a' for add, sub etc...
	for (int i = 0; i < 32;i++)
	{
		if(x==(reg_file[i].alt_name+d)){
			a=i;
			break;
		}
	else if(i==31){
			cout<<"SYNTAX Error"<<endl;
			exit (0);
			break;
		}
	}
}
void getao(){													//Get register index and offset for lw, sw
	geta();
	offset=0;
	num="";
	reg="";
	afile>>x;
	ls=x;
	int i=0;
	while(ls[i]!='(' && i<sizeof(ls) ){
		num=num+ls[i];
		i++;
	}
	i=i+1;
	offset=atoi( num.c_str() );
	if((offset%4)!=0){
		cout<<"offset ERROR"<<endl;
		exit(0);
	}
	while(ls[i]!=')' && i<sizeof(ls)){	
			reg=reg+ls[i];
			i++;
	}
	for (int i = 0; i < 32;i++)
	{
		
		if(reg==(reg_file[i].alt_name)){
			b=i;
			break;
		}
	else if(i==31){
			cout<<"SYNTAX Error"<<endl;
			exit (0);
			break;
		}
	}


}
void jump(){												//Function for identifying label and jumping
	afile>>x;
	afile.seekg(0);
	str=x;
	
	afile>>x;
	while (x!=".text"){
		afile>>x;
	
	}
	
	while(str+':'!=x){
	    		afile>>x;
	    		if(x=="halt"){
	    			cout<<"SYNTAX Error JUMPING  LABEL IS NOT FOUND"<<endl;
					exit (0);
					break;
				}
	    	}
	return;
}
void init_reg_file()
{
																	// Initialises the register file. 
	

	strcpy(reg_file[0].alt_name,"$zero");
	strcpy(reg_file[1].alt_name,"$at");
	strcpy(reg_file[2].alt_name,"$v0");
	strcpy(reg_file[3].alt_name,"$v1");
	strcpy(reg_file[4].alt_name,"$a0");
	strcpy(reg_file[5].alt_name,"$a1");
	strcpy(reg_file[6].alt_name,"$a2");
	strcpy(reg_file[7].alt_name,"$a3");
	strcpy(reg_file[8].alt_name,"$t0");
	strcpy(reg_file[9].alt_name,"$t1");
	strcpy(reg_file[10].alt_name,"$t2");
	strcpy(reg_file[11].alt_name,"$t3");
	strcpy(reg_file[12].alt_name,"$t4");
	strcpy(reg_file[13].alt_name,"$t5");
	strcpy(reg_file[14].alt_name,"$t6");
	strcpy(reg_file[15].alt_name,"$t7");
	strcpy(reg_file[16].alt_name,"$s0");
	strcpy(reg_file[17].alt_name,"$s1");
	strcpy(reg_file[18].alt_name,"$s2");
	strcpy(reg_file[19].alt_name,"$s3");
	strcpy(reg_file[20].alt_name,"$s4");
	strcpy(reg_file[21].alt_name,"$s5");
	strcpy(reg_file[22].alt_name,"$s6");
	strcpy(reg_file[23].alt_name,"$s7");
	strcpy(reg_file[24].alt_name,"$t8");
	strcpy(reg_file[25].alt_name,"$t9");
	strcpy(reg_file[26].alt_name,"$k0");
	strcpy(reg_file[27].alt_name,"$k1");
	strcpy(reg_file[28].alt_name,"$gp");
	strcpy(reg_file[29].alt_name,"$sp");
	strcpy(reg_file[30].alt_name,"$fp");
	strcpy(reg_file[31].alt_name,"$ra");
	
	return;
}
