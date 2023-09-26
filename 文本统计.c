/*以下任务需要用C语言完成：
对txt文件进行统计:1对于英文，统计每个单词(不区分大小写)出现过的次数:2对于其他符号(如“.”，“，”，不包括空格)统计每个符号出现过的次数。
实现功能:
给定单词/符号.输出对应的次数:统计结果以如下形式写入文件tongiitxt:
要求
结构使用单链表(不能使用数组，链表内部可以使用数组) ；链表空间在结束时要删除，不得造成内存泄露；
 能正确统计出不同单词/其他符号出现的次数 ；给定单词和符号，能够从链表中查询并输出次数 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 结构定义：链表节点
typedef struct Node {
    char* data;
    int count;
    struct Node* next;
} Node;

// 创建新节点
Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = strdup(data);
        newNode->count = 1;
        newNode->next = NULL;
    }
    return newNode;
}

// 查找节点
Node* findNode(Node* head, char* data) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 插入节点
void insertNode(Node** head, char* data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* existingNode = findNode(*head, data);
        if (existingNode) {
            existingNode->count++;
            free(newNode->data);
            free(newNode);
        } else {
            newNode->next = *head;
            *head = newNode;
        }
    }
}

// 释放链表内存
void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

//给定单词或者符号的查找
void findCount(Node* head, char* data) {
    Node* node = findNode(head, data);
    if (node) {
        printf("%s: %d\n", data, node->count);
    } else {
        printf("%s not found.\n", data);
    }
}

//找到出现最多的单词or符号
Node* findMostFrequent(Node* head) {
    Node* mostFrequent = NULL;
    Node* current = head;

    while (current != NULL) {
        if (mostFrequent == NULL || current->count > mostFrequent->count) {
            mostFrequent = current;
        }
        current = current->next;
    }

    return mostFrequent;
}

int isAlphaNumeric(char c) {
    return isalpha(c) || isdigit(c);
}

int isSymbol(char c) {
    return !isalnum(c) && c != ' ';
}

int main() {
    FILE* inputFile = fopen("C:\\Users\\Fanful\\CLionProjects\\workof828\\input.txt", "r");
    if (!inputFile) {
        printf("Failed to open input file.\n");
        return 1;
    }

    Node* wordList = NULL;
    Node* symbolList = NULL;
    int numWord = 0;
    int numSymbol = 0;
    char buffer[100];
    while (fscanf(inputFile, "%s", buffer) != EOF) {
        // 处理单词和符号，并插入链表
        int len = strlen(buffer);
        int start = 0;

        for (int i = 0; i <= len; i++) {
            if (isSymbol(buffer[i]) || buffer[i] == '\0') {
                if (i > start) {
                    char token[100];
                    strncpy(token, buffer + start, i - start);
                    token[i - start] = '\0';

                    if (isalpha(token[0])) {
                        // 处理单词
                        insertNode(&wordList, token);
                    } else {
                        // 处理符号
                        insertNode(&symbolList, token);
                    }
                }
                if (buffer[i] != ' ') {
                    // 插入当前符号
                    char symbol[2] = {buffer[i], '\0'};
                    insertNode(&symbolList, symbol);
                }
                start = i + 1;
            }
        }
    }

    fclose(inputFile);

    // 将统计结果写入文件
    FILE* outputFile = fopen("C:\\Users\\Fanful\\CLionProjects\\workof828\\tongji.txt", "w");
    if (!outputFile) {
        printf("Failed to open output file.\n");
        return 1;
    }

    Node* current = wordList;
    while (current != NULL) {
        fprintf(outputFile, "%s: %d\n", current->data, current->count);
        current = current->next;
        numWord += 1;
    }


    current = symbolList;
    while (current != NULL) {
        fprintf(outputFile, "%s: %d\n", current->data, current->count);
        current = current->next;
        numSymbol += 1;
    }

    fclose(outputFile);


    char findWord[100];
    printf("Find word: ");
    scanf("%s", findWord);
    findCount(wordList, findWord);

    char findSymbol;
    printf("Find symbol: ");
    scanf(" %c", &findSymbol); // 加入空格以忽略之前的换行符等输入
    char symbol[2] = {findSymbol, '\0'};
    findCount(symbolList, symbol);

    printf("total word number is %d,total symbol number is %d\n",numWord,numSymbol);
    // 查找并输出出现次数最多的单词
    Node* mostFrequentWord = findMostFrequent(wordList);
    if (mostFrequentWord) {
        printf("most frequency word: %s,totally: %d\n", mostFrequentWord->data, mostFrequentWord->count);
    } else {
        printf("Not Found\n");
    }

    // 查找并输出出现次数最多的符号
    Node* mostFrequentSymbol = findMostFrequent(symbolList);
    if (mostFrequentSymbol) {
        printf("most frequency symbol: %s,totally: %d\n", mostFrequentSymbol->data, mostFrequentSymbol->count);
    } else {
        printf("Not Found\n");
    }
    return 0;

}