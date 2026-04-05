#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

int open_spaces;

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

void PrintMap2(char *map, int width, int height, int x, int y){
    int mapPos = GetMapCoords(x, y, width);

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
            
            printf("\033[37m");
    
            if (GetMapCoords(j, i, width) == mapPos){
                printf("\033[42m");  // Green background for highlighted cell
            }
            
            printf("%c", map[width * i + j]);
            
            printf("\033[0m");       // Reset all formatting
            printf("|");
            printf("\e[37m");
        }
        printf("\n");
        PrintIndent((int)log10((double)height) + 2);
        for (int k = 0; k < width * 2 + 1; k++)
            printf("-");
        printf("\n");
    }
}

// int* PlaceBombs(int width, int height, int size){
//     int *bombs = malloc(size * sizeof(int));
//     int rand_x;
//     int rand_y;
//     int place;
//     srand(time(NULL));
//     for (int i = 0; i < size; i++){
//         do
//         {
//             rand_y = rand() % height;
//             rand_x = rand() % width;
//             place = rand_y * width + rand_x;
//         } while (Contains(bombs, place, size));
//         bombs[i] = place;
//     }
//     return bombs;
// }

int* PlaceBombs(int width, int height, int size){
    int *bombs = malloc(size * sizeof(int));
    int spaces = width * height;
    int *possible_places = malloc(spaces * sizeof(int));
    for (int i = 0; i < spaces; i++)
        possible_places[i] = i;

    for (int i = 0; i < size; i++){
        int random = rand() % (spaces - i);
        bombs[i] = possible_places[random];
        int temp = possible_places[spaces - 1 - i];
        possible_places[spaces - 1 - i] = possible_places[random];
        possible_places[random] = temp;
    }
    free(possible_places);
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

void AskForFlag(int *flag){
    char mango;
    do{
        printf("Flag or bomb (f or b): ");
        while ((mango = getchar()) != '\n' && mango != EOF);
        mango = getchar();
    } while (mango != 'f' && mango != 'b');
    *flag = (mango == 'f');
}

void RevealBombs(char *map, int *bombs, int size_bombs){
    for (int i = 0; i < size_bombs; i++){
        map[bombs[i]] = 'B';
    }
}

void FloodZeros(char *map, int *bombs, int size_bomb, int x, int y, int width, int height, int *possible_coords){
    if (x < 0 || y < 0) return;
    if (width <= x || height <= y) return;
    int coord = GetMapCoords(x, y, width);
    if (Contains(bombs, coord, size_bomb)){
        RevealBombs(map, bombs, size_bomb);
        return;
    }
    int mango = GetBombAmountsAtCoord(bombs, x, y, width, size_bomb);
    if (possible_coords[coord] != -1) return;
    if (mango != 0){
        SetMapAtCoord(map, x, y, width, mango + 48);
        possible_coords[coord] = 0;
        open_spaces--;
        return;
    }
    
    map[coord] = ' ';
    open_spaces--;
    possible_coords[coord] = 0;

    FloodZeros(map, bombs, size_bomb, x + 1, y    , width, height, possible_coords);
    FloodZeros(map, bombs, size_bomb, x - 1, y    , width, height, possible_coords);
    FloodZeros(map, bombs, size_bomb, x    , y + 1, width, height, possible_coords);
    FloodZeros(map, bombs, size_bomb, x    , y - 1, width, height, possible_coords);
}

void GetInput(int *x, int *y, int *flag){
    char ch;

    if(!kbhit()){

        ch = getch();

        // if (ch == )

        // printf("The character: %d\n", ch);

        if(ch == -32)
        {
            ch = getch();

            if(ch==80) // down
            {
                *y = 1;
            }

            else if(ch==72) // up
            {
                *y = -1;
            }

            else if(ch==75) // left
            {
                *x = -1;
            }   
                
            
            else if(ch==77) // right
            {
                *x = 1;
            }    
        }

        if (ch == 3)
            exit(0);

        if (ch == 102)
            *flag = 1;

        else if (ch == 98)
            *flag = 0;

        
    }
}

void Clamp(int *value, int min, int max){
    if (*value < min)
        *value = min;
    else if (max < *value)
        *value = max;
}

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void InputLoop(char *map, int *x, int *y, int width, int height, int *flag){
    int add_x = 0;
    int add_y = 0;
    while (1){
        GetInput(&add_x, &add_y, flag);
        *x += add_x;
        *y += add_y;

        Clamp(x, 0, width - 1);
        Clamp(y, 0, height - 1);

        if (*flag != -1)
            return;

        clear();
        PrintMap2(map, width, height, *x, *y);
        add_x = 0;
        add_y = 0;
    }
}

int main(){
    printf("Hello World\n");
    int width;
    int height;
    int x = 0;
    int y = 0;
    int bomb_count = 2;
    printf("How many bombs: ");
    scanf("%d", &bomb_count);
    int mango;
    int flag = -1;

    srand(time(NULL));
    
    GetSize(&width, &height);
    int size = width * height;
    open_spaces = size - bomb_count;
    int *possible_coords = malloc(size * sizeof(int));
    memset(possible_coords, -1, size * sizeof(int));

    char* map = CreateMap(width, height);
    int* bombs = PlaceBombs(width, height, bomb_count);
    PrintMap(map, width, height);

    while (1){
        InputLoop(map, &x, &y, width, height, &flag);
        mango = GetBombAmountsAtCoord(bombs, x, y, width, bomb_count) + 48;
        
        if (flag == 1){
            
            if (map[GetMapCoords(x, y, width)] == 'F')
                SetMapAtCoord(map, x, y, width, 'O');
            else if (map[GetMapCoords(x, y, width)] == 'O')
                SetMapAtCoord(map, x, y, width, 'F');
        } 
        else {
            FloodZeros(map, bombs, bomb_count, x, y, width, height, possible_coords);
        } 
        if (mango + 1 == 67 && flag == 0){
            clear();
            printf("You lose gang!\n");
            PrintMap(map, width, height);
            break;
        }
        else if (open_spaces <= 0){
            clear();
            printf("You win gang!\n");
            PrintMap(map, width, height);
            break;
        }

        flag = -1;

        clear();
        PrintMap2(map, width, height, x, y);
        // printf("Remaining: %d\n", open_spaces);
    }
    
    free(possible_coords);
    free(bombs);
    free(map);

    return 0;
}