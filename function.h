//From: Eplankton Date: 2021/8/12
char userInput[64];
char cushion;
struct matrix
{
    char *name;
    int row;
    int column;
};

int search(char *);                           //Compare userInput with the list of command.(0)
void test();                                  //A test process.(1)
void help();                                  //Help manual.(2)
void clear();                                 //Clear the screen.(3)
void matrixInput(char *);                     //To input a matrix.(4)
void matrixDetect(char *);                    //To detect a matrix.(5)
void matrixExtract(struct matrix *, float *); //To import a matrix from 'matrixstream'.
int matrixEmploy(struct matrix *);            //To confirm a matrix and return its name/row/column.
void matrixAddition(char *);                  //To add two matrixes together.(6)

int search(char *userInput)
{
    int i = 0, note = 0, len = 0, check = 0;
    FILE *fp = NULL;
    char buff[64];
    char copy[64];
    char temp[64];
    fp = fopen("command_list", "r");

    if (strchr(userInput, ')') == NULL || strchr(userInput, '(') == NULL)
    {
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m LOST_() \033[0m\n");
    }
    else
    {
        while (strcmp(buff, "END") != 0 && check == 0)
        {
            fgets(buff, 64, (FILE *)fp);
            for (i = 0; i < 63; i++)
            {
                temp[i] = buff[i];
            }
            const char t[2] = ")";

            len = strlen(strtok(temp, t));

            if (strncmp(buff, userInput, len) == 0) //Whether userInput is a command or not.
            {
                check = 1;
                for (i = 0; i < 63; i++)
                {
                    copy[i] = buff[i];
                }
            }
        }
    }

    if (check == 0)
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Command_NotFound\033[0m\n");
    }
    else
    {
        const char cut[2] = "#";
        char *token;
        token = strtok(copy, cut);

        while (token != NULL && check != 0)
        {
            note = atoi(token);
            token = strtok(NULL, cut);
        }
    }

    fclose(fp);
    return note;
}

void test()
{
    printf("[\033[32;1mSuccess\033[0m]\033[36;1m BioMatrix\033[0m (v0.0.1) is running on your environment.");
}

void help()
{
    int i = 0;
    FILE *fp = NULL;
    char buff[128];
    fp = fopen("help", "r");

    while (strcmp(buff, "END") != 0)
    {
        fgets(buff, 128, (FILE *)fp);
        const char t[2] = ")";
        printf("\n\033[32m    %s\033\n", buff);
    }
}

void clear()
{
    printf("\33[2J");
    printf("\33[100A");
}

void matrixInput(char *userInput)
{
    FILE *fp = NULL;
    fp = fopen("matrix", "a+");

    int j = 0, row = 0, column = 0;
    const char cut[2] = ",";
    const char cap[2] = "(";
    char *token;
    char *matrixName;
    char *temp;
    char *buff;

    token = strtok(userInput, cut);
    temp = token;

    while (token != NULL && j < 2)
    {
        switch (j)
        {
        case 0:
            token = strtok(NULL, cut);
            row = atoi(token);
            break;
        case 1:
            token = strtok(NULL, cut);
            column = atoi(token);
            break;
        }
        j++;
    }

    int check = 0;
    matrixName = strchr(temp, '(') + sizeof(char);

    if (row != 0 && column != 0)
    {
        while (!feof(fp) && check == 0)
        {
            int len = 0;
            fgets(buff, 64, (FILE *)fp);
            len = strlen(strtok(buff, "<"));

            if (strncmp(strtok(buff, "<"), matrixName, len) == 0 && check == 0) //Whether userInput is a useable matrixName.
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Existed\033[0m \033[33;1m<~ %s\033[0m\n", strtok(matrixName, ")"));
                check = 1;
            }
        }

        float save[row][column];
        float *r = &save[0][0];
        int m = 0, n = 0, i = 0;

        if (check != 0)
        {
            fclose(fp);
            fp = fopen("matrix", "r");
            int len = 0;
            len = strlen(matrixName);

            while (!feof(fp) && check != 0)
            {
                fgets(buff, 64, (FILE *)fp);
                if (strncmp(buff, matrixName, len) == 0 && check != 0)
                {
                    printf("\n\033[31;1mHere:\033[0m\n\n");
                    check = 0;
                    while (strchr(buff, '#') == NULL)
                    {
                        printf("\033[37;1m%s\033[0m", buff);
                        fgets(buff, 64, (FILE *)fp);
                    }
                }
            }
        }
        else
        {
            printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n\n", matrixName, row, column);
            for (i = 0; i < row; i++)
            {
                for (j = 0; j < column; j++)
                {
                    save[i][j] = 0;
                }
            }

            for (m = 0; m < row; m++)
            {
                for (n = 0; n < column; n++)
                {
                    printf(" %g ", save[m][n]);
                }
                printf("\n");
            }

            for (i = 0; i < row; i++)
            {
                for (j = 0; j < column; j++)
                {
                    printf("\nThe row(%d)column(%d) = ", i + 1, j + 1);

                    scanf("%g", &save[i][j]);

                    *r++ = save[i][j]; //Output the matrix

                    printf("\n");

                    for (m = 0; m < row; m++)
                    {
                        for (n = 0; n < column; n++)
                        {
                            if (m == i && n == j)
                            {
                                printf("\033[33;1m %g \033[0m", save[m][n]);
                            }
                            else
                            {
                                printf(" %g ", save[m][n]);
                            }
                        }
                        printf("\n");
                    }
                }
                printf("\n");
            }

            printf("\n[\033[32;1mMatrix\033[0m]: \033[33;1m%s\033[0m <\033[37;1m %d\033[0m,\033[37;1m %d\033[0m > has been saved.\n\n", matrixName, row, column);

            for (i = 0; i < row; i++)
            {
                for (j = 0; j < column; j++)
                {
                    if (j != 0)
                        printf("\033[37;1m %g \033[0m", save[i][j]);
                    else
                        printf("\033[37;1m[ %g \033[0m", save[i][j]);
                }
                printf("\033[37;1m]\033[0m\n");
            }

            fprintf(fp, "\n%s<%d,%d>\n", matrixName, row, column);
            for (i = 0; i < row; i++)
            {
                for (j = 0; j < column; j++)
                {
                    if (j == column - 1)
                        fprintf(fp, "%g\n", save[i][j]);
                    else
                        fprintf(fp, "%g ", save[i][j]);
                }
            }
            fprintf(fp, "#\n");

            FILE *fstream = NULL;
            fstream = fopen("matrixstream", "a+");
            fprintf(fstream, "\n%s<%d,%d>\n", matrixName, row, column);
            for (i = 0; i < row; i++)
            {
                for (j = 0; j < column; j++)
                {
                    fprintf(fstream, "%g\n", save[i][j]);
                }
            }
            fprintf(fstream, "#\n");
            fclose(fstream);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }

    fclose(fp);
}

void matrixDetect(char *userInput)
{
    FILE *fp = NULL;
    fp = fopen("matrix", "r");
    char buff[64];
    char *prov;
    char *matrixName;
    int check = 0;
    matrixName = strtok((strchr(userInput, '(') + sizeof(char)), ")"); //userInput as 'matrixInput(test)', matrixName = "test"

    if (matrixName != 0)
    {
        fclose(fp);
        fp = fopen("matrix", "r");

        int len = 0;
        len = strlen(matrixName);

        while (!feof(fp) && check == 0)
        {
            fgets(buff, 64, (FILE *)fp);
            if (strncmp(buff, matrixName, len) == 0 && check == 0)
            {
                printf("\n\033[34;1mHere:\033[0m\n\n");
                check = 1;
                while (strchr(buff, '#') == NULL)
                {
                    printf("\033[37;1m%s\033[0m", buff);
                    fgets(buff, 64, (FILE *)fp);
                }
            }
        }
        if (check == 0)
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }

    fclose(fp);
}

void matrixExtract(struct matrix *f, float *array)
{
    FILE *fstream = NULL;
    fstream = fopen("matrixstream", "r");
    char buff[10];
    char *prov;
    char *matrixName;
    int check = 0;
    int number = 0;
    matrixName = f->name;

    if (matrixName != 0)
    {
        fclose(fstream);
        fstream = fopen("matrixstream", "r");

        int len = 0;
        len = strlen(matrixName);

        while (!feof(fstream) && check == 0)
        {
            fgets(buff, 10, (FILE *)fstream);
            if (strncmp(buff, matrixName, len) == 0 && check == 0)
            {
                check = 1;
                fgets(buff, 10, (FILE *)fstream);
                while (strchr(buff, '#') == NULL && number != (f->row) * (f->column))
                {
                    int i = 0, j = 0;

                    if (number != (f->row) * (f->column))
                    {
                        for (i = 0; i < f->row; i++)
                        {
                            for (j = 0; j < f->column; j++)
                            {
                                fscanf(fstream, "%g", array);
                                fgets(buff, 10, (FILE *)fstream);
                                array++;
                                number++;
                            }
                        }
                    }
                }
            }
        }
        if (check == 0)
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }

    fclose(fstream);
}

int matrixEmploy(struct matrix *f)
{
    FILE *fp = NULL;
    fp = fopen("matrix", "r");
    char buff[64];
    char *matrixName;
    char *token;
    char *temp;
    char bach[2] = "<";
    int check = 0, i = 0, j = 0;
    matrixName = f->name;
    char prov[strlen(matrixName) + 5];

    for (i = 0; i < strlen(matrixName); i++)
    {
        prov[i] = matrixName[i];
    }
    strcat(prov, bach); //A new way to detect matrixName without using strtok()

    if (matrixName != 0)
    {
        fclose(fp);
        fp = fopen("matrix", "r");
        int len = 0;

        while (!feof(fp) && check == 0)
        {
            fgets(buff, 64, (FILE *)fp);

            if (strstr(buff, prov) != NULL && check == 0)
            {
                check = 1;
                token = strtok(buff, ",");
                temp = strchr(token, '<') + 1;
                token = strtok(NULL, ",");
                f->row = atoi(temp);
                f->column = atoi(token);
            }
        }
        if (check == 0)
        {
            printf("\n[\033[31;1mError\033[0m]:\033[31;1m Matrix Not_Found\033[0m \033[33;1m <~ %s\033[0m\n", matrixName);
        }
    }
    else
    {
        printf("\n[\033[31;1mError\033[0m]:\033[31;1m Invalid_input\033[0m\n");
    }

    fclose(fp);
    return check;
}

void matrixAddition(char *userInput)
{
    struct matrix former;
    struct matrix latter;
    struct matrix result;

    struct matrix *p = &former;
    struct matrix *q = &latter;

    FILE *fp = NULL;
    fp = fopen("matrix", "r+");
    int j = 0, check = 0;
    const char cut[2] = ",";
    const char cap[2] = "(";
    char *token;
    char buff[64];

    token = strtok(userInput, cut);

    former.name = strchr(token, '(') + sizeof(char);

    while (token != NULL && j < 2)
    {
        switch (j)
        {
        case 0:
            token = strtok(NULL, cut);
            latter.name = token;
            break;
        case 1:
            token = strtok(NULL, cut);
            if (token == 0)
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name_invalid\033[0m\n");
            }
            else
            {
                int i = 0;
                result.name = token;
                result.name[strlen(token) - 1] = '\0';

                char bach[strlen(result.name) + 5];
                char point[2] = "<";

                for (i = 0; i < strlen(result.name); i++)
                {
                    bach[i] = result.name[i];
                }
                strcat(bach, point);
                while (!feof(fp) && check == 0)
                {
                    fgets(buff, 64, (FILE *)fp);
                    if (strstr(buff, bach) != NULL && check == 0) //Whether userInput is a useable matrixName.
                    {
                        printf("\n[\033[31;1mError\033[0m]:\033[31;1m result.name existed\033[0m \033[33;1m<~ %s\033[0m\n", result.name);
                        check = 1;
                    }
                }
            }

            break;
        }
        j++;
    }

    if (token != 0 && check == 0)
    {
        int i = 0, j = 0;

        int check_former = matrixEmploy(p);
        int check_latter = matrixEmploy(q);

        if (check_former != 0 && check_latter != 0)
        {
            if (former.row == latter.row && former.column == latter.column)
            {
                float matrixfirst[former.row][former.column];
                float matrixsecond[latter.row][latter.column];
                float *arone = &matrixfirst[0][0];
                float *artwo = &matrixsecond[0][0];

                matrixExtract(p, arone);
                matrixExtract(q, artwo);

                printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", former.name, former.row, former.column);
                for (i = 0; i < former.row; i++)
                {
                    for (j = 0; j < former.column; j++)
                    {
                        if (j != 0)
                            printf(" %g ", matrixfirst[i][j]);
                        else
                            printf("[ %g ", matrixfirst[i][j]);
                    }
                    printf("]\n");
                }
                printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d > \n", latter.name, latter.row, latter.column);
                for (i = 0; i < latter.row; i++)
                {
                    for (j = 0; j < latter.column; j++)
                    {
                        if (j != 0)
                            printf(" %g ", matrixsecond[i][j]);
                        else
                            printf("[ %g ", matrixsecond[i][j]);
                    }
                    printf("]\n");
                }

                result.row = former.row;
                result.column = former.column;
                float matrixAns[former.row][latter.column];

                printf("\n[\033[34;1mMatrix\033[0m]: \033[33;1m%s\033[0m < %d, %d >\n", result.name, result.row, result.column);

                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        matrixAns[i][j] = matrixfirst[i][j] + matrixsecond[i][j];
                    }
                }

                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        if (j != 0)
                            printf(" %g ", matrixAns[i][j]);
                        else
                            printf("[ %g ", matrixAns[i][j]);
                    }
                    printf("]\n");
                }

                fprintf(fp, "\n%s<%d,%d>\n", result.name, result.row, result.column);

                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        if (j == result.column - 1)
                            fprintf(fp, "%g\n", matrixAns[i][j]);
                        else
                            fprintf(fp, "%g ", matrixAns[i][j]);
                    }
                }
                fprintf(fp, "#\n");

                FILE *fstream = NULL;
                fstream = fopen("matrixstream", "a+");
                fprintf(fstream, "\n%s<%d,%d>\n", result.name, result.row, result.column);
                for (i = 0; i < result.row; i++)
                {
                    for (j = 0; j < result.column; j++)
                    {
                        fprintf(fstream, "%g\n", matrixAns[i][j]);
                    }
                }
                fprintf(fstream, "#\n");
                fclose(fstream);
            }
            else
            {
                printf("\n[\033[31;1mError\033[0m]:\033[31;1m row/column not equal\033[0m\n");
            }
        }
    }
    else
    {
        printf("\n[\033[36;1mHelp\033[0m]:\033[37;1m >> matrixAddition(A,B,result)\033[0m\n");
    }
    fclose(fp);
}