#include <bits/stdc++.h>
using namespace std;

#define gg(i, m, n) for(i = m; i < n; i++)



class TrieNode {
    public:
        vector<TrieNode *>v;
        int color;
        TrieNode() : v(26, nullptr), color(0){}
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word, int current_color) {
        TrieNode* node = root;
        int n =  word.size();
        for(int i = 0; i< n; i++){
            if(root->v[word[i]- 'a'] == nullptr){
                node->v[word[i]-'a'] = new TrieNode();
            }
            node = node->v[word[i]-'a'];
        }
        node->color = current_color;
    }
    
    int search(string word) {
        TrieNode* node = root;
        int n = word.size();
        for(int i = 0; i < n; i++){
            if(node->v[word[i] - 'a'] == nullptr){
                return false;
            }
            node = node->v[word[i] - 'a']; 
        }
        if(node->color != -1){
            return node->color;
        }
        return -1;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for(int i = 0; i < prefix.size(); i++){
            if(node->v[prefix[i] - 'a'] == nullptr){
                return false;
            }
            node = node->v[prefix[i]- 'a'];
        }
        return true;

    }
};



/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */





class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        Trie names;
        Trie account[1001];
        int current_color = 0;
        
        vector<vector<string>>  answer;
        
        for(auto line: accounts) {
            person++;
            current_color++;
            int n = accounts.size();
            
            string s  = tolower(line[0]);
            
            
            
            set<string> ga;
            
            int color = names.search(s);
            if(color == -1) {
                names.insert(s, current_color);
            } else {
                // guardar los email
            }
            
            
            bool flag = false;
            
            int true_color
            
            int i; gg(i, 1, n) {
                string s = "";
                for(auto c: line[i]) if(c != '@' and c != '.') s += c;
                
                ga.insert(line[i]);
                
                int another_color = account[color].search(s);
                
                if(another_color != -1 and another_color != current_color) {
                    flag = true;
                    break;
                }
                
                account[color].insert(s, current_color);
                
                // extraer los email y unirlos por color
            }
            
            // megear ambos sets
            
            // return set_merge
        }
	}
};

// -------- Helpers de aserción --------
void assertEq2D(const vector<vector<string>>& got,
                const vector<vector<string>>& exp,
                const string& name) {
    if (got != exp) {
        cerr << "[FALLO] " << name << "\n";
        cerr << "Esperado:\n";
        for (auto &row : exp) {
            cerr << "  [";
            for (size_t i = 0; i < row.size(); ++i) {
                if (i) cerr << ", ";
                cerr << row[i];
            }
            cerr << "]\n";
        }
        cerr << "Obtenido:\n";
        for (auto &row : got) {
            cerr << "  [";
            for (size_t i = 0; i < row.size(); ++i) {
                if (i) cerr << ", ";
                cerr << row[i];
            }
            cerr << "]\n";
        }
        assert(false);
    }
}

int main() {
    // T1: Merge básico (dos cuentas, mismo nombre, 1 email en común)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"John","a@mail","b@mail"},
            {"John","b@mail","c@mail"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"John","a@mail","b@mail","c@mail"}
        };
        assertEq2D(got, exp, "T1: merge básico");
    }

    // T2: Sin overlap (se conservan dos grupos)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"Mary","m1@mail","m2@mail"},
            {"Mary","m3@mail"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"Mary","m1@mail","m2@mail"},
            {"Mary","m3@mail"}
        };
        assertEq2D(got, exp, "T2: sin solapamiento");
    }

    // T3: Cadena de unión (0-1-2 conectan por correos encadenados)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"Ana","e1@x","e2@x"},
            {"Ana","e2@x","e3@x"},
            {"Ana","e3@x","e4@x"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"Ana","e1@x","e2@x","e3@x","e4@x"}
        };
        assertEq2D(got, exp, "T3: cadena de unión");
    }

    // T4: Nombres distintos pero emails conectan → nombre del representante (índice 0)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"Bob","x@z","y@z"},
            {"Bob","y@z","z@z"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"Bob","x@z","y@z","z@z"}
        };
        assertEq2D(got, exp, "T4: nombre del representante");
    }

    // T5: Duplicados dentro de una misma cuenta (se ignoran en el resultado final)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"Zed","a@a","a@a","b@a"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"Zed","a@a","b@a"}
        };
        assertEq2D(got, exp, "T5: duplicados internos");
    }

    // T6: Caso mínimo (una cuenta, un correo)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"Solo","only@mail"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"Solo","only@mail"}
        };
        assertEq2D(got, exp, "T6: mínimo");
    }

    // T7: Varios componentes sin unión (orden por índice de cuenta)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"A","a@x"},
            {"B","b@x"},
            {"C","c@x"},
            {"D","d@x"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"A","a@x"},
            {"B","b@x"},
            {"C","c@x"},
            {"D","d@x"}
        };
        assertEq2D(got, exp, "T7: múltiples componentes sin unión");
    }

    // T8: Dos grupos separados (0-1 y 2-3), cada uno con su representante
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"G1","g1@a","g1@b"},
            {"G1","g1@b","g1@c"},
            {"G2","g2@a","g2@b"},
            {"G2","g2@b","g2@c"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"G1","g1@a","g1@b","g1@c"},
            {"G2","g2@a","g2@b","g2@c"}
        };
        assertEq2D(got, exp, "T8: dos grupos separados");
    }

    // T9: Sensibilidad a mayúsculas en emails (A@x != a@x)
    {
        Solution sol;
        vector<vector<string>> acc = {
            {"Case","A@x","a@x"}
        };
        auto got = sol.accountsMerge(acc);
        vector<vector<string>> exp = {
            {"Case","A@x","a@x"} // sort lex: "A@x" < "a@x"
        };
        assertEq2D(got, exp, "T9: case-sensitive en emails");
    }

    cout << "¡Todos los tests pasaron! \n";
    return 0;
}
