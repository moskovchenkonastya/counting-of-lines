#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>  

using namespace std;

//Размер блока, используемого для расширения памяти под строку
#define blockSize 5

unsigned lookForNewLine(char *str, unsigned strUsed);

int main(int argc, char *argv[]) {
    
/*
    stream    - файл, из которого ведется чтение;
    line      - массив строк из файла (буфер);
    lineUsed  - количество символов текущей строки, уже хранящихся в буфере;
    lineIndex - номер текущей строки (начиная с 0).
 */
    unsigned lineUsed = 0, lineIndex = 0;
    
    if (argc != 2){
       cout <<"Data is not correct\n" << endl;
       return 1;
    }
    
    FILE 	*stream = fopen(argv[1], "r");
	char  **line = (char **) malloc(sizeof(char *));

	 /*
    Выделяем место под первую строку. Не забываем, что в строке будет еще пристуствовать
    символ '\n', и поэтому выделяем памяти на 1 символ больше, чем размер блока.
    */

    line[0] = (char *) malloc(blockSize + 1);

    /*
    Будет производить чтение строк, пока это возможно. В том случае, когда файл закончится,
    fgets по стандарту вернет NULL. Длина считываемого блока равна N = blockSize + 1, т.к. по стандарту
    fgets считывает не более чем N-1 символов, добавляя в конец строки '\0'.

    newLine - позиция символа перeвода строки в текущей строке.

    В случае, если символ не найден, мы увеличиваем размер буффера под текущую строку и продолжаем процесс.
    Иначе - отcекаем лишний кусок выделенной памяти и выделяем место под новую строку, не забыв обнулить
    переменную lineUsed.
    */

    while (fgets(&line[lineIndex][lineUsed], blockSize + 1, stream) != NULL) {
        unsigned newLine = lookForNewLine(line[lineIndex], lineUsed);
        cout<<newLine<<endl;
        if (newLine != -1) {
            lineUsed += blockSize;
            line[lineIndex] = (char *) realloc(line[lineIndex], lineUsed + blockSize + 1);
        } else {
            lineUsed = newLine;
            line[lineIndex][lineUsed] = '\0';
            line[lineIndex] = (char *) realloc(line[lineIndex], lineUsed + 1);
            line = (char **) realloc(line, (++lineIndex + 1) * sizeof(char *));
            line[lineIndex] = (char *) malloc(blockSize + 1);
            lineUsed = 0;
        }
    }

    fclose(stream);
    
    //cout << lineIndex + 1 << endl;
    /*
   освобождение памяти
    */
    for (unsigned i = 0; i < lineIndex; i++) {
        
        free(line[i]);
    }

    free(line[lineIndex]);
    free(line);
    

    
    
    
    
    return 0;
}

unsigned lookForNewLine(char *str, unsigned strUsed) {
    unsigned i = strUsed;
    while (str[i--] != &&str[i] != '\n' && str[i] != EOF) {
        i++;
    } 
    //if(str[i] == '\n') cout << i <<endl;
    return (str[i] == '\n') ? i: -1;
}

