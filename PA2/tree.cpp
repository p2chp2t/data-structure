#include "tree.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end)
{
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++)
  {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')')
    {
      if (s.back() == '(')
      {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end)
{
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1)
  {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data)
{
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder(int node_value)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *cur;
  findNode(_root, node_value);
  cur = target;
  if (cur == NULL)
  {
    return "error";
  }
  string answer = "";
  in_preOrder(&answer, cur);
  answer.pop_back();
  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder(int node_value)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *cur = NULL;
  findNode(_root, node_value);
  cur = target;
  if (cur == NULL)
  {
    return "error";
  }
  string answer = "";
  in_postOrder(&answer, cur);
  answer.pop_back();
  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder(int node_value)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *cur = NULL;
  findNode(_root, node_value);
  cur = target;
  if (cur == NULL)
  {
    return "error";
  }
  string answer = "";
  in_inOrder(&answer, cur);
  answer.pop_back();
  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *targetNode = NULL;
  findNode(_root, node_value);
  targetNode = target;
  if (targetNode == NULL)
  {
    return -1;
  }
  else
  { // target node가 있는 경우
    cal_depth(_root, node_value, 0);
    return depth;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isReverseComplete()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (_root == NULL)
    return true;
  if (_root->left == NULL && _root->right == NULL)
    return true;
  return isReverseCompleteHelper(_root);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */
void BinaryTree::findNode(Node *node, int value)
{
  if (node->value == value + '0')
    target = node;
  if (node->left != NULL)
    findNode(node->left, value);
  if (node->right != NULL)
    findNode(node->right, value);
}

void BinaryTree::in_preOrder(string *answer, Node *node)
{
  if (node != NULL)
  {
    int buffer = node->value - 48;
    *answer += to_string(buffer);
    *answer += " ";
    in_preOrder(answer, node->left);
    in_preOrder(answer, node->right);
  }
}

void BinaryTree::in_postOrder(string *answer, Node *node)
{
  if (node != NULL)
  {
    in_postOrder(answer, node->left);
    in_postOrder(answer, node->right);
    int buffer = node->value - 48;
    *answer += to_string(buffer);
    *answer += " ";
  }
}

void BinaryTree::in_inOrder(string *answer, Node *node)
{
  if (node != NULL)
  {
    in_inOrder(answer, node->left);
    int buffer = node->value - 48;
    *answer += to_string(buffer);
    *answer += " ";
    in_inOrder(answer, node->right);
  }
}

void BinaryTree::cal_depth(Node *root, int node_value, int tmp)
{
  if (root->value == node_value + '0')
    depth = tmp;
  if (root->left != NULL)
    cal_depth(root->left, node_value, tmp + 1);
  if (root->right != NULL)
    cal_depth(root->right, node_value, tmp + 1);
}

bool BinaryTree::isReverseCompleteHelper(Node *node)
{
  if (node->left == NULL && node->right == NULL)
  {
    return true;
  }
  if (node->left == NULL && node->right != NULL)
  {
    return true;
  }
  if (node->left != NULL && node->right == NULL)
  {
    return false;
  }
  return isReverseCompleteHelper(node->left) &&
         isReverseCompleteHelper(node->right->right) &&
         isReverseCompleteHelper(node->right->left);
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
