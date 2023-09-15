#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ShoppingItem {
    char name[50];
    int quantity;
    struct ShoppingItem* next;
};

struct ShoppingItem* shoppingList = NULL;
struct ShoppingItem* list2 = NULL;

void addItem(char itemName[], int itemQuantity) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuantity;
    newItem->next = NULL;

    if (shoppingList == NULL) {
        shoppingList = newItem;
    } else {
        struct ShoppingItem* current = shoppingList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}

void removeItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                shoppingList = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}

void displayList() {
    struct ShoppingItem* current = shoppingList;
    printf("购物清单:\n");
    while (current != NULL) {
        printf("%s - 数量：%d\n", current->name, current->quantity);
        current = current->next;
    }
}

void updateQuantity(char itemName[], int newItemQuantity) {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            current->quantity = newItemQuantity;
            break;
        }
        current = current->next;
    }
}

void clearList() {
    while (shoppingList != NULL) {
        struct ShoppingItem* temp = shoppingList;
        shoppingList = shoppingList->next;
        free(temp);
    }
}

int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }
    return total;
}

void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    printf("查找商品 \"%s\" ：\n", itemName);
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - 数量：%d\n", current->name, current->quantity);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到商品 \"%s\"。\n", itemName);
    }
}

void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL) {
        nextItem = current->next;
        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                strcpy(tempName, current->name);
                strcpy(current->name, nextItem->name);
                strcpy(nextItem->name, tempName);

                tempQuantity = current->quantity;
                current->quantity = nextItem->quantity;
                nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

void mergeLists() {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }

    if (current != NULL) {
        current->next = list2;
    } else {
        shoppingList = list2;
    }
    list2 = NULL;
}

void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                // 如果要删除的是第一个节点
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);
                if (!deleteAll) {
                    break;
                }
            } else {
                // 如果要删除的不是第一个节点
                struct ShoppingItem* temp = current;
                prev->next = current->next;
                current = current->next;
                free(temp);
                if (!deleteAll) {
                    break;
                }
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main() {
    int num;
    char itemName[50];
    int itemQuantity;
    printf("输入数字选择功能\n");
    printf("1:添加商品到购物清单\n");
    printf("2:从购物清单中移除商品\n");
    printf("3:查看购物清单\n");
    printf("4:修改购物清单中商品的数量\n");
    printf("5:清空购物清单\n");
    printf("6:计算购物清单中商品的总数量\n");
    printf("7:找购物清单中的商品\n");
    printf("8:排序购物清单\n");
    printf("9:合并购物清单\n");
    printf("10:删除购物清单中的商品\n");
    scanf("%d", &num);
    switch (num) {
        case 1:
            printf("输入商品名称：");
            scanf("%s", itemName);
            printf("输入商品数量：");
            scanf("%d", &itemQuantity);
            addItem(itemName, itemQuantity);
            break;
        case 2:
            printf("输入商品名称：");
            scanf("%s", itemName);
            removeItem(itemName);
            break;
        case 3:
            displayList();
            break;
        case 4:
            printf("输入商品名称：");
            scanf("%s", itemName);
            printf("输入商品数量：");
            scanf("%d", &itemQuantity);
            updateQuantity(itemName, itemQuantity);
            break;
        case 5:
            clearList();
            break;
        case 6:
            printf("购物清单中商品的总数量为：%d\n", totalQuantity());
            break;
        case 7:
            printf("输入商品名称：");
            scanf("%s", itemName);
            findItem(itemName);
            break;
        case 8:
            sortList();
            break;
        case 9:
            printf("输入要合并的第二个购物清单：\n");
            mergeLists();
            break;
        case 10:
            printf("输入要删除的商品名称：");
            scanf("%s", itemName);
            int deleteAll;
            printf("输入是否删除所有匹配的商品 (0-否，1-是)：");
            scanf("%d", &deleteAll);
            deleteItem(itemName, deleteAll);
            break;
        default:
            printf("NULL\n");
    }
    return 0;
}