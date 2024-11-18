#include <iostream>
using namespace std;
struct Node {
	char c[100];
	Node* next;
};
typedef Node* PNode;
struct List {
	PNode Firstword;
	PNode Lastword;
};
typedef List* PList;
//khoi tao
void List_init (PList list){
	list->Firstword = list->Lastword = NULL;
}
//tao node
PNode CreateNode(const char* c) {
	PNode newNode = new Node;
	int i = 0;
	while (c[i] != '\0' && i < sizeof(c) / 2) {
		newNode->c[i] = c[i];
		i++;
	}
	newNode->c[i] = '\0';
	newNode->next = NULL;
	return newNode;
}
// gan node
void AddNode(PList l, PNode n) {
	if (l->Firstword == NULL && l->Lastword == NULL) l->Firstword = l->Lastword = n;
	else {
		l->Lastword->next = n;
		l->Lastword = n;
	}
}
//gan node vao danh sach
void AttachList(PList l, const char* c) {
	Node* pDT = CreateNode(c);
	if (pDT == NULL) return;
	AddNode(l, pDT);
}
//nhap tu
void InputWord(PList l) {
    char sentence[256];
	cout << "nhap cau: ";
	cin.getline(sentence, 256);
	int start = 0;
	for (int i = 0; sentence[i] != '\0'; i++) {
		if (sentence[i] == ' ' || sentence[i + 1] == '\0') {
			int end = (sentence[i] == ' ') ? i : i + 1;
			char word[50];
			int length = end - start;
			if (length > 0 && length < 50) {
				for (int j = 0; j < length; j++) {
					word[j] = sentence[start + j];
				}
				word[length] = '\0';
				AttachList(l, word);
			}
			start = i + 1;
		}
	}

}
//so sanh hai tu
bool CompareWords(const char* c1, const char* c2) {
	int i = 0;
	while (c1[i] != '\0' && c2[i] != '\0') {
		if (c1[i] != c2[i]) {
			return false;
		}
		i++;
	}
	return c1[i] == '\0' && c2[i] == '\0';
}
//xoa node trung
void DelSimNode(PList l) {
    if (l->Firstword == nullptr) {
        cout << "Danh sach rong" << endl;
        return;
    }
    PNode current = l->Firstword;
    while (current != NULL && current->next != NULL) {
        PNode nextNode = current->next;

        if (CompareWords(current->c, nextNode->c)) {
            current->next = nextNode->next;
            delete nextNode;
        } else {
            current = current->next;
        }
    }
}
// Xuat cau
void PrintWord(PList l) {
	PNode ch = l->Firstword;
	while (ch != NULL) {
		cout << ch->c << " ";
		ch = ch->next;
	}

}
//tu xuat hien nhieu nhat
void MostFrequentWord1(PList l) {
	const char* mostFrequentWords[100]; 
	int CountW = 0;                 
	int max = 0;

	PNode current = l->Firstword;

	while (current != NULL) {
		int count = 1;
		PNode compare = current->next;
		while (compare != NULL) {
			if (CompareWords(current->c, compare->c)) {
				count++;
			}
			compare = compare->next;
		}
		if (count > max) {
			max = count;
			CountW = 0; 
			mostFrequentWords[CountW++] = current->c;
		}
		else if (count == max) {
			mostFrequentWords[CountW++] = current->c;
		}

		current = current->next;
	}
	cout << "Cac tu xuat hien nhieu nhat (" << max << " lan):" << endl;
	for (int i = 0; i < CountW; ++i) {
		bool isDuplicate = false;
		for (int j = 0; j < i; ++j) {
			if (CompareWords(mostFrequentWords[i], mostFrequentWords[j])) {
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate) {
			cout << mostFrequentWords[i] << std::endl;
		}
	}
}
//Dem so tu vung xuat hien
int CountUniqueWords(PList l) {
	PNode NodeCheck = l->Firstword;
	int count = 0;
	while (NodeCheck != NULL) {
		bool unique = true;
		PNode NodeDuyet = l->Firstword;
		while (NodeDuyet != NodeCheck) {
			if (CompareWords(NodeDuyet->c, NodeCheck->c)) {
				unique = false;
				break;
			}
			NodeDuyet = NodeDuyet->next;
		}
		if (unique) count++;
		NodeCheck = NodeCheck->next;
	}
	return count;
}
int main() {
	List Sentence;
	List_init(&Sentence);
	InputWord(&Sentence);
	cout << "cau sau khi xoa tu lay: ";
	DelSimNode(&Sentence);
	PrintWord(&Sentence);
	cout << endl;
	MostFrequentWord1(&Sentence);
	cout << "So tu vung xuat hien la: " << CountUniqueWords(&Sentence);
}


