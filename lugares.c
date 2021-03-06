#include <stdio.h>
#include <string.h>
#include "objetos.h"
#include "etc.h"
#include "add.h"


void comandoOlhar(const char* add)
{
    if (add != NULL && strcmp(add, "aqui") == 0)
    {
        printf("Voce esta na/o %s.\n", player->lugar->descricao);
        listaObjetosNoLugar(player->lugar);
    }
    else
    {
        OBJETO* obj = estaVisivel("o que voce quer olhar", add);
        switch (pegarDistancia(player, obj))
        {
        case distAquiInventario:
            printf("Dificil de ver, tente pegar isso primeiro.\n");
            break;
        case distAli:
            printf("Muito longe, tente chegar mais perto.\n");
            break;
        case distNaoAqui:
            printf("Voce nao ve nenhum %s aqui.\n", add);
            break;
        case distObjetoDesconhecido:
            // ja lidado
            break;
        default:
            printf("%s", obj->detalhes);
            listaObjetosNoLugar(obj);
        }
    }
}

static void moverPlayer(OBJETO* passagem)
{
    printf("%s", passagem->textoIda);
    if (passagem->destino != NULL)
    {
        player->lugar = passagem->destino;
        printf("\n");
        comandoOlhar("aqui");
    }
}

void comandoIr(const char* add)
{
    OBJETO *obj = estaVisivel("onde voce quer ir", add);
    switch (pegarDistancia(player, obj))
    {
    case distAli:
        moverPlayer(pegarPassagem(player->lugar, obj));
        break;
    case distNaoAqui:
        printf("Voce nao ve nenhum %s aqui.\n", add);
        break;
    case distObjetoDesconhecido:
        // ja foi lidado pelo pegarInvisvel
        break;
    default:
        moverPlayer(obj);
    }
}