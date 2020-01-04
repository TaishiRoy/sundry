#include<iostream>
#include <fstream>
#define MAXFILENAME 100
using namespace std;
int currCount;

struct Node { 
    int key; 
	int minRange, maxrange;
    struct Node *left, *right; 
};


// -------------- HEAP INITIALISATION -----------------------
void hinit(int fileCount)
{
	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
	db = fopen( fn, "w+" );
	fprintf( db, "%2d\n" , 0 );
	for( int i=0; i<32; i++)
	{
		fprintf( db, "       -");
	}
	fclose (db);
	return;
}


// ------------------- SEARCH IN HEAP ---------------------
bool hsearch( int fileCount, int key )
{
	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
	db = fopen( fn, "r" );
	int N;
	fscanf( db, "%d" , &N);	

	//search for a key in file
	for(int i=0; i<N; i++)
	{
		int curr;
		fscanf( db, "%d" , &curr);
		if( curr == key )
		{
			fclose(db);
			return true;
		}
	}
	fclose(db);
	return false;
}


// ---------------------- HEAPIFY (BOTTOM UP) ----------------------------
void heapify( int fileCount, int N )
{
	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);		
	db = fopen( fn, "r+" );
	int parent = (N-1) / 2; 
	int valParent=0;
	int valChild;
	int parentPtr = 3 + (parent*8);
	int childPtr = 3 + ((N)*8);
	fseek( db, parentPtr, SEEK_SET);
	fscanf( db, " %d" , &valParent);
	fseek( db, childPtr, SEEK_SET);
	fscanf( db, " %d" , &valChild);
	if(valParent > valChild)
	{
		fseek( db,childPtr, SEEK_SET);
		snprintf(fn, MAXFILENAME, "%8d", valParent);
		fflush(db);
		
		fputs( fn, db);
		fflush(db);
		fseek( db,parentPtr, SEEK_SET);
		fflush(db);
		snprintf(fn, MAXFILENAME, "%8d", valChild);	
		
		fputs( fn, db);
		fflush(db);
		if(parent > 0)
		heapify( fileCount, parent);
	}
	fclose(db);
	return;
  
}


// -------------------------- HEAPIFY (TOP DOWN) ----------------------
void heapify_topdown( int fileCount, int N, int parent )
{

	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);		
	db = fopen( fn, "r+" );
	int min = parent, valMin, valChild1, valChild2, valParent;
	int child1 = (parent*2);
	int child2 = child1 + 1;
	fseek( db, 3+((min-1)*8), SEEK_SET);
	fscanf( db, " %d" , &valMin);
	valParent = valMin;
	fseek( db, 3+((child1-1)*8), SEEK_SET);
	fscanf( db, " %d" , &valChild1);
	fseek( db, 3+((child2-1)*8), SEEK_SET);
	fscanf( db, " %d" , &valChild2);
	if((child1 <= N) && ( valChild1 < valMin ))
	{
		min = child1;
		valMin = valChild1;
	} 

	if((child2 <= N) && ( valChild2 < valMin ))
	{
		min = child2;
		valMin = valChild2;
	} 
	
	if( min!=parent )
	{
		fseek( db,3+((parent-1)*8), SEEK_SET);
		snprintf(fn, MAXFILENAME, "%8d", valMin);
		fflush(db);
		fputs( fn, db);
		fflush(db);
		fseek( db, 3+((min-1)*8), SEEK_SET);
		fflush(db);
		snprintf(fn, MAXFILENAME, "%8d", valParent);	
		fputs( fn, db);
		
		fclose(db);
		heapify_topdown( fileCount, N, min);
	}
	return;
  
}


// ------------------------ INSERT IN HEAP -----------------------
void hinsert( int fileCount, int key )
{
	// do hsearch first
	if(!hsearch(fileCount, key))
	{
		
		// insert key in db
		char fn[MAXFILENAME+1];
		FILE* db;
		snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
		db = fopen( fn, "r+" );
		int N;
		fscanf( db, "%d" , &N);	
		
		if( N<32)
		{
			fseek( db, 0, SEEK_SET );
			snprintf(fn, MAXFILENAME, "%2d\n", ++N);
			fflush(db);
			fputs( fn, db);
			fseek( db, ((N-1)*8) , SEEK_CUR );
			fprintf( db, "%8d", key );
			fclose(db);
			if(N>1)
				heapify( fileCount, N-1 );
		}	
	}
	return; 
}



// -------------------- FIND MIN ELEMENT OF HEAP -----------------------
int hfindmin( int fileCount )
{
	// return min key 
	int min;
	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
	db = fopen( fn, "r" );
	fseek( db, 3, SEEK_SET );
	fscanf( db, "%d" , &min);
	fclose(db);
	return min;
}



// ----------------- DELETE MIN ELEMENT FROM HEAP -------------------
void hdelmin( int fileCount )
{
	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
	db = fopen( fn, "r+" );
	int N;
	fscanf( db, "%d" , &N);	
	if(N==0)
	{
		cout << "empty heap detected"<< endl;
		fclose(db);
		return;
	}	
	int last;
	fseek( db, 3+(N-1)*8, SEEK_SET);
	fscanf( db, "%d" , &last);
	fseek( db, 3, SEEK_SET);
	fflush(db);
	snprintf(fn, MAXFILENAME, "%8d", last);
	fputs( fn, db);

	fseek( db, 0, SEEK_SET);
	fflush(db);
	snprintf(fn, MAXFILENAME, "%2d", (N-1));
	fputs( fn, db);
	heapify_topdown( fileCount, N-1, 1);
	
	fseek( db, (3+(N-1)*8), SEEK_SET);
	fflush(db);
	snprintf(fn, MAXFILENAME, "       -");
	fputs( fn, db);
	fclose(db);
	
	return;
}


// -------------------- FIND MAX ELEMENT OF HEAP -----------------------
int hfindmax( int fileCount )
{
	// return max key 
	int max=0,N;
	char fn[MAXFILENAME+1];
	FILE* db;
	snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
	db = fopen( fn, "r" );
	fseek( db, 0, SEEK_SET );
	fscanf( db, "%d" , &N);
	fseek( db, (3 + (N/2)*8), SEEK_SET );
	for(int i=0; i<=(N/2); i++)
	{
		int temp;
		fscanf( db, "%d" , &temp);
		max = temp>max ? temp : max;
	}
	fclose(db);
	return max;

}


// ------------------- DATABASE INITIALIZATION -------------------------
Node* dbinit(int fileCount)
{
	Node* root = new Node;
	root->left = NULL;
	root->right = NULL;
	root->key = fileCount;
	hinit(fileCount);
	root->minRange = 9999999;
	root->maxrange = -9999999;
	return root;
}



// -------------------- SEARCH IN DATABASE -----------------------------
bool dbsearch(Node* root, int query)
{
	if( root==NULL )	return false;
	int min = root->minRange;
	int max = root->maxrange;
	int res;
	if ( query>=min && query<=max )
	{
		if( root->left == NULL && root->right == NULL)
			return hsearch(root->key, query);
				
		if( query<=(root->left->maxrange) && root->left != NULL )
			return dbsearch( root->left , query);

		if( query>=(root->right->minRange) && root->right != NULL)
			return dbsearch( root->right , query);
	}
	return false;
}


// --------------------- INSERT IN DATABASE ---------------------------------
Node* dbinsert(Node** root, int element)
{

	if( (*root)==NULL )	return *root;
	if(!dbsearch((*root), element))
	{
		if( (*root)->left == NULL && (*root)->right == NULL)
		{
			char fn[MAXFILENAME+1];
			FILE* db;
			int N;

			int fileCount = (*root)->key;
			snprintf(fn, MAXFILENAME, "%07d.dat", fileCount);
			db = fopen( fn, "r" );
			fseek( db, 0, SEEK_SET );
			fscanf( db, "%d" , &N);
			fclose(db);
			if(N==32)
			{
				//create new node
				Node* lesserNode = dbinit(++currCount);
				lesserNode->left = NULL;
				lesserNode->right = NULL;
				lesserNode->key = currCount;
				Node* greaterNode = new Node();
				greaterNode->left = NULL;
				greaterNode->right = NULL;
				greaterNode->key = fileCount;
						

				(*root)->left = lesserNode;
				(*root)->right = greaterNode;
				(*root)->key = -9999999;
				


				//copy paste first half into new file
				for( int i=0; i<(N/2); i++ )
				{
					int tempMin = hfindmin(fileCount);
					hdelmin(fileCount);
					hinsert(currCount,tempMin);
				}

				lesserNode->minRange = hfindmin(currCount);
				lesserNode->maxrange = hfindmax(currCount);
				greaterNode->minRange = hfindmin(fileCount);
				greaterNode->maxrange = hfindmax(fileCount);

				if( element<=lesserNode->maxrange )
				{
					hinsert(currCount, element);
					lesserNode->minRange = hfindmin(currCount);
					lesserNode->maxrange = hfindmax(currCount);
				}

				else
				{
					hinsert(fileCount, element);
					greaterNode->minRange = hfindmin(fileCount);
					greaterNode->maxrange = hfindmax(fileCount);
				}

				(*root)->minRange = (*root)->minRange<=lesserNode->minRange ? (*root)->minRange : lesserNode->minRange;
				(*root)->maxrange = (*root)->maxrange>=greaterNode->maxrange ? (*root)->maxrange : greaterNode->maxrange;
				return *root;

			}
			else
			{
				hinsert(fileCount, element);
				(*root)->minRange = (*root)->minRange<hfindmin(fileCount) ? (*root)->minRange : hfindmin(fileCount);
				(*root)->maxrange = (*root)->maxrange>hfindmax(fileCount) ? (*root)->maxrange : hfindmax(fileCount);
				return *root;
			}
		}

		if( element <= (*root)->left->maxrange)
		{
			Node* next = dbinsert(&((*root)->left), element);
			(*root)->minRange = (*root)->minRange<(*root)->left->minRange ? (*root)->minRange : (*root)->left->minRange;
			(*root)->maxrange = (*root)->maxrange>(*root)->left->maxrange ? (*root)->maxrange : (*root)->left->maxrange;
			return *root;
		}
		else
		{
			Node* next =  dbinsert(&((*root)->right), element);
			(*root)->minRange = (*root)->minRange<(*root)->right->minRange ? (*root)->minRange : (*root)->right->minRange;
			(*root)->maxrange = (*root)->maxrange>(*root)->right->maxrange ? (*root)->maxrange : (*root)->right->maxrange;
			return *root;
		}

	}

	return *root;
}


// ----------------- OUTPUTS INORDER TRAVERSAL OF BINARY TREE ---------------
void printInorder(Node* node, int cond) 
{ 
    if (node == NULL) 
        return; 

    printInorder(node->left, cond); 
	
	if(node->left == NULL && node->right == NULL)
	{
		if(cond == 1)
			cout << node->minRange << " " << node->maxrange << " "; 
		else
		{
			cout << hfindmin(node->key) << " " << hfindmax(node->key) << " "; 
		}
	}
  
    printInorder(node->right, cond); 
	return;
} 



// -------------------- HEIGHT OF BINARY TREE ----------------------------
int getHeight(Node* node) 
{ 
	int countL=0, countR=0;
    if (node == NULL) 
        return -1; 

    countL= getHeight(node->left); 
  
    countR=getHeight(node->right); 
	return countL>countR?(countL+1):(countR+1);
} 



// -------------------- BINARY TREE VISUAL OUTPUT --------------------------------
void travelTree(Node* node, int num) 
{ 
    if (node == NULL) 
        return; 

	for(int i=0; i<3-getHeight(node)+num; i++)
	 cout << "\t";
	

	cout << "+---Range = [" << node->minRange << "," << node->maxrange << "], File: " ;
	if(node->key < 0)
	cout << "None" << endl;
	else
	cout << "B1/000000" << node->key << ".dat" << endl;
	
    travelTree(node->left, num);

    travelTree(node->right, num); 
	return;
} 


// ----------------- OUTPUTS PREORDER TRAVERSAL OF BINARY TREE ---------------
void printPreorder(Node* node) 
{ 
    if (node == NULL) 
        return; 

	cout << node->minRange << " "; 

    printPreorder(node->left); 
  
    printPreorder(node->right); 
	
	return;
} 



// ----------------- OUTPUTS POSTORDER TRAVERSAL OF BINARY TREE ---------------
void printPostorder(Node* node) 
{ 
    if (node == NULL) 
        return; 


    printPostorder(node->left); 
  
    printPostorder(node->right); 

	cout << node->maxrange << " ";

	return;
} 


// --------------------------- NODE COUNT ----------------------------
int countTree(Node* node) 
{ 
	int count = 0;
    if (node == NULL) 
        return 0; 

    count+= countTree(node->left); 
	
	count++;
  
    count+=countTree(node->right); 
	return count;
} 





int main()
{
	int arr[999];
	Node* root = new Node();
	root = dbinit(currCount);


	
	// input
	int N;
	cout << "n_ins = ";
	cin >> N;
	cout << "Insert keys : " << endl;
	for( int i=0; i<N; i++)
	{
		int key;
		cin >> arr[i];
	}

	cout << "\n Enter two keys for search :" << endl;
	int key1, key2;
	cin >> key1 >> key2;





	for( int i =0; i<N; i++)
	{
		root = dbinsert(&root, arr[i]);
	}

	cout << "\n+++ Inorder listing of min and max values of leaves:" <<  endl;
	printInorder(root,1);
	cout << endl;

	cout << "\n+++ Inorder listing of min and max values read from files:" <<  endl;
	printInorder(root,2);
	cout << endl;


	cout << "\n+++ Sorted listing of min values at all nodes:" <<  endl;
	printPreorder(root);
	cout << endl;

	cout << "\n+++ Sorted listing of max values at all nodes:" <<  endl;
	printPostorder(root);
	cout << endl;

	cout << "\n+++ Statistics of the BST:" <<  endl;
	cout << "\tNumber of nodes = " << countTree(root)  << "\n\tNumber of leaves = " << currCount+1 << "\n\tHeight = " << getHeight(root) << endl;

	cout << "\n+++ The BST:"<< endl;
	cout << "Range = [" << root->minRange << "," << root->maxrange << "], File: " ;
	if(root->key < 0)
	cout << "None" << endl;
	else
	cout << "B1/000000" << root->key << ".dat" << endl;
	travelTree(root->left,0);
	travelTree(root->right,1);

	
	cout << "\n+++ Search results\n\tsearch(" << key1 << "): ";

	int res = dbsearch(root,key1);
	if(res!=0)	cout << "PRESENT" << endl;
	else	cout << "ABSENT" << endl;

	cout << "\tsearch(" << key2 << "): ";
	res = dbsearch(root,key2);
	if(res!=0)	cout << "PRESENT" << endl;
	else	cout << "ABSENT" << endl;
	return 0;
}

