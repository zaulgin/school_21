#include <stdio.h>
#define PERENOS printf("\n")
#define SPACE printf(" ")
#define BALL printf("o")
#define WIDTH 25
#define LENGTH 80

//переменные координат поля
unsigned int fieldX;
unsigned int fieldY;
//переменные координат мяча
unsigned int ballX = 39;
unsigned int ballY = 12;
//переменные координат ракеток
unsigned int rocket1X = 1;
unsigned int rocket1Y = 12;
unsigned int rocket2X = 78;
unsigned int rocket2Y = 12;
// char переменные пользовательского ввода
char p1input;
char p2input;
//переменная для определения корректного ввода
unsigned int incorrectInput = 0;
//переменные для направлений движения мяча
unsigned int ballMoveUp = 0;
unsigned int ballMoveLeft = 0;
//переменные для подсчета очков
unsigned int p1score = 0;
unsigned int p2score = 0;

//объявление функций
void inputCheck(char p1check, char p2check, char eos);
int game();
void fieldUpdate();
void ballMovement();
void gameOver();
void resetPositions();

int main() {
    //    char checkMenu;
    //    int menuChoice = 0;
    //     while(menuChoice != 2) {
    //         printf("1.Начать игру\n2.Выход\n");
    //         scanf("%d%c", &menuChoice, &checkMenu);
    //         if (menuChoice == 1 && checkMenu == '\n') {
    //             menuChoice = game(menuChoice);
    //         } else if (menuChoice == 2 && checkMenu == '\n') {
    //             printf("До свидания!\n");
    //             return 0;
    //         }
    //     }
    game();
    return 0;
}

void gameOver(int player) { printf("Игра окончена! Победил игрок №%d\n", player); }

//анализ пользовательского ввода
void inputCheck(char p1check, char p2check, char eos) {
    switch (p1check) {
        case 'a':
            rocket1Y--;
            if (rocket1Y < 2) {
                rocket1Y = 2;
            }
            break;
        case 'A':
            rocket1Y--;
            if (rocket1Y < 2) {
                rocket1Y = 2;
            }
            break;
        case 'z':
            rocket1Y++;
            if (rocket1Y > 22) {
                rocket1Y = 22;
            }
            break;
        case 'Z':
            rocket1Y++;
            if (rocket1Y > 22) {
                rocket1Y = 22;
            }
            break;
        case ' ':
            break;
        case '\n':
            break;
        default:
            break;
    }

    switch (p2check) {
        case 'k':
            rocket2Y--;
            if (rocket2Y < 2) {
                rocket2Y = 2;
            }
            break;
        case 'K':
            rocket2Y--;
            if (rocket2Y < 2) {
                rocket2Y = 2;
            }
            break;
        case 'm':
            rocket2Y++;
            if (rocket2Y > 22) {
                rocket2Y = 22;
            }
            break;
        case 'M':
            rocket2Y++;
            if (rocket2Y > 22) {
                rocket2Y = 22;
            }
            break;
        case ' ':
            break;
        case '\n':
            break;
        default:
            break;
    }

    if (eos != '\n') {
        incorrectInput = 1;
    }
}

int game() {
    char eos;
    // char lineCheck;
    fieldUpdate();
    ballMovement();
    while (1) {
        if (p1score != 21 && p2score != 21) {
            scanf("%c%c%c", &p1input, &p2input, &eos);
            inputCheck(p1input, p2input, eos);
            if (!incorrectInput) {
                //обновление поля
                fieldUpdate();
                ballMovement();
            } else {
                printf("некорректный ввод!\n");
                incorrectInput = 0;
            }
        } else if (p1score == 21) {
            resetPositions();
            fieldUpdate();
            gameOver(1);
            return 0;
        } else if (p2score == 21) {
            resetPositions();
            fieldUpdate();
            gameOver(2);
            return 0;
        }
    }
    return 0;
}

void ballMovement() {
    if (ballMoveUp && ballMoveLeft) {
        ballX--;
        ballY--;
    } else if (ballMoveUp && !ballMoveLeft) {
        ballX++;
        ballY--;
    } else if (!ballMoveUp && ballMoveLeft) {
        ballX--;
        ballY++;
    } else if (!ballMoveUp && !ballMoveLeft) {
        ballX++;
        ballY++;
    }
}

void fieldUpdate() {
    printf("\033[0d\033[2J");
    for (fieldY = 0; fieldY < WIDTH; fieldY++) {
        for (fieldX = 0; fieldX < LENGTH; fieldX++) {
            if ((fieldY == 0 || fieldX == 0) || (fieldY == 24 || fieldX == 79)) {
                printf("*");
            } else if (fieldX == rocket1X &&
                       (fieldY == rocket1Y || fieldY == rocket1Y - 1 || fieldY == rocket1Y + 1)) {
                printf("|");
            } else if (fieldX == rocket2X &&
                       (fieldY == rocket2Y || fieldY == rocket2Y - 1 || fieldY == rocket2Y + 1)) {
                printf("|");
            } else if (fieldX == ballX && fieldY == ballY) {
                if (ballY == 23 && ballMoveUp == 0 && ballX != 77 && ballX != 2) {
                    BALL;
                    ballMoveUp = 1;
                } else if (ballY == 1 && ballMoveUp == 1 && ballX != 77 && ballX != 2) {
                    BALL;
                    ballMoveUp = 0;
                } else if ((ballX == 77 && ballY != 23 && ballY != 1 &&
                            (ballY == rocket2Y || ballY == rocket2Y - 1 || ballY == rocket2Y + 1) &&
                            ballMoveLeft == 0)) {
                    BALL;
                    ballMoveLeft = 1;
                } else if ((ballX == 2 && ballY != 23 && ballY != 1 &&
                            (ballY == rocket1Y || ballY == rocket1Y - 1 || ballY == rocket1Y + 1) &&
                            ballMoveLeft == 1)) {
                    BALL;
                    ballMoveLeft = 0;
                } else if ((ballX == 77 && ballY == 23) &&
                           (ballY == rocket2Y || ballY == rocket2Y - 1 || ballY == rocket2Y + 1)) {
                    BALL;
                    ballMoveLeft = 1;
                    ballMoveUp = 1;
                } else if ((ballX == 77 && ballY == 1) &&
                           (ballY == rocket2Y || ballY == rocket2Y - 1 || ballY == rocket2Y + 1)) {
                    BALL;
                    ballMoveLeft = 1;
                    ballMoveUp = 0;
                } else if ((ballX == 2 && ballY == 23) &&
                           (ballY == rocket1Y || ballY == rocket1Y - 1 || ballY == rocket1Y + 1)) {
                    BALL;
                    ballMoveLeft = 0;
                    ballMoveUp = 1;
                } else if ((ballX == 2 && ballY == 1) &&
                           (ballY == rocket1Y || ballY == rocket1Y - 1 || ballY == rocket1Y + 1)) {
                    BALL;
                    ballMoveLeft = 0;
                    ballMoveUp = 0;
                } else {
                    BALL;
                }
            } else {
                SPACE;
            }
            if (ballX > 77) {
                resetPositions();
                p1score++;
                ballMoveLeft = 1;
                ballMoveUp = p1score % 2;
            }
            if (ballX < 2) {
                resetPositions();
                p2score++;
                ballMoveLeft = 0;
                ballMoveUp = p2score % 2;
            }
        }
        PERENOS;
    }
    //ТЕСТ КООРДИНАТ ВСЕХ ОБЪЕКТОВ!
    //     printf("ballX = %d\tballY = %d\n", ballX, ballY);
    //     printf("rocket1X = %d\trocket1Y = %d\n", rocket1X, rocket1Y);
    //     printf("rocket2X = %d\trocket2Y = %d\n", rocket2X, rocket2Y);
    printf("Player 1\t\t\t\t\t\t\tPlayer 2\n");
    printf("Score: %u\t\t\t\t\t\t\tScore: %u\n", p1score, p2score);
    printf("A/a: rocket up\t\t\t\t\t\t\tK/k: rocket up\n");
    printf("Z/z: rocket down\t\t\t\t\t\tM/m: rocket down\n");
}

void resetPositions() {
    ballX = 39;
    ballY = 12;
    rocket1X = 1;
    rocket1Y = 12;
    rocket2X = 78;
    rocket2Y = 12;
}
