#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ShoppingItem {
    char name[50];                  // 商品名称
    int quantity;                   // 商品数量
    struct ShoppingItem* next;      // 指向下一个节点的指针
};

// 购物清单头指针
struct ShoppingItem* shoppingList = NULL;

// 1. 添加商品到购物清单
void addItem(char itemName[], int itemQuantity) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuantity;
    newItem->next = NULL;

    if (shoppingList == NULL) {
        // 购物清单为空，直接将新节点设置为头节点
        shoppingList = newItem;
    } else {
        // 找到购物清单的尾节点，并将新节点连接到尾部
        struct ShoppingItem* current = shoppingList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}

// 2. 从购物清单中移除商品
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

// 3. 查看购物清单
void displayList() {
    struct ShoppingItem* current = shoppingList;

    if (current == NULL) {
        printf("购物清单为空。\n");
    } else {
        printf("购物清单:\n");
        while (current != NULL) {
            printf("%s - 数量：%d\n", current->name, current->quantity);
            current = current->next;
        }
    }
}

// 4. 修改购物清单中商品的数量
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

// 5. 清空购物清单
void clearList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    shoppingList = NULL; // 头指针置为空
}

// 6. 计算购物清单中商品的总数量
int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;

    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }

    return total;
}

// 7. 查找购物清单中的商品
void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    int found = 0;

    printf("查找商品 \"%s\"：\n", itemName);

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

// 8. 排序购物清单
void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;

    while (current != NULL) {
        nextItem = current->next;

        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                // 交换商品信息
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

// 9. 合并购物清单
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
  
    struct ShoppingItem* current = *list1;

    // 遍历到第一个购物清单的末尾
    while (current->next != NULL) {
        current = current->next;
    }

    // 将第二个购物清单连接到第一个清单的末尾
    current->next = *list2;
    *list2 = NULL; // 清空第二个购物清单的头指针，防止误用
}

// 10. 删除购物清单中的商品
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
    int choice;
    char itemName[50];
    int itemQuantity;
    struct ShoppingItem* list2 = NULL;   // 在 main 函数之外声明变量 list2
    struct ShoppingItem* list1 = NULL;   // 在 main 函数之外声明变量 list1

    while (1) {
        printf("欢迎使用购物清单管理系统！\n");
        printf("1. 添加商品到购物清单\n");
        printf("2. 从购物清单中移除商品\n");
        printf("3. 查看购物清单\n");
        printf("4. 修改购物清单中商品的数量\n");
        printf("5. 清空购物清单\n");
        printf("6. 计算购物清单中商品的总数量\n");
        printf("7. 查找购物清单中的商品\n");
        printf("8. 排序购物清单\n");
        printf("9. 合并购物清单\n");
        printf("10. 删除购物清单中的商品\n");
        printf("0. 退出\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入商品名称：");
                scanf("%s", itemName);
                printf("请输入商品数量：");
                scanf("%d", &itemQuantity);
                addItem(itemName, itemQuantity);
                printf("已添加商品到购物清单。\n\n");
                break;

            case 2:
                printf("请输入要移除的商品名称：");
                scanf("%s", itemName);
                removeItem(itemName);
                printf("已从购物清单中移除商品。\n\n");
                break;

            case 3:
                displayList();
                printf("\n");
                break;

            case 4:
                printf("请输入要修改数量的商品名称：");
                scanf("%s", itemName);
                printf("请输入新的商品数量：");
                scanf("%d", &itemQuantity);
                updateQuantity(itemName, itemQuantity);
                printf("已修改购物清单中商品的数量。\n\n");
                break;

            case 5:
                clearList();
                printf("已清空购物清单。\n\n");
                break;

            case 6:
                printf("购物清单中商品的总数量为：%d\n\n", totalQuantity());
                break;

            case 7:
                printf("请输入要查找的商品名称：");
                scanf("%s", itemName);
                findItem(itemName);
                printf("\n");
                break;

            case 8:
                sortList();
                printf("已排序购物清单。\n\n");
                break;

            case 9:
                printf("将list2合并到list1中。\n");

                addItem("商品1", 5);
                addItem("商品2", 3);
                addItem("商品3", 2);
                list1 = shoppingList;   // 将当前购物清单保存为list1

                addItem("商品4", 1);
                addItem("商品5", 4);
                list2 = shoppingList;   // 将当前购物清单保存为list2

                mergeLists(&list1, &list2);   // 合并两个购物清单
                shoppingList = list1;   // 将合并后的购物清单设置为当前购物清单

                printf("已合并购物清单。\n\n");
                break;

            case 10:
                printf("请输入要删除的商品名称：");
                scanf("%s", itemName);
                printf("是否删除所有匹配项？（1表示是，0表示否）：");
                scanf("%d", &itemQuantity);
                deleteItem(itemName, itemQuantity);
                printf("已删除购物清单中的商品。\n\n");
                break;

            case 0:
                printf("感谢使用购物清单管理系统！再见！\n");
                return 0;

            default:
                printf("无效选项，请重新输入。\n\n");
        }
    }

    return 0;
}

