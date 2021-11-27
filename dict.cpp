#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <queue>
using namespace std;

class node
{
public:
    char word[20];
    char meaning[40];
    node *left, *right;

    node(char *word, char *meaning)
    {
        strcpy(this->word, word);
        strcpy(this->meaning, meaning);
        this->left = this->right = NULL;
    }
};

node *insert(node *root, char *word, char *meaning)
{
    if (root == NULL)
    {
        return new node(word, meaning);
    }
    else
    {
        if (strcmp(root->word, word) < 0)
        {
            root->left = insert(root->left, word, meaning);
        }
        if (strcmp(root->word, word) > 0)
        {
            root->right = insert(root->right, word, meaning);
        }
    }
    return root;
}

void search(node *root, char *word)
{
    if (root == NULL)
    {
        cout << "The word is not found" << endl;
        return;
    }

    if (strcmp(root->word, word) == 0)
    {
        cout << "Word: " << root->word << "\n"
             << "Meaning: " << root->meaning << endl;
    }
    else if (strcmp(root->word, word) < 0)
    {
        search(root->left, word);
    }
    else
    {
        search(root->right, word);
    }
}

void r_inorder(node *root)
{
    if (root)
    {
        r_inorder(root->right);
        cout << root->word << " : " << root->meaning << endl;
        r_inorder(root->left);
    }
}

void level(node *root)
{
    queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        cout << q.front()->word << " ~ " << q.front()->meaning << '\n';
        if (q.front()->left)
            q.push(q.front()->left);
        if (q.front()->right)
            q.push(q.front()->right);
        q.pop();
    }
}

int main()
{
    node *root = NULL;
    ifstream fin("words.txt", ios::in);
    char a[21], b[41];
    while (fin >> a)
    {
        fin.get(b, 40, '\n');
        root = insert(root, a, b);
    }

    int ch = 1;
    cout << "\n---CONCISE OXFORD---" << endl;
    do
    {
        cout << "\n1 Enter a word to search\n";
        cout << "2 Add a word and it's meaning\n";
        cout << "3 Alaphabetically sorted words\n";
        cout << "4 Exit\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            char s[21];
            cin >> s;
            search(root, s);
            break;
        case 2:
            cin >> a;
            cin.get(b, 40, '\n');
            root = insert(root, a, b);
            cout << "Dictionary successfully updated !!\n";
            break;
        case 3:
            r_inorder(root);
            cout << endl;
            break;
        case 4:
            cout << "Thanks for using us!" << endl;
            exit(0);
            break;
        default:
            cout << "Wrong Choice !!" << endl;
            break;
        }
    } while (ch >= 1 && ch <= 4);
    return 0;
}