#ifndef PARAM_H
#define PARAM_H

#ifdef PARAM_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

typedef struct parameters {
        float alpha;
        float beta;
        float density;
        float velocity;
} parameters;

EXTERN int  param_parse(int argc, char *argv[],parameters **param);
EXTERN int  param_init(parameters **param);
EXTERN void param_free(parameters* p);

#undef PARAM_IMPORT
#undef EXTERN


#endif
