#include<bits/stdc++.h>
using namespace std; 
#include"binaryTreeNode.h"



char subConvert(int s)
{
    return s+48;
}

string convert(int s)
{
    string i="";
    
    while(s>0)
    {
        char current=subConvert(s%10);
        s/=10;
        string temp="";
        temp+=current;
        for(int j=0;j<i.length();j++)
            temp+=i[j];
        i=temp;
    }
    
    
    return i;
}

int heightBT(binaryTreeNode<int>* root)
{
    if(root==NULL)
    {
        return 0;
    }
    
    int height=0;
    int compare=0;
    compare=heightBT(root->left);
    if(compare>height)
        height=compare;
    compare=heightBT(root->right);
    if(compare>height)
        height=compare;
    return height+1;
}

void printTree(binaryTreeNode<int>* root)
{
    binaryTreeNode<int>* current=root;
    queue<binaryTreeNode<int>*> pendingNodes;
    pendingNodes.push(root);
    int height=heightBT(root);
    int total=pow(2,height+1)-3;
    
    string** treeMatrix=new string*[height];
    for(int i=0;i<height;i++)
    {
        treeMatrix[i]=new string[total];
        for(int j=0;j<total;j++)
        {
            treeMatrix[i][j]=" ";
        }
        
    }
    
    binaryTreeNode<int>* dummy=new binaryTreeNode<int>(0);
    int rowStart=total/2;
    int col=0;
    int prev=0;
    for(int i=0;i<height;i++)
    {   
        col=rowStart;
        for(int j=0;j<pow(2,i);j++)
        {
           binaryTreeNode<int>* node=pendingNodes.front();
           pendingNodes.pop();
           if(node==dummy)treeMatrix[i][col]='x';
           else treeMatrix[i][col]=convert(node->data);
           if(node->left==NULL)pendingNodes.push(dummy);
           else pendingNodes.push(node->left);
           if(node->right==NULL)pendingNodes.push(dummy);
           else pendingNodes.push(node->right);
           col+=pow(2,height-i+1); 
        }
        rowStart=rowStart-pow(2,height-i-1);
    }
    
    cout<<"************************";
    cout<<endl;
    
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<total;j++)
            cout<<treeMatrix[i][j];
        cout<<endl;
    }
    cout<<endl;
    cout<<"************************";
    
}


binaryTreeNode<int>* takeInputLevelWise()
{
    int rootData;
    cout<<"Please enter root data:";
    cin>>rootData;
    binaryTreeNode<int>* root=new binaryTreeNode<int>(rootData);
    queue<binaryTreeNode<int>*> pendingNodes;
    pendingNodes.push(root);
    while(!pendingNodes.empty())
    {
        binaryTreeNode<int>* next=pendingNodes.front();
        pendingNodes.pop();
        int leftChild,rightChild;
        cout<<"Enter left child of "<<next->data<<":";
        cin>>leftChild;
        if(leftChild!=-1)
        {
            binaryTreeNode<int>* node=new binaryTreeNode<int>(leftChild);
            next->left=node;
            pendingNodes.push(node);
        }
        cout<<"Enter right child of "<<next->data<<":";
        cin>>rightChild;
        if(rightChild!=-1)
        {
            binaryTreeNode<int>* node=new binaryTreeNode<int>(rightChild);
            next->right=node;
            pendingNodes.push(node);
        }
    }
    
    return root;
}

bool mirror(binaryTreeNode<int>* root1,binaryTreeNode<int>* root2)
{
    if(root1->data!=root2->data)
    {
        return false;
    }

    bool con1=true;
    bool con2=true;
    if(root1->left==NULL && root2->right==NULL)con1=true;
    else if(root1->left!=NULL && root2->right!=NULL)
    con1=mirror(root1->left,root2->right);
    else con1=false;
    if(root2->right==NULL && root2->left==NULL)con2=true;
    else if(root1->right!=NULL && root2->left!=NULL)
    con2=mirror(root1->right,root2->left);
    else con2=false;
    return con1&&con2;
    
    
}

int main()
{
    binaryTreeNode<int>* root1=takeInputLevelWise();
    //binaryTreeNode<int>* root2=takeInputLevelWise();
    printTree(root1);
    //printTree(root2);
    cout<<endl;
    //bool ans=mirror(root1,root2);
    //cout<<ans;
}

