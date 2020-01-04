#include<iostream>
using namespace std;

class ListNode
{
    public:
    int first,second,dir;
    ListNode* next;
};

class TreeNode
{
    public:
    int first, second;
    TreeNode* left, *right;
};


// -------------------- RETURNS GCD OF TWO INTEGERS --------------------------
int gcd(int a, int b)
{
    if(a==b)    return a;
    if(a==0)    return b;
    if(b==0)    return a;
    if(a>b) return gcd(a-b,b);
    if(b>a) return gcd(a,b-a);
}

void printList(ListNode* n) 
{ 
    while (n != NULL) { 
        cout << n->first << " " << n->second << " " << n->dir<<  endl; 
        n = n->next; 
    } 
} 



// ---------------------- PREORDER TRAVERSAL ------------------------
void preorderTree(TreeNode* n)
{
    if( n == NULL)  return;
    cout << "(" << n->first << "," << n->second << ")  ";
    preorderTree(n->left);
    preorderTree(n->right);
}


// ------------------------ INORDER TRAVERSAL ------------------------
void inorderTree(TreeNode* n)
{
    if( n == NULL)  return;
    inorderTree(n->left);
    cout << "(" << n->first << "," << n->second << ")  ";
    inorderTree(n->right);
}



int findMax( TreeNode* n, int max)
{
    if( n == NULL)  return max;
    max = max > n->first ? max : n->first;
    max = max > findMax(n->left, max) ? max : findMax(n->left, max);
    max = max > findMax(n->right, max) ? max : findMax(n->right, max);
    return max;
}

bool isEmpty(TreeNode** arr, int size)
{
    for( int i=0; i<size; i++)
    {
        if(arr[i]!=NULL)
        {
            if( arr[i]->first != 0)
            {
                return false;
            }
        }    
    }
    return true;
}

void freeList(TreeNode* head)
{
   TreeNode* tmp;

   while (head != NULL)
    {
       tmp = head;
       if(head->left!=NULL) head = head->left;
       else
       head = head->right;
       free(tmp);
    }

}


/*
void lexorderTree(TreeNode* n)
{

    int max = findMax(n, -99);
    TreeNode** arrList = new TreeNode*[max];
    for(int i = 0; i < max; ++i) 
    {
        arrList[i] = new TreeNode;
    }
    for( int i=0 ; i<max; i++)
    {
        arrList[i]->left = NULL;
        arrList[i]->right = NULL;
        arrList[i]->first = 0;
    }
    arrList[0] = n;
    while(!isEmpty(arrList, max))
    {
        for( int i=0; i<max; i++)
        {
            if(arrList[i]->left == NULL && arrList[i]->right == NULL && arrList[i]->first!= 0)
            {
                arrList[i]->first = 0;
            }
            if(arrList[i]->left != NULL)   
            {
                arrList[i+arrList[i]->second] = arrList[i]->left;
            }
            if(arrList[i]->right != NULL)
            {
                arrList[i] = arrList[i]->right;
                cout << "(" << arrList[i]->first << "," << arrList[i]->second << ")  ";
                break;
            }
            else
            {
                arrList[i]->right = NULL;
                arrList[i]->left = NULL;
                arrList[i]->first = 0;
            }
            
        }
    }
    for( int i =0; i<max; i++)
    {
        freeList(arrList[i]);
    }
    
}
*/

int countNodes(TreeNode* n)
{
    int count = 1;
    if (n->left != NULL) {
       count += countNodes(n->left);
    }
    if (n->right != NULL) {
        count += countNodes(n->right);
    }
    return count;
}

ListNode* reverseList(ListNode** head)
{
    ListNode* curr = *head;
    ListNode* prev = NULL;
    ListNode* next = curr->next;

    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

ListNode* getRecursiveList(int a,int b)
{
    ListNode* newNode = new ListNode();
    newNode->first = a;
    newNode->second = b;
    newNode->dir = -1;
    if(a==b)    return newNode;
    if(a>b) 
    {
        newNode->dir = 0;
        newNode->next = getRecursiveList(a-b, b);
        return newNode;
    }
    else
    {
        newNode->dir = 1;
        newNode->next = getRecursiveList(a, b-a);
        return newNode;
    }
    
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< S E A R C H >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool tsearch( int a, int b, TreeNode* treeHead)
{
    if( gcd(a, b) != 1)  return false;
    ListNode* newNode = new ListNode();
    newNode  = getRecursiveList(a,b);
    ListNode* listHead = reverseList(&newNode);
    while(1)
    {
        if(treeHead->first == a && treeHead->second == b)  return true;
        if(listHead->first != treeHead->first)  return false;
        if(listHead->second != treeHead->second)    return false;
        if(listHead->next == NULL)  return false;
        listHead = listHead->next;
        if(listHead->dir == 0)
        {
            if(treeHead->left == NULL)  return false;
            treeHead = treeHead->left;
        }  
        if(listHead->dir == 1)
        {
            if(treeHead->right == NULL)  return false;
            treeHead = treeHead->right;
        }
    }


    return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< I N S E R T >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool tinsert( int a, int b,TreeNode* treeHead)
{

    if( gcd(a,b) != 1)   return false;
    if(tsearch(a,b, treeHead))    return true;
    ListNode* newNode = new ListNode();
    newNode  = getRecursiveList(a,b);
    ListNode* listHead = reverseList(&newNode); 
    
    TreeNode* temp = treeHead;
    while(1)
    {
        if(listHead->first != treeHead->first)  break;
        if(listHead->second != treeHead->second)    break;
        if(listHead->next == NULL)  break;
        ListNode* prev = listHead;
        listHead = listHead->next;

        if(listHead->dir == 0)
        {
            if( treeHead->left == NULL)
            {
                listHead = prev;
                break;
            }
            treeHead = treeHead->left;
        }  
        if(listHead->dir == 1) 
        {
            if( treeHead->right == NULL)
            {
                listHead = prev;
                break;
            }
            treeHead = treeHead->right;
        }

    }
    while(1)
    {
        if(listHead->next == NULL)  return true;
        listHead = listHead->next;
        if(listHead->dir == 0)
        {
            TreeNode* newNode = new TreeNode();
            treeHead->left = newNode;
            treeHead->left->first = listHead->first;
            treeHead->left->second = listHead->second;
            treeHead = treeHead->left;
        } 
        if(listHead->dir == 1) 
        {
            TreeNode* newNode = new TreeNode();
            treeHead->right = newNode;
            treeHead->right->first = listHead->first;
            treeHead->right->second = listHead->second;
            treeHead = treeHead->right;
        } 
    }
    return true;

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< D E L E T E >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool tdelete( int a, int b,TreeNode** treeHead)
{
    if(!tsearch(a,b, *treeHead))    return false;
    ListNode* newNode = new ListNode();
    newNode  = getRecursiveList(a,b);
    ListNode* listHead = reverseList(&newNode);
    
    TreeNode* temp = *treeHead;
    while(1)
    {
        if(listHead->first != (*treeHead)->first)  break;
        if(listHead->second != (*treeHead)->second)    break;
        if(listHead->next->next == NULL) 
        {
            if(listHead->next->dir == 0)    (*treeHead)->left = NULL;
            else    (*treeHead)->right = NULL;
            break;
        }
        
        listHead = listHead->next;


        if(listHead->dir == 0)
        {
            if( (*treeHead)->left == NULL)  break;
            (*treeHead) = (*treeHead)->left;
        }  
        if(listHead->dir == 1) 
        {
            if( (*treeHead)->right == NULL) break;
            (*treeHead) = (*treeHead)->right;
        }
    }
    return true;

}

int main()
{
    TreeNode* treeHead = new TreeNode();
    treeHead->first = 1;
    treeHead->second = 1;
    TreeNode* treeStore = treeHead;
    int nin,ndel,a1,a2,b1,b2;
    cout << "\nnins = ";
    cin >> nin ;
    cout << "\nndel = ";
    cin >> ndel ;
    int ins[nin+1][2], del[ndel+1][2];
    for(int i=0; i<nin; i++)
    {
        cout << "\nenter pair for insertion:";
        cin >> ins[i][0] >> ins[i][1];
    };

    cout << "\nenter pair for search:";
    cin >> a1 >> b1;
    cout << "\nenter pair for search:";
    cin >> a2 >> b2;

    for(int i=0; i<ndel; i++)
    {
        cout << "\nenter pair for deletion:";
        cin >> del[i][0] >> del[i][1];
    };

    cout << "OUTPUT::::"<< endl;
    cout << "nins = " << nin << endl;
    cout << "ndel = " << ndel << endl;

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<

    "+++ INSERTION PHASE\n" <<
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    for(int i=0; i<nin; i++)
    {
        int before = countNodes(treeHead);
        tinsert(ins[i][0], ins[i][1], treeHead);
        int after = countNodes(treeHead);
        cout << "(" << ins[i][0] << "," << ins[i][1] << "): " << after-before << " nodes added" << endl;
    };

    cout << "\n+++ Number of nodes = " << countNodes(treeHead) << endl;

    cout << "\n\n+++ Preorder" << endl;
    preorderTree(treeHead);
    cout << endl;

    cout << "\n\n+++ Inorder" << endl;
    inorderTree(treeHead);
    cout << endl;

    /*
    cout << "\n\n+++ Lexorder" << endl;
    preorderTree(treeHead);
    cout << endl;
    */

    cout << "\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
    "+++ SEARCH PHASE\n" <<
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "(" << a1 << "," << b1 << ") :";
    if(tsearch(a1,b1, treeHead))    cout << "Search Successful" << endl;
    else cout << "Search Failed" << endl;

    cout << "(" << a2 << "," << b2 << ") :";
    if(tsearch(a2,b2, treeHead))    cout << "Search Successful" << endl;
    else cout << "Search Failed" << endl;

    cout << "\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
    "+++ DELETION PHASE\n" <<
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    for(int i=0; i<ndel; i++)
    {
        int before = countNodes(treeStore);
        TreeNode* temp = treeStore;
        tdelete(del[i][0], del[i][1], &temp);
        int after = countNodes(treeStore);
        cout << "(" << del[i][0] << "," << del[i][1] << "): " << before-after << " nodes deleted" << endl;
    };

    cout << "\n+++ Number of nodes = " << countNodes(treeStore) << endl;

    cout << "\n\n+++ Preorder" << endl;
    preorderTree(treeStore);
    cout << endl;

    cout << "\n\n+++ Inorder" << endl;
    inorderTree(treeStore);
    cout << endl;

    /*
    cout << "\n\n+++ Lexorder" << endl;
    lexorderTree(treeHead);
    cout << endl;
    */



    return 1;
}
