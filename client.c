#include <stdio.h>
#include "tree.h"

int main()
{
    tree_t mytree;
    init(&mytree);

    int key, opt;

    while(1)
    {
        printf("\n===== Binary Search Tree Menu =====\n");
        printf("1. Insert a key\n");
        printf("2. Delete a key\n");
        printf("3. Display (Inorder Traversal)\n");
        printf("0. Exit\n");
        printf("===================================\n");
        printf("Enter your choice: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(&mytree, key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete_key(&mytree, key);
                break;

            case 3:
                printf("Inorder traversal: ");
                disp(&mytree);
                printf("\n");
                break;

            case 0:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
