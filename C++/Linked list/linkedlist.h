#include <sstream>

template <typename T>
class linkedlist {
public:
    linkedlist()
        : head(nullptr), tail(nullptr), length(0)
    {
    }
    ~linkedlist()
    {
        dl_node* np;
        for (np = head; head; np = head)
        {
            head = head->next;
            delete np;
        }
    }
    struct dl_node {
        dl_node(const T& data, dl_node* next = nullptr, dl_node* prev = nullptr)
            : data(data), next(next), prev(prev)
        {
        }
        dl_node(T&& data, dl_node* next = nullptr, dl_node* prev = nullptr)
            : data(data), next(next), prev(prev)
        {
        }
        ~dl_node()
        {
        }
        dl_node* next;
        dl_node* prev;
        T data;
    };

    void push_top(const T& dane) {
        auto nowa_glowa = new dl_node(dane);
        if (head) {
            head->prev = nowa_glowa;
            nowa_glowa->nast = head;
            head = nowa_glowa;
        }
        else {
            tail = head = nowa_glowa;
        }
        ++length;
    }

    void push_bot(const T& dane) {
        auto nowy_ogon = new dl_node(dane);
        if (tail) {
            tail->next = nowy_ogon;
            nowy_ogon->prev = tail;
            tail = nowy_ogon;
        }
        else {
            head = tail = nowy_ogon;
        }
        ++length;
    }
    void clear_top() {
        dl_node* np;
        if (head) {
            np = head;
            head = head->next;
            if (!head) tail = nullptr;
            else head->prev = nullptr;
            delete np;
            --length;
        }

    }

    void clear_bot() {
        dl_node* np;
        if (tail) {
            np = tail;
            tail = tail->prev;
            if (!tail) head = nullptr;
            else tail->next = nullptr;
            delete np;
            np = nullptr;
            --length;
        }
    }
    dl_node* search_dl(const T& el) {
        dl_node* np = head;
        while (np != nullptr) {
            if (np->data == el) {
                return (np);
            }
            np = np->next;
        } return nullptr;
    }
    T ind(const unsigned int a) {
        dl_node* np = head;
        for (int i = 0; i < a; i++) {
            np = np->next;
        }
        return np->data;
    }
    int index_int(const T& el) {
        int indeks = 0;
        dl_node* np = head;
        while (np != nullptr) {
            if (np->data == el) {
                return(indeks);
            }
            np = np->next;
            indeks++;
        }
        return(-1);
    }
    bool search_del(const T& n) {
        dl_node* tmp = search_dl(n);
        return(clear(tmp->data));
    }
    void insertAfter(dl_node* p, const T& data) {
        if (p == nullptr) {
            throw std::runtime_error("NULL");
        }
        if (tail == p) push_bot(data);
        else {
            dl_node* new_dlnode = new dl_node(data);
            new_dlnode->data = data;
            new_dlnode->next = p->next;
            new_dlnode->prev = p;
            p->next = new_dlnode;
        }
    }
    void insertAt(dl_node* p, const T& data) {
        if (p == nullptr) {
            throw std::runtime_error("NULL");
        }
        p->data = data;
    }
    T index_search(const T& index) {
        dl_node* np = head;
        while (np != nullptr) {
            if (np->data == index) {
                return(np->data);
            }
            np = np->next;
        }
    }
    dl_node* getHead() {
        return head;
    }
    bool clear(const T& data)
    {
        dl_node* i = search_dl(data);
        if (i == nullptr) return false;
        else if (i == head) {
            clear_top();
            return true;
        }
        else if (i == tail) {
            clear_bot();
            return true;
        }
        else {
            dl_node* tmp = i;
            dl_node* np = tmp;
            np->prev->nast = np->next;
            np->next->prev = np->prev;
            --length;
            delete np;
            return true;
        }
    }
    void clear_all() {
        dl_node* np = head;
        dl_node* tmp = nullptr;
        while (np != nullptr) {
            clear_top();
            np = head;
        }
    }
    std::string disp() {
        if (length == 0) return "lista jest pusta\n";
        std::ostringstream disp;
        dl_node* np = head;
        while (np) {
            disp << np->data << "   ";
            np = np->next;
        }
        return disp.str();
    }

    unsigned int getLength() {
        return length;
    }
private:
    dl_node* head;
    dl_node* tail;
    unsigned length;
};