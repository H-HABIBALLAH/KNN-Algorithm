#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char *nomCouleur;
} couleur;

typedef struct
{
    float x, y;
} pointSup;

typedef struct rect
{
    int id;
    couleur c;
    pointSup p;
    struct rect *next;
} rectangle;

typedef struct 
{
    int id;
    float d;
}distance;

void triTab(distance *d,int n)
{
    int i,j,temp;
    for(i=0;i<n;i++)
    {
        for(j=i;j<n;j++)
        {
            if(d[i].d>d[j].d)
            {
                temp =d[i].d;
                d[i].d=d[j].d;
                d[j].d=temp;
                temp =d[i].id;
                d[i].id=d[j].id;
                d[j].id=temp;
            }
        }
    }
}

char *enterText()
{
    char text[100];
    gets(text);
    char *realText;
    realText = (char *)malloc((strlen(text) + 1) * sizeof(char));
    strcpy(realText, text);
    realText[strlen(text) + 1] = '\0';
    return realText;
}

rectangle *createRectangle()
{
    rectangle *r;
    getchar();
    r = (rectangle *)malloc(sizeof(rectangle));
    printf("Donner la couleur : ");
    r->c.nomCouleur = enterText();
    printf("Donnez x : ");
    scanf("%f", &r->p.x);
    printf("Donnez y : ");
    scanf("%f", &r->p.y);
    r->next = NULL;
    return r;
}

void addRectangle(rectangle **tete, rectangle *r)
{
    rectangle *courant;
    if (*tete == NULL)
    {
        *tete = r;
        return;
    }
    courant = *tete;
    while (courant->next != NULL)
        courant = courant->next;
    courant->next = r;
}

void displayRectangle(rectangle *r)
{
    printf("la couleur est : %s\n", r->c.nomCouleur);
    printf("x = %.2f\n", r->p.x);
    printf("y = %.2f\n", r->p.y);
}

void displayListe(rectangle *tete)
{
    int i = 1;
    rectangle *courant;
    if (tete == NULL)
    {
        printf("La liste est vide !!\n");
        return;
    }
    courant = tete;
    while (courant != NULL)
    {
        printf("rectangle %d : \n", i++);
        displayRectangle(courant);
        courant = courant->next;
    }
}

distance *claculerDistance(rectangle *tete, rectangle *r, int nbr)
{
    distance *d;
    int i = 0;
    d = (distance *)malloc(nbr * sizeof(distance));
    rectangle *courant = tete;
    while (courant != NULL)
    {
        d[i].d = sqrt(pow(courant->p.x - r->p.x, 2) + pow(courant->p.y - r->p.y, 2));
        d[i].id=i;
        courant = courant->next;
        i++;
    }

    return d;
}

void displayDistance(rectangle *tete,rectangle *rect, distance *d, int n)
{
    rectangle *courant = tete;
    printf("La distance du rectancle du point superieur (%.1f , %.1f) par rappor au rectangle du point superieur : \n", rect->p.x, rect->p.y);
    for (int i = 0; i < n; i++)
    {
        printf("(%.1f , %.1f) est : ",courant->p.x, courant->p.y);
        printf("%.2f\n", d[i].d);
        courant = courant->next;
    }
}

rectangle *createRectangleDistance()
{
    rectangle *r;
    getchar();
    r = (rectangle *)malloc(sizeof(rectangle));
    r->c.nomCouleur = "noir";
    printf("Donnez x : ");
    scanf("%f", &r->p.x);
    printf("Donnez y : ");
    scanf("%f", &r->p.y);
    r->next = NULL;
    return r;
}

int main()
{
    rectangle *tete, *r,*courant;
    int nbr;
    tete = NULL;
    printf("donner le nombre des rectangles : ");
    scanf("%d", &nbr);
    for (int i = 0; i < nbr; i++)
    {
        r = createRectangle();
        r->id=i;
        addRectangle(&tete, r);
    }
    displayListe(tete);
    printf("claculer les distances : \n");
    rectangle *rect = createRectangleDistance();
    distance *d = claculerDistance(tete, rect, nbr);
    displayDistance(tete, rect, d, nbr);
    distance *temp=(distance *)malloc(nbr * sizeof(distance));
    for (int i = 0; i < nbr; i++)
    {
        temp[i].d=d[i].d;
        temp[i].id=d[i].id;
    }
    triTab(temp,nbr);
    int k,nr=0,nb=0;
    printf("Donnez k : ");scanf("%d",&k);
    printf("les %d rectangles les plus proches ont les points superieurs suivant : \n",k);
    for (int i = 0; i < k; i++)
    {
        courant=tete;
        while (1)
        {
            if(temp[i].id==courant->id)break;
            courant=courant->next;
        }
        if(strcmp(courant->c.nomCouleur,"bleu")==0)nb++;
        if(strcmp(courant->c.nomCouleur,"rouge")==0)nr++;
        printf("(%.1f , %.1f) - ",courant->p.x,courant->p.y);
    }
    printf("\n Parmi ces rectangles il ya %d rouge et %d bleu ",nr,nb);
    return 0;
}