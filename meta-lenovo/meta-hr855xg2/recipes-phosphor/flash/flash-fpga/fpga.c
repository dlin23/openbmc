//¡°Copyright ? 2019-present Lenovo
//Licensed under BSD-3, see COPYING.BSD file for details.¡±

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "fpga.h"
//#include <linux/jtag.h>
//#include <uapi/linux/jtag.h>

#define JTAG_DEVICE_PATH "/dev/jtag0"

int get_freq (unsigned int *value)
{
  int fd = -1;
  int res = -1;
  fd = open(JTAG_DEVICE_PATH,O_RDWR | O_SYNC);
  if(fd == -1){
    printf("open aspeed jtag file fail\n");
	return fd;
  }
  else{
	res = ioctl(fd,JTAG_GIOCFREQ,value);
	if(res == -1){
	   printf("call get frequency in driver fail\n");
	}
  }
  
  close(fd);
  
  return res;
  
}
int jtag_update_cpld(jtag_ioaccess_data *argp,int command)
{
	int fd = -1;
    int res = -1;
    fd = open(JTAG_DEVICE_PATH,O_RDWR);
    if(fd == -1){
        printf("open aspeed jtag file fail\n");
	    return fd;
    }
    else{
	    res = ioctl(fd,JTAG_UPDATE_CPLD,argp);
	    if(res == -1){
	        printf("call update cpld via jtag in driver fail\n");
	    }else{
			res = (int)argp->data;  //size of cpld image file
		}
    }
  
    close(fd);
  
    return res;
}

int update_cpld_start(int argvcnt,char **cargv)
{

	char array_buf[256]={0,};                                                                                                                              
	int res;                                                                                                                                            
	int retry_cnt = 0;                                                                                                                                     
	int arg=0, argc=0;                                                                                                                                     
	jtag_ioaccess_data jtag_arg_bak,jtag_arg;                                                                                                              
    char *argv[8]={ &array_buf[0  ],	&array_buf[32 ],                                                                                                   
                	&array_buf[64 ],	&array_buf[96 ],                                                                                                   
                	&array_buf[128],	&array_buf[160],                                                                                                   
                	&array_buf[192],	&array_buf[224]                                                                                                    
                   };                                                                                                                                     
	memset(&jtag_arg, 0x00, sizeof(jtag_ioaccess_data));                                                                                                   
    snprintf(argv[argc++],32,"-");                                                                                                                        
    snprintf(argv[argc++],32,"-dDO_REAL_TIME_ISP=1");
	                                                                                                   
            
    /* argvcnt = 3 cargv[0][0] = '-' cargv[0][1] = '@'	cargv[0][2]= image file address in memory
       cargv[1][2] = image file size 
	   argv[0] = array_buf[0-31] = "-"
       argv[1] = array_buf[32-63] = "-dDO_REAL_TIME_ISP=1"
       argv[2] = array_buf[64-95] = "-aPROGRAM"	   
	   argv[3] = array_buf[96-127] = "-@address"
	   argv[4] = array_buf[128-159] = "-Limagesize  */

	for (arg = 0; arg < argvcnt; arg++){                                                                                                                    
		if (cargv[arg][0] == '-'){                                                                                                                        
			switch(cargv[arg][1]){                                                                                                                        
				case '@':				/* get memory buffer address */                                                                                    
					if (sscanf(&cargv[arg][2], "%08x", (unsigned int *)&jtag_arg.input_buffer_base) != 1){
                    	res = -1;// this should be replace in kernel.
					}
                break;                                                                                                                                 
				case 'l':				/* get memory buffer size */                                                                                       
				case 'L':                                                                                                                                  
					if (sscanf(&cargv[arg][2], "%ld", &jtag_arg.data) != 1){
						res = -1;   
                    }						
				break;                                                                                                                                 
                default:                                                                                                                                  
                    snprintf(argv[argc],32,"%s",cargv[arg]);                                                                                             
                    argc++;   //arg = 2 argc = 3  cargv[2] = "-aPROGRAM"                                                                                                                         
               break;                                                                                                                                
			}			                                                                                                                                   
		}                                                                                                                                                  
	}                                                                                                                                                      
	                                                                                                                                                       
	//Set argument count and argument string array.                                                                                                        
	jtag_arg.value = argc;                                                                                                                                 
	jtag_arg.address = (unsigned long)array_buf;	                                                                                                       
	//----------------------------------------------------------------                                                                                     
	// Re-programmed when Exit code = 11 : Device verify failure.                                                                                          
	jtag_arg_bak =jtag_arg;                                                                                                                                
	do{                                                                                                                                                    
		if(retry_cnt){                                                                                                                                     
			jtag_arg=jtag_arg_bak;                                                                                                                         
			printf("res =%d,retry_cnt=%d\n",res,retry_cnt);                                                                                           
			sleep(3);                                                                                                                                      
		}                                                                                                                                                  
		res = jtag_update_cpld(&jtag_arg, JTAG_UPDATE_CPLD);                                                                                                  
	}while((retry_cnt++ < UPDATE_RETRY_MAX) && (res == 11));                                                                                      
	                                                                                                                                                       
	return res;   
}

