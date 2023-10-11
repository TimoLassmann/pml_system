#include "tld.h"

#include <getopt.h>

#define OPT_ALPHA 0
#define OPT_BETA 1
#define OPT_DENSITY 2

#define MARGIN 22

#define PARAM_IMPORT
#include "param.h"


static int print_help(char *argv[]);

int param_parse(int argc, char *argv[],parameters **param)
{
        parameters* p = NULL;
        int c;
        int help = 0;

        RUN(param_init(&p));

        while (1){
                static struct option long_options[] ={
                        {"alpha", required_argument,0,'a'},
                        {"beta", required_argument,0,'b'},
                        {"density", required_argument,0,'d'},
                        {"help", no_argument,0,'h'},
                        {0, 0, 0, 0}
                };

                int option_index = 0;

                c = getopt_long_only (argc, argv,"a:b:d:h",long_options, &option_index);

                /* Detect the end of the options. */
                if (c == -1){
                        break;
                }
                switch(c) {
                case 'a':
                        p->alpha = (float) atof(optarg);
                        break;
                case 'b':
                        p->beta = (float) atof(optarg);
                        break;
                case 'd':
                        p->density = (float) atof(optarg);
                        break;

                case 'h':
                        help = 1;
                        break;
                case '?':
                        param_free(p);
                        return FAIL;
                        break;
                default:
                        abort ();
                }
        }

        if(help || argc < 2 ){
                print_help(argv);
        }

        *param = p;
        return OK;
ERROR:
        return FAIL;
}

int print_help(char * argv[])
{
        const char usage[] = " ";
        char* basename = NULL;

        RUN(tld_get_filename(argv[0],  &basename));

        fprintf(stdout,"\nUsage: %s %s\n\n",basename ,usage);
        fprintf(stdout,"Options:\n\n");

        fprintf(stdout,"%*s%-*s: %s %s\n",3,"",MARGIN-3,"-a/--alpha","Alpha parameter." ,"[180]"  );
        fprintf(stdout,"%*s%-*s: %s %s\n",3,"",MARGIN-3,"-b/--beta","Beta parameter." ,"[17]"  );
        fprintf(stdout,"%*s%-*s: %s %s\n",3,"",MARGIN-3,"-d/--density","Inital particle density." ,"[0.07]"  );

        fprintf(stdout,"\n\n");
        /* fprintf(stdout,"%*s%-*s: %s %s\n",3,"",MESSAGE_MARGIN-3,"--reformat","Reformat existing alignment." ,"[NA]"  ); */

        /* fprintf(stdout,"\nExamples:\n\n"); */

        /* fprintf(stdout,"Passing sequences via stdin:\n\n   cat input.fa | kalign -f fasta > out.afa\n\n"); */
        /* fprintf(stdout,"Combining multiple input files:\n\n   kalign seqsA.fa seqsB.fa seqsC.fa -f fasta > combined.afa\n\n"); */

        if(basename){
                MFREE(basename);
        }
        return OK;
ERROR:
        if(basename){
                MFREE(basename);
        }
        return FAIL;
}

int param_init(parameters **param)
{

        parameters* p = NULL;
        MMALLOC(p, sizeof(parameters));
        p->alpha = 180.0f;
        p->beta = 17.0f;
        p->density = 0.06f;
        p->velocity = 0.67f;
        *param =p;
        return OK;
ERROR:
        param_free(p);
        return FAIL;
}

void param_free(parameters *p)
{
        if(p){
                MFREE(p);
        }
}

#undef MARGIN
