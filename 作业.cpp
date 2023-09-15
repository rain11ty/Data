#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ShoppingItem {
    char name[50];                  // ��Ʒ����
    int quantity;                   // ��Ʒ����
    struct ShoppingItem* next;      // ָ����һ���ڵ��ָ��
};

// �����嵥ͷָ��
struct ShoppingItem* shoppingList = NULL;

// 1. �����Ʒ�������嵥
void addItem(char itemName[], int itemQuantity) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuantity;
    newItem->next = NULL;

    if (shoppingList == NULL) {
        // �����嵥Ϊ�գ�ֱ�ӽ��½ڵ�����Ϊͷ�ڵ�
        shoppingList = newItem;
    } else {
        // �ҵ������嵥��β�ڵ㣬�����½ڵ����ӵ�β��
        struct ShoppingItem* current = shoppingList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}

// 2. �ӹ����嵥���Ƴ���Ʒ
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

// 3. �鿴�����嵥
void displayList() {
    struct ShoppingItem* current = shoppingList;

    if (current == NULL) {
        printf("�����嵥Ϊ�ա�\n");
    } else {
        printf("�����嵥:\n");
        while (current != NULL) {
            printf("%s - ������%d\n", current->name, current->quantity);
            current = current->next;
        }
    }
}

// 4. �޸Ĺ����嵥����Ʒ������
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

// 5. ��չ����嵥
void clearList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    shoppingList = NULL; // ͷָ����Ϊ��
}

// 6. ���㹺���嵥����Ʒ��������
int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;

    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }

    return total;
}

// 7. ���ҹ����嵥�е���Ʒ
void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    int found = 0;

    printf("������Ʒ \"%s\"��\n", itemName);

    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - ������%d\n", current->name, current->quantity);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
    }
}

// 8. �������嵥
void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;

    while (current != NULL) {
        nextItem = current->next;

        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                // ������Ʒ��Ϣ
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

// 9. �ϲ������嵥
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
  
    struct ShoppingItem* current = *list1;

    // ��������һ�������嵥��ĩβ
    while (current->next != NULL) {
        current = current->next;
    }

    // ���ڶ��������嵥���ӵ���һ���嵥��ĩβ
    current->next = *list2;
    *list2 = NULL; // ��յڶ��������嵥��ͷָ�룬��ֹ����
}

// 10. ɾ�������嵥�е���Ʒ
void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                // ���Ҫɾ�����ǵ�һ���ڵ�
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);

                if (!deleteAll) {
                    break;
                }
            } else {
                // ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
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
    struct ShoppingItem* list2 = NULL;   // �� main ����֮���������� list2
    struct ShoppingItem* list1 = NULL;   // �� main ����֮���������� list1

    while (1) {
        printf("��ӭʹ�ù����嵥����ϵͳ��\n");
        printf("1. �����Ʒ�������嵥\n");
        printf("2. �ӹ����嵥���Ƴ���Ʒ\n");
        printf("3. �鿴�����嵥\n");
        printf("4. �޸Ĺ����嵥����Ʒ������\n");
        printf("5. ��չ����嵥\n");
        printf("6. ���㹺���嵥����Ʒ��������\n");
        printf("7. ���ҹ����嵥�е���Ʒ\n");
        printf("8. �������嵥\n");
        printf("9. �ϲ������嵥\n");
        printf("10. ɾ�������嵥�е���Ʒ\n");
        printf("0. �˳�\n");
        printf("������ѡ�");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("��������Ʒ���ƣ�");
                scanf("%s", itemName);
                printf("��������Ʒ������");
                scanf("%d", &itemQuantity);
                addItem(itemName, itemQuantity);
                printf("�������Ʒ�������嵥��\n\n");
                break;

            case 2:
                printf("������Ҫ�Ƴ�����Ʒ���ƣ�");
                scanf("%s", itemName);
                removeItem(itemName);
                printf("�Ѵӹ����嵥���Ƴ���Ʒ��\n\n");
                break;

            case 3:
                displayList();
                printf("\n");
                break;

            case 4:
                printf("������Ҫ�޸���������Ʒ���ƣ�");
                scanf("%s", itemName);
                printf("�������µ���Ʒ������");
                scanf("%d", &itemQuantity);
                updateQuantity(itemName, itemQuantity);
                printf("���޸Ĺ����嵥����Ʒ��������\n\n");
                break;

            case 5:
                clearList();
                printf("����չ����嵥��\n\n");
                break;

            case 6:
                printf("�����嵥����Ʒ��������Ϊ��%d\n\n", totalQuantity());
                break;

            case 7:
                printf("������Ҫ���ҵ���Ʒ���ƣ�");
                scanf("%s", itemName);
                findItem(itemName);
                printf("\n");
                break;

            case 8:
                sortList();
                printf("���������嵥��\n\n");
                break;

            case 9:
                printf("��list2�ϲ���list1�С�\n");

                addItem("��Ʒ1", 5);
                addItem("��Ʒ2", 3);
                addItem("��Ʒ3", 2);
                list1 = shoppingList;   // ����ǰ�����嵥����Ϊlist1

                addItem("��Ʒ4", 1);
                addItem("��Ʒ5", 4);
                list2 = shoppingList;   // ����ǰ�����嵥����Ϊlist2

                mergeLists(&list1, &list2);   // �ϲ����������嵥
                shoppingList = list1;   // ���ϲ���Ĺ����嵥����Ϊ��ǰ�����嵥

                printf("�Ѻϲ������嵥��\n\n");
                break;

            case 10:
                printf("������Ҫɾ������Ʒ���ƣ�");
                scanf("%s", itemName);
                printf("�Ƿ�ɾ������ƥ�����1��ʾ�ǣ�0��ʾ�񣩣�");
                scanf("%d", &itemQuantity);
                deleteItem(itemName, itemQuantity);
                printf("��ɾ�������嵥�е���Ʒ��\n\n");
                break;

            case 0:
                printf("��лʹ�ù����嵥����ϵͳ���ټ���\n");
                return 0;

            default:
                printf("��Чѡ����������롣\n\n");
        }
    }

    return 0;
}

