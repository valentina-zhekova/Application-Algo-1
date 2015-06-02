#include <iostream>
#include <string.h>
using namespace std;

void evaluate(char* expression) {
    int size = strlen(expression);
    bool no_point_to_go_further = false;
    int exp = 0;
    int v[3] = {0, 0, 0};
    bool b[3] = {false, false, false};
    for (int i = 0; i < size; i++) {
        switch(expression[i]) {
            case '{':
                if (!b[0] && !b[1] && !b[2])
                    b[0] = true;
                else
                    no_point_to_go_further = true;
                break;
            case '[':
                if (!b[1] && !b[2]) {
                    b[1] = true;
                    if (b[0]) {
                        v[0] += exp;
                        exp = 0;
                    }
                } else
                    no_point_to_go_further = true;
                break;
            case '(':
                if (!b[2] && (b[1] || !b[0])) {
                    b[2] = true;
                    if (b[1]) {
                        v[1] += exp;
                        exp = 0;
                    }
                } else
                    no_point_to_go_further = true;
                break;
            case '}':
                if (b[0] && !b[1] && !b[2]) {
                    b[0] = false;
                    v[0] += exp;
                    exp = 0;
                } else
                    no_point_to_go_further = true;
                break;
            case ']':
                if (b[1] && !b[2]) {
                    b[1] = false;
                    v[1] += exp;
                    exp = 0;
                    if (b[0]) {
                        v[0] += 2 * v[1];
                        v[1] = 0;
                    }
                } else
                    no_point_to_go_further = true;
                break;
            case ')':
                if (b[2]) {
                    b[2] = false;
                    v[2] += exp;
                    exp = 0;
                    if (b[1]) {
                        v[1] += 2 * v[2];
                        v[2] = 0;
                    }
                } else
                    no_point_to_go_further = true;
                break;
            default:
                exp *= 10;
                exp += expression[i] - '0';
        }
        if (no_point_to_go_further)
            break;
    }

    if (no_point_to_go_further) {
        cout << "NO" << "\n";
    } else {
        for (int i = 0; i < 3; i++) {
            if (v[i] != 0) {
                cout << v[i] << "\n";
                break;
            }
        }
    }
}

int main() {
    evaluate("[123(145)38(37)812]");
    evaluate("{125[2][(1)][3]125}");
    evaluate("[125()125()125()125]");
    evaluate("{125()125}");
    evaluate("{125[12]{125}[12]125}");

    cin.get();
    return 0;
}
