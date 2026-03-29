#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void PrintIndent(int size){
    // printf("The size given: %d\n", size);
    char *indent = malloc(size + 1);
    memset(indent, (int)' ', size);
    indent[size] = 0;
    printf("%s", indent);
    free(indent);
}

char* CreateMap(int width, int height){
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    int size = width * height;
    char *map = malloc(size);
    memset(map, (int)'O', size);
    return map;
}

void PrintMap(char *map, int width, int height){
    PrintIndent((int)log10((double)height) + 2);
    printf("|");
    for (int i = 0; i < width; i++)
        printf("%c|", i + 65);
    printf("\n");
    PrintIndent((int)log10((double)height) + 2);
    for (int k = 0; k < width * 2 + 1; k++)
    printf("-");
    printf("\n");
    for (int i = 0; i < height; i++){
        printf("%d", i + 1);
        PrintIndent((int)log10((double)height) - (int)log10((double)i + 1) + 1);
        printf("|");
        for (int j = 0; j < width; j++){
            printf("%c|", map[width * i + j]);
        }
        printf("\n");
        PrintIndent((int)log10((double)height) + 2);
        for (int k = 0; k < width * 2 + 1; k++)
            printf("-");
        printf("\n");
    }
}

void GetSize(int *width, int *height){
    printf("Enter width: ");
    scanf("%d", width);
    printf("Enter height: ");
    scanf("%d", height);
}

void GetCoords(int *x, int *y, int width, int height){
    do
    {
        printf("Enter X coord: ");
        char mango;
        while ((mango = getchar()) != '\n' && mango != EOF);
        mango = getchar();
        *x = (int)mango - 65;
        if (*x < 0 || width <= *x)
            printf("You went out of bounds!\n");
    } while (*x < 0 || width <= *x);
    
    do
    {
        printf("Enter Y coord: ");
        scanf("%d", y);
        (*y)--;
        if (*y < 0 || height <= *y)
            printf("You went out of bounds!\n");
    } while (*y < 0 || height <= *y);
}

int Contains(int *container, int element, int size){
    for (int i = 0; i < size; i++){
        if (container[i] == element) return 1;
    }
    return 0;
}

void SetMapAtCoord(char* map, int x, int y, int width, char c){
    map[y * width + x] = c;
}

int GetMapCoords(int x, int y, int width){
    return y * width + x;
}

int* PlaceBombs(int width, int height, int size){
    int *bombs = malloc(size * sizeof(int));
    int rand_x;
    int rand_y;
    int place;
    for (int i = 0; i < size; i++){
        do
        {
            rand_y = rand() % height;
            rand_x = rand() % width;
            place = rand_y * width + rand_x;
        } while (Contains(bombs, place, size));
        bombs[i] = place;
    }
    return bombs;
}

int GetBombAmountsAtCoord(int* bombs, int x, int y, int width, int size){
    if (Contains(bombs, GetMapCoords(x, y, width), size)) return 18;
    int bombs_amount = 0;

    for (int _x = 0; _x < 3; _x++){
        if (Contains(bombs, GetMapCoords(x - 1 + _x, y - 1, width), size)) bombs_amount++;
    }
    if (Contains(bombs, GetMapCoords(x - 1, y, width), size)) bombs_amount++;
    if (Contains(bombs, GetMapCoords(x + 1, y, width), size)) bombs_amount++;

    for (int _x = 0; _x < 3; _x++){
        if (Contains(bombs, GetMapCoords(x - 1 + _x, y + 1, width), size)) bombs_amount++;
    }

    return bombs_amount;
}

void FloodZeros(char *map, int width, int height, int *possible_coords, int size){
    // if ( )
}

int main(){
    printf("Hello World\n");
    int width;
    int height;
    int x;
    int y;
    int bomb_count = 5;
    int mango;
    
    GetSize(&width, &height);
    int size = width * height;
    int *possible_coords = malloc(size);
    memset(possible_coords, -1, size);

    char* map = CreateMap(width, height);
    int* bombs = PlaceBombs(width, height, bomb_count);
    PrintMap(map, width, height);

    while (1 == 1){
        GetCoords(&x, &y, width, height);
        mango = GetBombAmountsAtCoord(bombs, x, y, width, bomb_count) + 48;
        SetMapAtCoord(map, x, y, width, mango);
        if (mango + 1 == 67)
            break;
        PrintMap(map, width, height);
    }
    
    free(possible_coords);
    free(bombs);
    free(map);

    return 0;
}