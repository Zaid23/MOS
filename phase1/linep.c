/******************************************************/
/* File Name:- linep.c                                 */
/* Licence:- GNU GPL v3                               */
/* Project Name:-Multiprogramming Operating System    */
/* ****************************************************/

#include"linep.h"

/* Allocate memory for lineprinter */
static LINEPRINTER* linep_alloc(LINEPRINTER *linep){
  if(linep==NULL){
    linep=(LINEPRINTER*)malloc(sizeof(LINEPRINTER));
  }
  if(linep==NULL){
    fprintf(stderr,"Memory not allocated");
    exit(8);
  }
  return linep;
}

/* Set all memory locations to null for lineprinter */
static LINEPRINTER* linep_set(LINEPRINTER *linep){
  memset((void*)(*linep).OPLINE,'\0',sizeof(char)*42);
  return linep;
}

/* Calling innitialize function for linep */
LINEPRINTER* linep_init(LINEPRINTER *linep){
  linep= linep_alloc(linep);
  linep=linep_set(linep);
  return linep;
}

/* Open file for putting output  */
FILE* linep_open(FILE *FOUT,char *filename){
  FOUT=O_WRIT(filename);
  if(FOUT==NULL){
    fprintf(stderr,"Cant open output file");
    exit(8);
  }
  return FOUT;
}

/* Close output file */
void linep_close(FILE *FOUT){
  if(FOUT){
      CLOSE(FOUT);
    }
 }


void linep_print(FILE *FOUT,LINEPRINTER *linep){
  int i,found=0;
  if(FOUT && linep->OPFLAG)
    {
      fseek(FOUT,0,SEEK_END);
      for(i=0;i<strlen(linep->OPLINE)+1;i++)
        if(linep->OPLINE[i]=='\n')
          {
            found=1;
            break;
          }
      if(!found)
        linep->OPLINE[strlen(linep->OPLINE)]='\n';
      fputs(linep->OPLINE,FOUT);
    }
  linep->OPFLAG=0;
}

void linep_jobend(FILE *FOUT){
  if(FOUT)
    {
      fseek(FOUT,0,SEEK_END);
      fprintf(FOUT,"\n\n");
    }
}
