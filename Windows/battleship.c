#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

// On the player - 0 means blank, 1 means ship
// On the board - 0 means blank, 1 means successful ship blast, 2 means missed attempt

int take_cords(char orientation, int n){
    int cords;
    scanf("%d", &cords);
    while(cords < 0 || cords > 99 ||(orientation == 'h' && (cords/10)>(10 - n))||(orientation == 'v' && (cords % 10)>(10 - n))){
        printf("Invalid input. Enter again: ");
        scanf("%d", &cords);
    }
    return cords;
}

int check_validity(char orientation, int n, int player_board[10][10], int x, int y){
    int i, invalid=0;
    if(orientation=='h'){
        for(i=0; i<n; i++){
            if(player_board[x+i][y]!=0){invalid=1; break;}
        }
    } else if(orientation=='v'){
        for(i=0; i<n; i++){
            if(player_board[x][y+i]!=0){invalid=1; break;}
        }
    } else{
        if(player_board[x][y]!=0) invalid=1;
    }
    return invalid;
}

void print_board_1(int player_board[10][10]){
    printf("The board looks like: \n\n");
    int i, k;
    for(k=0; k<=9; k++){
        printf(" %d ", k);
    }
    printf("\n");
    for(k=0; k<=9; k++){
        for(i=0; i<=9; i++){
                if(player_board[i][k]==0) printf(" _ ");
                else printf(" X ");
        }
        printf(" %d \n", k);
    }
}

void print_board_2(int playerTurn, int player_board[10][10], int board[10][10]){
    printf("O means a HIT ship, _ means missed attack, X means blank.\n");
    printf("If you see continuous numbers, like 55555 or 22, then that is a Ship of n-length that you've sunk.\n");
    printf("This is Player-%d's turn. The board looks like: \n", playerTurn);
    int i, k;
    for(k=0; k<=9; k++){
        printf(" %d ", k);
    }
    printf("\n");
    for(k=0; k<=9; k++){
        for(i=0; i<=9; i++){
                if(board[i][k]==0) printf(" X ");
                else if(board[i][k]==10) printf(" _ ");
                else if(board[i][k]==1) printf(" O ");
                else printf(" %d ", board[i][k]);
        }
        printf(" %d \n", k);
    }
}

int generate_board(int player_num, int player_board[10][10]){
    int i, n, x, y, cords, invalid=0;
    char orientation;
    printf("\n\nPlayer %d is to enter his configuration.\nThere will be 4 ships on this 10x10 board.\nTheir lengths will be 2,3,4,5\n", player_num);
    print_board_1(player_board);
    for(n=5; n>=2; --n){
        printf("(Player %d) Do you want your %d tiles long ship to be vertical or horizontal?\nEnter H for horizontal and V for vertical: ",player_num, n);
        scanf(" %c", &orientation);
        orientation = tolower(orientation);
        while(orientation!='h' && orientation!='v'){
            printf("Invalid input. Enter again: ");
            scanf(" %c", &orientation);
            orientation = tolower(orientation);
        }
        do{
            if(invalid ==1) printf("Invalid coordinates, Enter XY again: ");
            else if(orientation=='h') printf("(Player %d) Enter the position of the leftmost point of the ship\n(Format is XY): ", player_num);
            else printf("(Player %d) Enter the poisition of the topmost point of the ship\n(Format is XY): ", player_num);
            cords = take_cords(orientation, n);
            x = cords/10;
            y = cords - (10*x);
            invalid = check_validity(orientation, n, player_board, x, y);
        }while(invalid==1);
        if(orientation=='h'){ for(i=0; i<n; i++){player_board[x+i][y] = n;} }
        else { for(i=0; i<n; i++){player_board[x][y+i] = n;} }
        print_board_1(player_board);
    }
}

void update_board(int player_board[10][10], int x, int y, int board[10][10]) {
    if (player_board[x][y] == 0) {
        board[x][y] = 10;
        printf(">>> THE ATTACK WAS A MISS! <<<\n\n");
    } else {
        board[x][y] = 1;
        int ship_id = player_board[x][y];

        int unhit_segments = 0;
        for (int k = 0; k <= 9; k++) {
            for (int i = 0; i <= 9; i++) {
                if (player_board[i][k] == ship_id && board[i][k] != 1) {
                    unhit_segments++;
                }
            }
        }

        if (unhit_segments == 0) {
            for (int k = 0; k <= 9; k++) {
                for (int i = 0; i <= 9; i++) {
                    if (player_board[i][k] == ship_id) board[i][k] = ship_id;
                }
            }
            system("cls");
            printf(">>> THE ATTACK SANK THE ENTIRE %d-TILE SHIP! <<<\n\n", ship_id);
        } else {
            system("cls");
            printf(">>> THE ATTACK WAS A HIT! <<<\n\n");
        }
    }
}

int check_win(int board1[10][10], int player1[10][10], int board2[10][10], int player2[10][10]){
    int counter1[6]={0};
    int counter2[6]={0};
    for(int k=0; k<=9; k++){
        for(int i=0; i<=9; i++){
            if(player1[i][k]!=0 && player1[i][k]==board1[i][k]) counter1[player1[i][k]]++;
            if(player2[i][k]!=0 && player2[i][k]==board2[i][k]) counter2[player2[i][k]]++;
        }
    }
    if(counter1[2]==2 && counter1[3]==3 && counter1[4]==4 && counter1[5]==5){
        printf("Player 2 wins!");
        exit(0);
    } else if(counter2[2]==2 && counter2[3]==3 && counter2[4]==4 && counter2[5]==5){
        printf("Player 1 wins!");
        exit(0);
    }
}

int main(){
     int board1[10][10] = {0};
     int board2[10][10] = {0};
     int player1[10][10] = {0};
     int playerTurn = 1;
     int attack_cords, x, y, invalidity = 0;
     system("cls");
     generate_board(1, player1);
     system("cls");
     int player2[10][10] = {0};
     generate_board(2, player2);
     system("cls");
     printf("Now the Game starts.\n");
     for(int i=1; i>0; i++){
         invalidity=0;
         if(i%2!=0){playerTurn=1; print_board_2(playerTurn, player1, board2);}
         else {playerTurn=2; print_board_2(playerTurn, player2, board1);}
         printf("Enter the coordinates (XY) of the place you'd like to attack: ");
         do{
             if(invalidity!=0) printf("Invalid input, enter again: ");
             attack_cords = take_cords(1, 1);
             x = attack_cords/10;
             y = attack_cords - (x*10);
             if(playerTurn==1) invalidity = check_validity(1, 1, board2, x, y);
             else invalidity = check_validity(1, 1, board1, x, y);
         }while(invalidity==1);
         if (i % 2 != 0) {
             system("cls");
             update_board(player2, x, y, board2); // P1 attacks P2's ships, recorded on board1
             print_board_2(playerTurn, player1, board2);
             printf("\n\nPress ENTER to continue...");
             getchar(); getchar(); // Input pause to let player read result before clearing
             system("cls");

        } else {
            system("cls");
             update_board(player1, x, y, board1); // P2 attacks P1's ships, recorded on board2
             print_board_2(playerTurn, player1, board1);
             printf("\n\nPress ENTER to continue...");
             getchar(); getchar();
             system("cls");
        }
        check_win(board1, player1, board2, player2);
    }
}
