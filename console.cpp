#include "main.h"
#include "cmd_console_tools.h"
#include <ctime>
#include <iostream>
using namespace std;
void clearstdin()
{
    char c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
}

void func4()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;
    coord now_cur;

    srand((unsigned int)time(NULL));
    getRandC(size);
    generate(board, size, 5);

    paint_board(board, size);

    showstr(0,size.y+4,"��С�������������End����...");

    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "�����������������.", 0, 7, 1, 30);
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func5()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;

    coord now_cur;
    coord con_size, con_buf_size;

    int score = 0, total = 0, clear_count[8] = { 0 };

    getRandC(size);

    srand((unsigned int)time(NULL));
    generate(board, size, 5);

    setconsoleborder(size.c * 4 + 7, size.r * 2 + 5);
    setcursor(CURSOR_INVISIBLE);
    getconsoleborder(con_size.r, con_size.c, con_buf_size.r, con_buf_size.c);
    printf("��Ļ��%d��%d��\n", con_buf_size.r, con_buf_size.c);
    paint_board_with_line(board, size, { 1, 0}, 0);

    showstr(0, size.y * 2 + 2, "��С�������������End����...");
    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "�����������������.", 0, 7, 1, 30);
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func6()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;
    coord start, end, now;

    coord now_cur, con_size, con_buf_size;

    int clear_count[8] = { 0 };

    int loop, valid, ret, X, Y, maction, keycode1, keycode2;

    int next[3];

    coord path[100];
    coord clear_set[50];

    srand((unsigned int)time(NULL));
    getRandC(size);

    generate(board, size, size.r * size.c * 3 / 5);

    setcursor(CURSOR_INVISIBLE);
    setconsoleborder(4 * size.c + 3, 2 * size.r + 5);
    setfontsize("������", 28);
    getconsoleborder(con_size.x, con_size.y, con_buf_size.r, con_buf_size.c);

    cls();
    printf("��Ļ��%d��%d��(�Ҽ��˳�)", con_buf_size.r, con_buf_size.c);
    paint_board_with_line(board, size, { 1, 0 }, 0);

    enable_mouse();
    start = { -1,-1 };
    loop = 1;
    while (loop)
    {
        ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            now = { Y - 1,(X - 0) / 2 };

            //�������λ��
            valid = 0;
            if (now.x % 2 == 1 && now.y % 2 == 1)
            {
                now.x /= 2;
                now.y /= 2;
                if (now.x >= 0 && now.x < size.x && now.y >= 0 && now.y < size.y)
                    valid = 1;
            }

            //��Ч,��ʾ
            if (valid)
            {
                gotoxy(0, 2 * size.r + 2);
                setcolor();
                printf("[��ǰ���] %c��%c��                       ", now.r + 'A', now.c + '1');

                if (maction == MOUSE_LEFT_BUTTON_CLICK) //�������
                {
                    showstr(0, 2 * size.r + 2, "[[���]]");

                    if ((start.x == X && start.y == Y))
                        break;
                   
                    if (board[now.r][now.c] != 0) //����,��ѡ��ʼ��
                    {
                        if (start.x != -1) //��ԭ��ѡ��λ�õ���ԭ
                            printElem(board, size, start, {1,0 }, normal);
                        start = now; 
                        printElem(board, size, start, {1,0}, selected);
                    }
                    else if (start.x != -1 && start.y != -1) //û��,����ѡ��ʼ��
                    {
                        end = now;
                        if (!bfs(board, size, start, end, path))
                        {
                            gotoxy(0, 2 * size.r + 2);
                            setcolor();
                            printf("[����] �޷���[%c%c]�ƶ���[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                        }
                        else
                        { //�����ƶ�
                            dmove(board, size, { 1,0 }, path);

                            board[end.r][end.c] = board[start.r][start.c];
                            board[start.r][start.c] = 0;
                            start = { -1, -1 };

                            if (canclear(board, size, start, clear_set))
                            {
                                dclear(board, size, { 1,0 }, clear_set);
                                clear(board, clear_set, clear_count);
                            }
                            else
                            {
                                insert(board, size, next[0]);
                                insert(board, size, next[1]);
                                insert(board, size, next[2]);
                                next[0] = rand() % 7 + 1;
                                next[1] = rand() % 7 + 1;
                                next[2] = rand() % 7 + 1;
                            }
                            break;
                        }
                    } //�����λ��...

                } //maction
            }     //if valid
            //�����Ҽ�
            if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                break;
        }     //(CCT_MOUSE_EVENT)
    }         //end of while(loop)

    disable_mouse(); //�������

    showstr(0, size.r * 2 + 3, "��С�������������End����...");
    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "�����������������.", 0, 7, 1, 30);
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func7()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;

    coord now_cur;
    coord con_size, con_buf_size;

    coord start, end, now;
    int next[3];
    coord path[100];
    coord clear_set[50];
    int score = 0, total = 0, clear_count[8] = { 0 };
    int loop, wait_input, valid, ret, X, Y, maction, keycode1, keycode2;

    

    srand((unsigned int)time(NULL));
    getRandC(size);

    setcursor(CURSOR_INVISIBLE);
    setconsoleborder(4 * size.c + 50, 2 * size.r + 10);
    setfontsize("������", 28);
    getconsoleborder(con_size.x, con_size.y, con_buf_size.x, con_buf_size.y);

    enable_mouse();
    cls();

    generate(board, size, 5);
    next[0] = rand() % 7 + 1;
    next[1] = rand() % 7 + 1;
    next[2] = rand() % 7 + 1;

    printf("��Ļ��%d��%d��(�Ҽ��˳�)", con_buf_size.r, con_buf_size.c);

    coord board_start = { 1, 0 }; //size.r/y,size.c/x
    coord score_start = { 1, size.x * 4 + 12 };
    coord next_start = { 5, size.x * 4 + 12 };
    coord stat_start = { 9, size.x * 4 + 12 };
    coord tips_start = { 2 * size.r + 2, 0 };

    paint_board_with_line(board, size, board_start, 0);
    paint_score(total, score_start, 0);
    paint_next(next, next_start, 0);
    paint_stat(board, size, stat_start, clear_count, 0);

    start = { -1,-1 };
    loop = 1;
    while (!game_over(board, size) && loop)
    {
        paint_board_with_line(board, size, board_start, 1);
        paint_score(total, score_start, 1);
        paint_next(next, next_start, 1);
        paint_stat(board, size, stat_start, clear_count, 1);

        wait_input = 1;
        while (wait_input)
        {
            ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

            if (ret == CCT_MOUSE_EVENT)
            {
                now.x = (X - board_start.x) / 2;
                now.y = Y - board_start.y;

                //�������λ��
                valid = 0;
                if (now.x % 2 == 1 && now.y % 2 == 1)
                {
                    now.x /= 2;
                    now.y /= 2;
                    if (now.x >= 0 && now.x < size.x && now.y >= 0 && now.y < size.y)
                        valid = 1;
                }
                //��Ч,��ʾ
                if (valid)
                {
                    gotoxy(tips_start.x, tips_start.y);
                    setcolor();
                    printf("[��ǰ���] %c��%c��                       ", now.r + 'A', now.c + '1');

                    if (maction == MOUSE_LEFT_BUTTON_CLICK) //�������
                    {
                        showstr(tips_start.x+1, tips_start.y, "[[���]]");

                        if (board[now.r][now.c] != 0) //����,��ѡ��ʼ��
                        {
                            if (start.x != -1) //��ԭ��ѡ��λ�õ���ԭ
                                printElem(board, size, start, board_start, normal);
                            start = now;
                            printElem(board, size, now, board_start, selected);
                        }
                        else if (start.x != -1 && start.y != -1) //û��,����ѡ��ʼ��
                        {
                            end = now;
                            if (!bfs(board, size, start, end, path))
                            {
                                gotoxy(tips_start.x, tips_start.y);
                                setcolor();
                                printf("[����] �޷���[%c%c]�ƶ���[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                            }
                            else
                            { //�����ƶ�
                                dmove(board, size, board_start, path);

                                board[end.r][end.c] = board[start.r][start.c];
                                board[start.r][start.c] = 0;
                                start = { -1, -1 };

                                if (canclear(board, size, end, clear_set))
                                {
                                    dclear(board, size, board_start, clear_set);
                                    clear(board, clear_set, clear_count);
                                }
                                else
                                {
                                    insert(board, size, next[0]);
                                    insert(board, size, next[1]);
                                    insert(board, size, next[2]);
                                    next[0] = rand() % 7 + 1;
                                    next[1] = rand() % 7 + 1;
                                    next[2] = rand() % 7 + 1;
                                }
                                wait_input = 0;
                            }
                        } //�����λ��...

                    } //maction
                }     //if valid
                //�����Ҽ�
                if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                    loop = wait_input = 0;
            } //if (CCT_MOUSE_EVENT)
        }     //loop
    }         //!gameover&&loop

    disable_mouse(); //�������

    showstr(tips_start.x, tips_start.y + 2, "��С�������������End����...");

    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "�����������������.");
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func8()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;

    coord now_cur, con_size, con_buf_size;

    coord start, end, now, selectbox;
    int next[3];
    coord path[100];
    coord clear_set[50];
    int score = 0, total = 0, clear_count[8] = { 0 };
    int loop, wait_input, valid, ret, X, Y, maction, keycode1, keycode2;

    getRandC(size);

    srand((unsigned int)time(NULL));
    setcursor(CURSOR_INVISIBLE);
    setconsoleborder(4 * size.c + 50, 2 * size.r + 10);
    setfontsize("������", 28);
    getconsoleborder(con_size.x, con_size.y, con_buf_size.x, con_buf_size.y);
    enable_mouse();

    generate(board, size, 5);
    next[0] = rand() % 7 + 1;
    next[1] = rand() % 7 + 1;
    next[2] = rand() % 7 + 1;

    //������ӡ��λ��
    coord board_start = { 1, 0 }; //size.r/y,size.c/x
    coord score_start = { 1, size.x * 4 + 12 };
    coord next_start = { 5, size.x * 4 + 12 };
    coord stat_start = { 9, size.x * 4 + 12 };
    coord tips_start = { 2 * size.r + 2, 0 };
    start = { -1,-1 };
    selectbox = { 0,0 };//��ʼλ��Ϊ{0,0}

    cls();
    printf("��Ļ��%d��%d��(�Ҽ��˳�)", con_buf_size.r, con_buf_size.c);

    paint_board_with_line(board, size, board_start, 0);
    paint_score(total, score_start, 0);
    paint_next(next, next_start, 0);
    paint_stat(board, size, stat_start, clear_count, 0);

    loop = 1;
    while (!game_over(board, size) && loop)
    {
        paint_board_with_line(board, size, board_start, 1);
        paint_score(total, score_start, 1);
        paint_next(next, next_start, 1);
        paint_stat(board, size, stat_start, clear_count, 1);
        printElem(board, size, selectbox, board_start, board[selectbox.r][selectbox.c] ? normal_with_box : box);

        wait_input = 1;
        while (wait_input)
        {
            ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

            if (ret == CCT_MOUSE_EVENT)
            {
                now.x = (X - board_start.x) / 2;
                now.y = Y - board_start.y;

                //�������λ��
                valid = 0;
                if (now.x % 2 == 1 && now.y % 2 == 1)
                {
                    now.x /= 2;
                    now.y /= 2;
                    if (now.x >= 0 && now.x < size.x && now.y >= 0 && now.y < size.y)
                        valid = 1;
                }
                //��Ч,��ʾ
                if (valid)
                {
                    gotoxy(tips_start.x, tips_start.y);
                    setcolor();
                    printf("[��ǰ���] %c��%c��                       ", now.r + 'A', now.c + '1');

                    if (maction == MOUSE_LEFT_BUTTON_CLICK) //�������
                    {
                        showstr(tips_start.x + 1, tips_start.y, "[[���]]");

                        if (board[now.r][now.c] != 0) //����,��ѡ��ʼ��
                        {
                            if (start.x != -1) //��ԭ��ѡ��λ�õ���ԭ
                                printElem(board, size, start, board_start, normal);
                            start = now;
                            printElem(board, size, now, board_start, selected);
                        }
                        else if (start.x != -1 && start.y != -1) //û��,����ѡ��ʼ��
                        {
                            end = now;
                            if (!bfs(board, size, start, end, path))
                            {
                                gotoxy(tips_start.x, tips_start.y);
                                setcolor();
                                printf("[����] �޷���[%c%c]�ƶ���[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                            }
                            else
                            { //�����ƶ�
                                dmove(board, size, board_start, path);

                                board[end.r][end.c] = board[start.r][start.c];
                                board[start.r][start.c] = 0;
                                start = { -1, -1 };

                                if (canclear(board, size, end, clear_set))
                                {
                                    dclear(board, size, board_start, clear_set);
                                    clear(board, clear_set, clear_count);
                                }
                                else
                                {
                                    insert(board, size, next[0]);
                                    insert(board, size, next[1]);
                                    insert(board, size, next[2]);
                                    next[0] = rand() % 7 + 1;
                                    next[1] = rand() % 7 + 1;
                                    next[2] = rand() % 7 + 1;
                                }
                                wait_input = 0;
                            }
                        } //�����λ��...

                    } //maction
                }     //if valid
                //�����Ҽ�
                if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                    loop = wait_input = 0;

            } //if (CCT_MOUSE_EVENT)
            else if (ret == CCT_KEYBOARD_EVENT) {
                showstr(tips_start.x, tips_start.y, "[��ǰ����]                       ", 0, 7, 1, 30);
                
                switch (keycode1) {
                case 27:	//ESC��,ȡ��ѡ��
                    if(start.x!=-1)
                        printElem(board, size, start, board_start,normal );
                    start = { -1,-1 };
                    showstr(tips_start.x + 10, tips_start.y, "Esc", 0, 7, 1, 30);
                    break;//Esc break
                case 13://Enter
                case 32://Space
                    if (board[selectbox.r][selectbox.c] != 0) //����,��ѡ��ʼ��
                    {
                        if (start.x != -1) //��ԭ��ѡ��λ�õ���ԭ
                            printElem(board, size, start, board_start, normal);
                        start = selectbox;
                        printElem(board, size, start, board_start, selected_with_box);
                    }
                    else if (start.x != -1) //û��,����ѡ��ʼ��
                    {
                        end = selectbox;
                        if (!bfs(board, size, start, end, path))
                        {
                            gotoxy(tips_start.x, tips_start.y);
                            setcolor();
                            printf("[����] �޷���[%c%c]�ƶ���[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                        }
                        else
                        { //�����ƶ�
                            dmove(board, size, board_start, path);

                            board[end.r][end.c] = board[start.r][start.c];
                            board[start.r][start.c] = 0;
                            start = { -1, -1 };//����startλ��

                            if (canclear(board, size, end, clear_set))
                            {
                                dclear(board, size, board_start, clear_set);
                                clear(board, clear_set, clear_count);
                            }
                            else
                            {
                                insert(board, size, next[0]);
                                insert(board, size, next[1]);
                                insert(board, size, next[2]);
                                next[0] = rand() % 7 + 1;
                                next[1] = rand() % 7 + 1;
                                next[2] = rand() % 7 + 1;
                            }
                            wait_input = 0;
                        }
                    } 
                    break;//Enter break
                case 224://�����
                    //ԭλ��
                    if(selectbox.x==start.x&&selectbox.y==start.y)//��ѡ�е�
                        printElem(board, size, selectbox, board_start, selected);
                    else//����
                        printElem(board, size,selectbox , board_start, normal);
                        switch (keycode2) {
                    case KB_ARROW_UP:
                        if(selectbox.y>0)selectbox.y--;
                        showstr(tips_start.x+10, tips_start.y, "�ϼ�ͷ", 0, 7, 1, 30);
                        break;
                    case KB_ARROW_DOWN:
                        if (selectbox.y <size.y-1)selectbox.y++;
                        showstr(tips_start.x + 10, tips_start.y, "�¼�ͷ", 0, 7, 1, 30); 
                        break;
                    case KB_ARROW_LEFT:
                        if (selectbox.x > 0)selectbox.x--;
                        showstr(tips_start.x + 10, tips_start.y, "���ͷ", 0, 7, 1, 30);
                        break;
                    case KB_ARROW_RIGHT:
                        if (selectbox.x <size.x-1)selectbox.x++;
                        showstr(tips_start.x + 10, tips_start.y, "�Ҽ�ͷ", 0, 7, 1, 30);
                        break;
                    }//�ĸ�����
                    //��λ��
                        if (selectbox.r == start.r&&selectbox.c == start.c)//��ѡ�е�
                            printElem(board, size, selectbox, board_start, selected_with_box);
                        else if (board[selectbox.r][selectbox.c] != 0)
                            printElem(board, size, selectbox, board_start, normal_with_box);
                        else
                            printElem(board, size, selectbox, board_start, box);
                     break;//case 224 break
                }//end of swicth(keycode1)
            }//end of else if(ret == CCT_KEYBOARD_EVENT��

        }     //loop
    }         //!gameover&&loop

    disable_mouse(); //�������

    showstr(tips_start.x, tips_start.y + 2, "��С�������������End����...");

    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "�����������������.");
        gotoxy(now_cur.x, now_cur.y);
    }
}