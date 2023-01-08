
#ifndef LIST_HEADER
#define LIST_HEADER

typedef struct Node Node;
typedef struct List List;
struct Node{
   Node* prox;
   void** points;
   //int fig2d;
   //float color[3];
   //float thick;
};
struct List{
   int size;
   Node* hdy;
};

Node* crtNode(void** points, int figtype, float color[3], float thick);
void listInit(List** list);
void listInsert(List* list, Node* nod, int pos);
Node* listGetittem(List* list, int pos);
void listClear(List* list);
int listLen(List* list);
void listR(List* list, int pos);
Node* listPop(List* list);

Node* crtNode(void** points, int figtype, float color[3], float thick){
   Node* hdy = (Node*) malloc(sizeof(Node));
   hdy->points = points;
   //hdy->fig2d = figtype;
   //(hdy->color)[0] = color[0]; (hdy->color)[1] = color[1]; (hdy->color)[2] = color[2];
   //hdy->thick = thick ;
   return hdy;
}

void listInit(List** list){
   *list = (List*) malloc(sizeof(List));
   (*list)->hdy = NULL;
   (*list)->size = 0;
}

void listInsert(List* list, Node* nod, int pos){
   if (pos == 0){
      Node* aux = list->hdy;
      list->hdy = nod;
      nod->prox = aux;
   }
   else{
      int i=0;
      Node* ptr;
      ptr = list->hdy;
      while(i<pos-1){
         ptr = ptr->prox;
         i++;
      }
      Node* aux = (Node*) malloc(sizeof(Node));
      aux = ptr->prox;
      ptr->prox = nod;
      nod->prox = aux;
   }
   list->size++;
}

Node* listGetittem(List* list, int pos){
   int i=0;
   Node* ptr = list->hdy;
   while(i<pos){
      ptr = ptr->prox;
      i++;
   }
   return ptr;
}

Node* listPop(List* list){
   if(list->hdy==NULL){
      return NULL;
   }
   Node* ptr;
   ptr = list->hdy;
   Node** hdy = &(list->hdy);
   while((ptr = ptr->prox) != NULL){
      hdy = &((list->hdy)->prox);}; Node* nod = (Node*) malloc(sizeof(Node)); nod = *hdy; (*hdy) = NULL; \
   return nod;
   list->size--;
}

void listR(List* list, int pos){
   if(pos==0 && list->hdy!=NULL){
      Node* ptr = list->hdy;
      list->hdy = list->hdy->prox;
      free(ptr);
   }
   else{
      Node* ptr = list->hdy;
      int i=0;
      while(i<(pos-1)){
         ptr = ptr->prox;
         i++;
      }
      Node* prox = ptr->prox->prox;
      free(ptr->prox);
      ptr->prox = prox;
   }
   list->size--;
}

void listClear(List* list){
   if(list->hdy != NULL){
      Node* ptr, *ptr2;
      ptr = list->hdy->prox;
      ptr2 = ptr;
      list->hdy = NULL;
      while((ptr = ptr2) != NULL){
         ptr2 = ptr2->prox;
         free(ptr);
      }
   }
   list->size = 0;
}
#endif