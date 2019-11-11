#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C"{
#endif
    
    typedef struct graf *GRAF;

    GRAF newGrafo();
    void desenho(GRAF grafo);

#ifdef __cplusplus
}
#endif

#endif  // APP_H