//¡°Copyright ? 2019-present Lenovo
//Licensed under BSD-3, see COPYING.BSD file for details.¡±

/**
 * This program is a test utility for update cpld image via accessing JTAG.
 * Actions:
 *   GET_FREQ:  get frequency
 *   UPDATE_CPLD: update image
     
 */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "fpga.h"

//#include <linux/jtag.h>
//#include <uapi/linux/jtag.h>

#define MAX_EXARGV_CNT 6
#define MAX_EXARGV_STR_LEN 20
#define MEMBUFFSIZE 512*1024

typedef enum {
	GET_FREQ,
	UPDATE_CPLD,
	NO_FUNCTION
}AspeedJTAGactions;

char *image_file = NULL;

AspeedJTAGactions action = NO_FUNCTION;


static void ShowUsuage ( void )
{
   printf ("obmc-fpga-test  - Copyright (c) 2019 Lenovo.\n");	
   printf( "Usage : obmc-fpga-test <command> \n" );
   printf("\t<command>        can be one of the following:\n");
   printf( "\t--get-jtag-freq: \tGet aspeed jtag frequency\n" );
   printf( "\t--update-cpld: \tupdate cpld image\n" );
   printf( "\n" );

}
static int process_arguments( int argc, char **argv )
{
	int i = 1;
	int ret = 0;
	
	while( i < argc ){  	
		/* Check for a command */
		if( strcmp( argv[ i ], "--get-jtag-freq" ) == 0 )  
		{
			action = GET_FREQ;
		}
		else if (strcmp( argv[ i ], "--update-cpld" ) == 0)
		{
			action = UPDATE_CPLD;
			i ++;
			if(i>=argc){
				ret = -1;
			}
			image_file = argv[i];
		}
		i++;
	}
	return ret;
}
int main(int argc , char* argv [])
{
	int res;
	int fd = -1;
	unsigned int jtag_freq;
	if ( argc < 2 )
	{
		ShowUsuage(); 
		return 0;	
	}
	if ( -1 == process_arguments( argc , argv ))
	{
		ShowUsuage(); 
		return 0;	
	}
	switch (action){
	    case GET_FREQ:
			res = get_freq (&jtag_freq);
			if  ( -1 == res )
			{
				printf ( "Get aspeed freq  Failed \n"); 
				return -1;
			}
			printf ( "freq is %08x\n", (unsigned int)jtag_freq );
			break;
		case UPDATE_CPLD:
		    printf("entering update ...\n");
		    FILE *hFile = NULL;
			struct stat sbuf;
            int iTotalSize = 0;
			int iTransCount = 0;
			unsigned char *tempbuffer = NULL;
		    int exArgv_cnt = 0;
			char **exArgv=NULL;					  
			char Str[MAX_EXARGV_CNT][MAX_EXARGV_STR_LEN]={{0,},};
			int i;
			
			//Open file and get length of file.
			if (image_file != NULL && (access(image_file, 0) == 0)) {
				if (stat(image_file, &sbuf) == 0){
				    iTotalSize = sbuf.st_size;
				}
				hFile = fopen(image_file, "rb");
			}					
			else {
				printf ( "Invalid image file\n");
				return -1;
			}
			
			if (hFile == NULL) {
				printf ( "Open image Failed \n"); 
				return -1;
			}
			tempbuffer = (unsigned char *) malloc(MEMBUFFSIZE);
			memset(tempbuffer, 0xff, MEMBUFFSIZE);
			iTransCount = fread(tempbuffer, 1, MEMBUFFSIZE, hFile);
			exArgv = (char **) malloc((size_t) (MAX_EXARGV_CNT* sizeof(char *)));
			snprintf( Str[0], MAX_EXARGV_STR_LEN,"-@%08x ",(unsigned int)tempbuffer);
			snprintf( Str[1], MAX_EXARGV_STR_LEN,"-L%ld ",(long int)iTransCount);
			snprintf( Str[2], MAX_EXARGV_STR_LEN,"-aPROGRAM");
			for(i=0;i<MAX_EXARGV_CNT;i++) {
					if(Str[i][0] ==0) break;
					exArgv[exArgv_cnt++]=Str[i];
				}
		    res = update_cpld_start(exArgv_cnt, exArgv);
			if ( 0 > res ) {
				printf ("update fail\n");
				free(tempbuffer);
				fclose(hFile);
				return res;
				}else{
					printf("update done!\n");
				}
			break;
		
	    default:
			printf  ("Invalid JTAG Function Call\n");
			break;
	}
    return res;
}
