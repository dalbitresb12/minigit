#pragma once
#include <iostream>
#include <functional>

template <typename T>
struct Node{
  Node* left;
  Node* right;
  T value;
  int height;
  Node(T v) : value(v){}
};

template <class T>
class AVL{
  Node<T>* root;
  std::function<bool(T, T)> fn;
public:
  AVL(std::function<bool(T, T)> f){
    fn = f;
    root = nullptr;
  }
  void Insert(T v){
    Insert(v, root);
  }
  bool Contains(T v){
    return Contains(v, root);
  }
  void Show(){
    Show(root);
  }
private:
  void Insert(T v, Node<T>*& n){
    if (n == nullptr){
      n = new Node<T>(v);
    } else if (fn(v, n->value)){
      Insert(v, n->left);
    } else {
      Insert(v, n->right);
    }
    Balance(n);
  }
  bool Contains(T v, Node<T>*& n){
    if (n == nullptr) return false;
    if (v == n->value) return true;
    else {
      if (v < n->value && n->left != nullptr){
        return Contains(v, n->left);
      } else if (v > n->value && n->right != nullptr){
        return Contains(v, n->right);
      } else {
        return false;
      }
    } 
  }
  void Balance(Node<T>*& n){
    int rightHeight = Height(n->right);
    int leftHeight = Height(n->left);
    if (rightHeight - leftHeight > 1){
      int rrHeight = Height(n->right->right);
      int rlHeight = Height(n->right->left);
      if (rlHeight > rrHeight) HoraryRotation(n->right);
      AntihoraryRotation(n);
    } else if (leftHeight - rightHeight > 1){
      int llHeight = Height(n->left->left);
      int lrHeight = Height(n->left->right);
      if (lrHeight > llHeight) AntihoraryRotation(n->left);
      HoraryRotation(n);
    } else UpdateHeight(n);

  }
  void HoraryRotation(Node<T>*& n){
    Node<T>* aux = n->left;
    n->left = aux->right; UpdateHeight(n);
    aux->right = n; UpdateHeight(aux);
    n = aux;
  }
  void AntihoraryRotation(Node<T>*& n){
    Node<T>* aux = n->right;
    n->right = aux->left; UpdateHeight(n);
    aux->left = n; UpdateHeight(aux);
    n = aux;
  }
  void UpdateHeight(Node<T>*& n){
    if (n != nullptr){
      int rightHeight = Height(n->right);
      int leftHeight = Height(n->left);
      n->height = std::max(rightHeight, leftHeight) + 1;
    }
  }
  int Height(Node<T>* n){
    if (n == nullptr) return -1;
    return n->height;
  }
  void Show(Node<T>* n){
    if (n == nullptr) return;
    Show(n->left);
    std::cout << n->value << "->";
    Show(n->right);
  }
};
