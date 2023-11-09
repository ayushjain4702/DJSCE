#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char name[40];
    char phone_no[12];
    struct node*left;
    struct node*right;
};
struct node*head = NULL;
char temp_n[40];
char temp_p[12];

struct node* createNode(char*name, char*phone_no){
    struct node*new_node = (struct node*)malloc(sizeof(struct node));
    strcpy(new_node->name, name);
    strcpy(new_node->phone_no, phone_no);
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insert(char*name, char*phone_no)
{
    struct node*root = head;
    struct node*prev = NULL;
    if(root == NULL)
    {
        struct node*new_node = createNode(name, phone_no);
        head = new_node;
        return;
    }
    
    while(root!=NULL)
    {
        prev = root;
        if(strcmp(root->name,name)==0)
        {
            printf("Name is already there!\n");
            return;
        }
        else if(strcmp(root->name, name)>0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    struct node* new_node = createNode(name, phone_no);
    if(strcmp(prev->name, name)>0)
    {
        prev->left = new_node;
        
    }
    else
    {
        prev->right = new_node;
    }
}

int count_asc = 1;
void show_ascending(struct node*root)
{
    if(root!=NULL)
    {
        show_ascending(root->left);
        printf("%d Name : %15s, Phone No. %-10s \n",count_asc, root->name, root->phone_no);
        count_asc++;
        show_ascending(root->right);
    }
}

int count_desc = 1;
void show_descending(struct node*root)
{
    if(root!=NULL)
    {
        show_descending(root->right);
        printf("%d Name : %15s, Phone No. %-10s \n",count_desc, root->name, root->phone_no);
        count_desc++;
        show_descending(root->left);
    }
}

int found = 0;
int count_search = 1;
void search(struct node*root, char*phone_no)
{
    if(root!=NULL)
    {
        search(root->left, phone_no);
        if(strcmp(root->phone_no, phone_no) == 0)
        {
            printf("%d Name : %15s, Phone No. %-10s \n",count_search, root->name, root->phone_no);
            found = 1;
            count_search++;
        }
        search(root->right, phone_no);
    }
}

struct node*predecessor(struct node*root)
{
    while(root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

struct node*delete(struct node*root, char*name)
{
    if(root == NULL)
    {
        return root;
    }
    
    if(strcmp(root->name, name)>0)
    {
        root->left = delete(root->left, name);
    }
    else if(strcmp(root->name, name)<0)
    {
        root->right = delete(root->right, name);
    }
    else
    {
        if(root->left == NULL)
        {
            struct node*temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct node*temp = root->left;
            free(root);
            return temp;
        }
        
        struct node*pre = predecessor(root->left);
        strcpy(root->name, pre->name);
        root->left = delete(root->left, pre->name);
        
    }
    return root;
}

int main()
{
    printf("\n==================Phone Book Management System Using Treaps===================");
    // printf("======================================================================\n");
    menu:
    printf("\n---------------MENU--------------\n");
    printf("1. Add Contacts\n");
    printf("2. Remove Contacts\n");
    printf("3. Search by Phone No.\n");
    printf("4. Shown in Ascending Order\n");
    printf("5. Shown in Descending Order\n");
    printf("6. Exit Program\n");
    printf("\n---------------MENU--------------\n");
    int choice;
    printf("\n---------------------------------\n");
    printf("Enter the choice: ");
    scanf("%d", &choice);
    printf("\n---------------------------------\n");
    printf("\n");
    if(choice == 1)
    {
        printf("\n---------------------------------\n");
        printf("Enter Name: \n");
        while((getchar())!= '\n');
        scanf("%[^\n]%*c", temp_n);
        
        printf("Enter Phone No.: \n");
        scanf("%[^\n]%*c", temp_p);
        
        insert(temp_n,temp_p);
    }
    else if(choice == 2)
    {
        printf("\n---------------------------------\n");
        printf("Enter Name to Delete: \n");
        while((getchar())!= '\n');
        scanf("%[^\n]%*c", temp_n);
        delete(head, temp_n);
        
    }
    else if(choice == 3)
    {
        printf("\n---------------------------------\n");
        
        struct node*root = head;
        if(root == NULL)
        {
            printf("\n No Contacts are there to Search!");
            goto menu;
        }
        
        printf("Enter the Phone No.: \n");
        while((getchar())!= '\n');
        scanf("%[^\n]",temp_p);
        search(root, temp_p);
        if(found == 0)
        {
            printf("No Contacts Found!\n");
        }
        found = 0;
        count_search = 1;
        printf("\n");
       
        
    }
    else if(choice == 4)
    {
        printf("\n---------------------------------\n");
        
        struct node*root = head;
        if(root == NULL)
        {
            printf("\n No Contacts are there to show!");
            goto menu;
        }
        printf("Printing Contact in Ascending Order: \n");
        show_ascending(root);
        printf("\n");
        count_asc = 1;
        
    }
    else if(choice == 5)
    {
        printf("\n---------------------------------\n");
        struct node*root = head;
        if(root == NULL)
        {
            printf("\n No Contacts are there to show!");
            goto menu;
        }
        printf("Printing Contact in Descending Order: \n");
        show_descending(root);
        printf("\n");
        count_desc = 1;
        
    }
    else if(choice == 6)
    {
        printf("\n-------------------------------------------------------------\n");
        printf("\nContact Dictinary Signing off! Don't Forget to save Contacts!\n");
        printf("\n-------------------------------------------------------------\n");
        exit(0);
    }
    else
    {
        printf("\n---------------------------------\n");
        printf("Enter the valid option! \n");
    }
    goto menu;
    
    return 0;
}
