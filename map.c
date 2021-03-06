#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "map.h"

void print_block_energies(int** boostup_blocks, int num_boostup_blocks){
    printf("\n");
    for(int i=0; i<num_boostup_blocks; i++){
        printf("%d) x=%d, y=%d energy left=%d\n", i+1, boostup_blocks[i][0], boostup_blocks[i][1], boostup_blocks[i][2]);
    }
    printf("\n");
    return;
}


void print_energy_line(int line, int j, int energy_left, int num_digit){//kaC nabashe
    if(j%2==0){
        energy_left=energy_left-((line%6)-1)*20-(4*num_digit);
        for(int i=0; i<(5-num_digit); i++){
            if(energy_left<=0){
                printf(" ");
            }
            else{
                printf("E");
                energy_left-=4;
            }
        }
        return;
    }
    else{
        if(line%6==4||line%6==5){
            energy_left=energy_left-(4*num_digit)-((line%6)-4)*20;
        }
        else if(line%6==1||line%6==2){
            energy_left=energy_left-3*20-(4*num_digit)-((line%6)-1)*20;
        }
        else if(line%6==0){
            energy_left=energy_left-2*20-(4*num_digit);
        }
        for(int i=0; i<(5-num_digit); i++){
            if(energy_left<=0){
                printf(" ");
            }
            else{
                printf("E");
                energy_left-=4;
            }
        }
        return;
    }
}




int energy_left(int i, int j, int num_boostup_blocks, int** boostup_blocks){
    int energy_left1;
    for(int k=0; k<num_boostup_blocks; k++){
        if(boostup_blocks[k][0]==j && boostup_blocks[k][1]==i){
            energy_left1=boostup_blocks[k][2];
            return energy_left1;
        }                            
    }
}

void print(int size_game, int**map_bin, int**game_board, int colors[6], int num_boostup_blocks, int** boostup_blocks){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int counter_khat, i;
    for(i=size_game-1, counter_khat=1; counter_khat<=size_game*6; counter_khat++){
        int j;
        for(j=0; j<size_game; j++){
            if(j%2==0){
                if(counter_khat%6==0){
                    SetConsoleTextAttribute(hConsole, 7);
                    printf("      ");
                    continue;
                }
                if(game_board[i][j]==0){
                    if(map_bin[i][j]==ENERGY){
                        int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);                        
                        SetConsoleTextAttribute(hConsole, colors[1]*16);
                        //haminja rang printf ro tanzim mikonim
                        print_energy_line(counter_khat, j, energy_left1, 0);
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");

                    }
                    else if(map_bin[i][j]==MITOSIS){
                        SetConsoleTextAttribute(hConsole, colors[2]*17);
                        printf("MMMMM");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==FORBIDDEN){
                        SetConsoleTextAttribute(hConsole, colors[3]*17);
                        printf("FFFFF");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==NORMAL){
                        SetConsoleTextAttribute(hConsole, colors[4]*17);
                        printf("NNNNN");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }else if(game_board[i][j]>0){//karbar aval
                    if(map_bin[i][j]==ENERGY){
                        int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);
                        if(counter_khat%6==1){
                            SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                            if(game_board[i][j]>9){
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 2);
                            }else{
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 1);
                            }
                        }else{
                            SetConsoleTextAttribute(hConsole, colors[1]*16);
                            print_energy_line(counter_khat, j, energy_left1, 0);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==MITOSIS){
                        if(counter_khat%6==1){
                            SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                            if(game_board[i][j]>9){
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMM");
                                
                            }else{
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMM");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[2]*17);
                            printf("MMMMM");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    // else if(map_bin[i][j]==FORBIDDEN){
                        // printf("i:%d j:%d avatar:%d",i, j, game_board[i][j] );
                    // }
                    else if(map_bin[i][j]==NORMAL){
                        if(counter_khat%6==1){
                            SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                            if(game_board[i][j]>9){
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNN");
                                
                            }else{
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNN");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[4]*17);
                            printf("NNNNN");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }else if(game_board[i][j]<0){//karbar dovom
                    if(map_bin[i][j]==ENERGY){
                        int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);
                        if(counter_khat%6==1){
                            SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                            if((game_board[i][j]*-1)>9){
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 2);
                            }else{
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 1);
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[1]*16);
                            print_energy_line(counter_khat, j, energy_left1, 0);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==MITOSIS){
                        if(counter_khat%6==1){
                            SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                            if((game_board[i][j]*-1)>9){
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMM");
                            }
                            else{
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMM");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[2]*17);
                            printf("MMMMM");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    
                    // else if(map_bin[i][j]==FORBIDDEN){
                    //     printf("what 1");
                    // }

                    else if(map_bin[i][j]==NORMAL){
                        if(counter_khat%6==1){
                            SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                            if((game_board[i][j]*-1)>9){
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNN");
                            }else{
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNN");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[4]*17);
                            printf("NNNNN");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }
            }
            else{
                if((counter_khat%6==3)||(i==size_game-1&&(counter_khat%6>=1&&counter_khat%6<=3))){
                    SetConsoleTextAttribute(hConsole, 7);
                    printf("      ");
                    continue;
                }
                if((counter_khat%6>=4&&counter_khat%6<6)||(counter_khat%6==0)){
                    
                    if(game_board[i][j]==0){
                        if(map_bin[i][j]==ENERGY){
                            int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);  
                            // printf("energy left is%d", energy_left1);                      
                            SetConsoleTextAttribute(hConsole, colors[1]*16);
                            //haminja rang printf ro tanzim mikonim
                            print_energy_line(counter_khat, j, energy_left1, 0);
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");

                        }
                        else if(map_bin[i][j]==MITOSIS){
                            SetConsoleTextAttribute(hConsole, colors[2]*17);
                            printf("MMMMM");
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i][j]==FORBIDDEN){
                            SetConsoleTextAttribute(hConsole, colors[3]*17);
                            printf("FFFFF");
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i][j]==NORMAL){
                            SetConsoleTextAttribute(hConsole, colors[4]*17);
                            printf("NNNNN");
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                    }
                    else if(game_board[i][j]>0){//karbar aval
                        if(map_bin[i][j]==ENERGY){
                            int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);
                            // printf("energy left is%d\n", energy_left1);                      
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                                if(game_board[i][j]>9){
                                    printf("%d", game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                                    print_energy_line(counter_khat, j, energy_left1, 2);
                                }else{
                                    printf("%d", game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                                    print_energy_line(counter_khat, j, energy_left1, 1);
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 0);
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i][j]==MITOSIS){
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                                if(game_board[i][j]>9){
                                    printf("%d", game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                                    printf("MMM");
                                    
                                }else{
                                    printf("%d", game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                                    printf("MMMM");
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMMM");
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i][j]==NORMAL){
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                                if(game_board[i][j]>9){
                                    printf("%d", game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                                    printf("NNN");
                                    
                                }else{
                                    printf("%d", game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                                    printf("NNNN");
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNNN");
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                    }
                    else if(game_board[i][j]<0){//karbar dovom
                        if(map_bin[i][j]==ENERGY){
                            int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                                if((game_board[i][j]*-1)>9){
                                    printf("%d", -1*game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                                    print_energy_line(counter_khat, j, energy_left1, 2);
                                }else{
                                    printf("%d", -1*game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                                    print_energy_line(counter_khat, j, energy_left1, 1);
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 0);
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i][j]==MITOSIS){
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                                if((game_board[i][j]*-1)>9){
                                    printf("%d", -1*game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                                    printf("MMM");
                                }
                                else{
                                    printf("%d", -1*game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                                    printf("MMMM");
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMMM");
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i][j]==NORMAL){
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                                if((game_board[i][j]*-1)>9){
                                    printf("%d", -1*game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                                    printf("NNN");
                                }else{
                                    printf("%d", -1*game_board[i][j]);
                                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                                    printf("NNNN");
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNNN");
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                    }

                }else{//baghimande barabar 1 ya 2 bashe
                    if(game_board[i+1][j]==0){
                        if(map_bin[i+1][j]==ENERGY){
                            int energy_left1=energy_left(i+1, j, num_boostup_blocks, boostup_blocks);
                            SetConsoleTextAttribute(hConsole, colors[1]*16);
                            print_energy_line(counter_khat, j, energy_left1, 0);
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i+1][j]==MITOSIS){
                            SetConsoleTextAttribute(hConsole, colors[2]*17);
                            printf("MMMMM");
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i+1][j]==FORBIDDEN){
                            SetConsoleTextAttribute(hConsole, colors[3]*17);
                            printf("FFFFF");
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i+1][j]==NORMAL){
                            SetConsoleTextAttribute(hConsole, colors[4]*17);
                            printf("NNNNN");
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                    }else if(game_board[i+1][j]>0){//karbar aval
                        if(map_bin[i+1][j]==ENERGY){
                            int energy_left1=energy_left(i+1, j, num_boostup_blocks, boostup_blocks);
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                                if(game_board[i+1][j]>9){
                                    printf("%d", game_board[i+1][j]);
                                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                                    print_energy_line(counter_khat, j, energy_left1, 2);
                                }else{
                                    printf("%d", game_board[i+1][j]);
                                    SetConsoleTextAttribute(hConsole, colors[1]*16);
                                    print_energy_line(counter_khat, j, energy_left1, 1);
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 0);
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i+1][j]==MITOSIS){
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                                if(game_board[i+1][j]>9){
                                    printf("%d", game_board[i+1][j]);
                                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                                    printf("MMM");
                                }else{
                                    printf("%d", game_board[i+1][j]);
                                    SetConsoleTextAttribute(hConsole, colors[2]*17);
                                    printf("MMMM");
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMMM");
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        // else if(map_bin[i+1][j]==FORBIDDEN){
                        //     printf("what1");
                        // }
                        else if(map_bin[i+1][j]==NORMAL){
                            if(counter_khat%6==4){
                                SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                                if(game_board[i+1][j]>9){
                                    printf("%d", game_board[i+1][j]);
                                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                                    printf("NNN");
                                }else{
                                    printf("%d", game_board[i+1][j]);
                                    SetConsoleTextAttribute(hConsole, colors[4]*17);
                                    printf("NNNN");
                                }
                            }
                            else{
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNNN");
                            }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                    }else if(game_board[i+1][j]<0){
                        if(map_bin[i+1][j]==ENERGY){
                            int energy_left1=energy_left(i+1, j, num_boostup_blocks, boostup_blocks);
                            // if(counter_khat%6==4){
                                // SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                                // if((game_board[i+1][j]*-1)>9){
                                //     printf("%d", -1*game_board[i+1][j]);
                                //     SetConsoleTextAttribute(hConsole, colors[1]*16);
                                //     print_energy_line(counter_khat, j, energy_left1, 2);
                                // }else{
                                //     printf("%d", -1*game_board[i+1][j]);
                                //     SetConsoleTextAttribute(hConsole, colors[1]*16);
                                //     print_energy_line(counter_khat, j, energy_left1, 1);
                            //     }
                            // }
                            // else{
                            //     SetConsoleTextAttribute(hConsole, colors[1]*16);
                            //     print_energy_line(counter_khat, j, energy_left1, 0);
                            // }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        else if(map_bin[i+1][j]==MITOSIS){
                            // if(counter_khat%6==4){
                            //     SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                            //     if((game_board[i+1][j]*-1)>9){
                            //         printf("%d", -1*game_board[i+1][j]);
                            //         SetConsoleTextAttribute(hConsole, colors[2]*17);
                            //         printf("MMM");
                            //     }else{
                            //         printf("%d", -1*game_board[i+1][j]);
                            //         SetConsoleTextAttribute(hConsole, colors[2]*17);
                            //         printf("MMMM");
                            //     }
                            // }
                            // else{
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMMM");
                            // }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                        
                        // else if(map_bin[i+1][j]==FORBIDDEN){
                        //     printf("what1");
                        // }

                        else if(map_bin[i+1][j]==NORMAL){
                            // if(counter_khat%6==4){
                            //     SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                            //     if((game_board[i+1][j]*-1)>9){
                            //         printf("%d", -1*game_board[i+1][j]);
                            //         SetConsoleTextAttribute(hConsole, colors[4]*17);
                            //         printf("NNN");
                            //     }else{
                            //         printf("%d", -1*game_board[i+1][j]);
                            //         SetConsoleTextAttribute(hConsole, colors[4]*17);
                            //         printf("NNNN");
                            //     }
                            // }
                            // else{
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNNN");
                            // }
                            SetConsoleTextAttribute(hConsole, 7);
                            printf(" ");
                        }
                    }
                }
            }
        }
        
        if(counter_khat%6==0){
            i--;
        }
        // printf("this is counter_khat:%d\n i=%d, j=%d\n", counter_khat, i, j);
        SetConsoleTextAttribute(hConsole, 7);
        printf("\n");
        SetConsoleTextAttribute(hConsole, 7);
        if(i<0){
            // printf("this is counter_khat:%d\n i=%d, j=%d\n", counter_khat, i, j);
            break;
        }
    }
    SetConsoleTextAttribute(hConsole, 7);
    while(counter_khat%6!=2){
        i=0;
        int j;
        for(j=0; j<size_game; j++){
            if(j%2==0){
                SetConsoleTextAttribute(hConsole, 7);
                printf("      ");
                continue;
            }
            else{
                if(game_board[i][j]==0){
                    if(map_bin[i][j]==ENERGY){
                        int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);                        
                        SetConsoleTextAttribute(hConsole, colors[1]*16);
                        //haminja rang printf ro tanzim mikonim
                        print_energy_line(counter_khat, j, energy_left1, 0);
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");

                    }
                    else if(map_bin[i][j]==MITOSIS){
                        SetConsoleTextAttribute(hConsole, colors[2]*17);
                        printf("MMMMM");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==FORBIDDEN){
                        SetConsoleTextAttribute(hConsole, colors[3]*17);
                        printf("FFFFF");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==NORMAL){
                        SetConsoleTextAttribute(hConsole, colors[4]*17);
                        printf("NNNNN");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }
                else if(game_board[i][j]>0){//karbar aval
                    if(map_bin[i][j]==ENERGY){
                        int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);
                        if(counter_khat%6==4){
                            SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[0]);
                            if(game_board[i][j]>9){
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 2);
                            }else{
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 1);
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[1]*16);
                            print_energy_line(counter_khat, j, energy_left1, 0);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==MITOSIS){
                        if(counter_khat%6==4){
                            SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[0]);
                            if(game_board[i][j]>9){
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMM");
                                
                            }else{
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMM");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[2]*17);
                            printf("MMMMM");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    // else if(map_bin[i][j]==FORBIDDEN){
                    //     printf("stil what1");
                    // }
                    else if(map_bin[i][j]==NORMAL){
                        if(counter_khat%6==4){
                            SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[0]);
                            if(game_board[i][j]>9){
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNN");
                                
                            }else{
                                printf("%d", game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNN");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[4]*17);
                            printf("NNNNN");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }
                else if(game_board[i][j]<0){//karbar dovom
                    if(map_bin[i][j]==ENERGY){
                        int energy_left1=energy_left(i, j, num_boostup_blocks, boostup_blocks);
                        if(counter_khat%6==4){
                            SetConsoleTextAttribute(hConsole, (colors[1]*16)+colors[5]);
                            if((game_board[i][j]*-1)>9){
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 2);
                            }else{
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[1]*16);
                                print_energy_line(counter_khat, j, energy_left1, 1);
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[1]*16);
                            print_energy_line(counter_khat, j, energy_left1, 0);
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    else if(map_bin[i][j]==MITOSIS){
                        if(counter_khat%6==4){
                            SetConsoleTextAttribute(hConsole, (colors[2]*16)+colors[5]);
                            if((game_board[i][j]*-1)>9){
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMM");
                            }
                            else{
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[2]*17);
                                printf("MMMM");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[2]*17);
                            printf("MMMMM");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                    
                    // else if(map_bin[i][j]==FORBIDDEN){
                    //     printf("stil what1");
                    // }

                    else if(map_bin[i][j]==NORMAL){
                        if(counter_khat%6==4){
                            SetConsoleTextAttribute(hConsole, (colors[4]*16)+colors[5]);
                            if((game_board[i][j]*-1)>9){
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNN");
                            }else{
                                printf("%d", -1*game_board[i][j]);
                                SetConsoleTextAttribute(hConsole, colors[4]*17);
                                printf("NNNN");
                            }
                        }
                        else{
                            SetConsoleTextAttribute(hConsole, colors[4]*17);
                            printf("NNNNN");
                        }
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" ");
                    }
                }



            }
        }
        SetConsoleTextAttribute(hConsole, 7);
        // printf("this is counter_khat:%d\n i=%d, j=%d\n", counter_khat, i, j);
        printf("\n");
        counter_khat++;
    }
    SetConsoleTextAttribute(hConsole, 7);
    printf("\n");
    print_block_energies(boostup_blocks, num_boostup_blocks);
    return;

}


int millisleep(unsigned ms){
    SetLastError(0);
    Sleep(ms);
    return GetLastError() ?-1 :0;
}
