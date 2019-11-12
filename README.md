# Busca aproximada do melhor cenário sem interferência dos canais rede WIFI na frequência de 2,4 GHz.

> Projeto implementado como trabalho para a materia de Grafos do curso ciencia da computação da Unisul - 2019

### PROBLEMA
Uma determinada empresa pretende distribuir pontos de acesso wifi em uma cidade, para ter uma melhor qualidade de serviço é de necessidade que esses pontos de acesso não tenham interferência entre si.
 - O problema ignora todas as possíveis interferências ocasionadas por dispositivos externos, como por exemplo: Roteadores de de casa.

### MODELAGEM
 - Cores: Canal utilizado
 - Vetores: Pontos de acesso WIFI
 - Arestas: intersecção dos sinais

### DEPEDENCIAS
 - Graphviz ( http://www.graphviz.org/ )
```shell
$ sudo apt install graphviz
```

### COMO UTILIZAR
```shell
$ ./exec.sh
```