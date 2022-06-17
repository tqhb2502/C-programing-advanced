#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#include "jval.h"

// struct lưu thông tin các trạng thái
typedef struct stateDS {
    int matrix[9];
    struct stateDS *parent;
} State;

// so sánh 2 trạng thái
int compare(Jval x, Jval y) {
    State *a = (State *) jval_v(x);
    State *b = (State *) jval_v(y);

    // so sánh
    for (int i = 0; i < 9; i++) {
        if (a->matrix[i] > b->matrix[i]) {
            return 1;
        } else if (a->matrix[i] < b->matrix[i]) {
            return -1;
        }
    }

    return 0;
}

// BFS tìm trạng thái finish từ trạng thái start
void bfs(State *start, State *finish, Dllist result) {
    // JRB lưu các trạng thái đã tìm thấy
    JRB visited = make_jrb();

    // queue lưu các trạng thái trong quá trình BFS
    Dllist queue = new_dllist();
    Dllist queueNode;

    // xử lý trạng thái đầu tiên start
    dll_append(queue, new_jval_v(start));
    jrb_insert_gen(visited, new_jval_v(start), new_jval_i(1), compare);

    // BFS tìm các trạng thái
    State *u, *v;
    while (!dll_empty(queue)) {
        // lấy trạng thái từ queue
        queueNode = dll_first(queue);
        u = (State *) jval_v(queueNode->val);
        dll_delete_node(queueNode);

        // nếu trạng thái hiện tại BẰNG trạng thái finish -> ghi nhận kết quả
        if (compare(new_jval_v(u), new_jval_v(finish)) == 0) {
            dll_append(result, new_jval_v(u));

            while (u->parent != NULL) {
                u = u->parent;
                dll_append(result, new_jval_v(u));
            }

            break;
        }

        // nếu trạng thái hiện tại KHÁC trạng thái finish
        // tìm vị trí ô 0 trong bảng
        int zeroRow, zeroCol;
        for (int i = 0; i < 9; i++) {
            if (u->matrix[i] == 0) {
                zeroRow = i / 3;
                zeroCol = i - zeroRow * 3;
                break;
            }
        }

        // tạo ra các trạng thái con của trạng thái hiện tại
        int nextRow, nextCol;
        for (int i = 1; i <= 4; i++) {
            // ô 0 đi lên
            if (i == 1) {
                nextRow = zeroRow - 1;
                nextCol = zeroCol;
            }

            // ô 0 đi sang trái
            if (i == 2) {
                nextRow = zeroRow;
                nextCol = zeroCol - 1;
            }

            // ô 0 đi xuống
            if (i == 3) {
                nextRow = zeroRow + 1;
                nextCol = zeroCol;
            }

            // ô 0 đi sang phải
            if (i == 4) {
                nextRow = zeroRow;
                nextCol = zeroCol + 1;
            }

            // nếu đi ra ngoài bảng
            if (nextRow < 0 || 2 < nextRow) continue;
            if (nextCol < 0 || 2 < nextCol) continue;

            // tạo trạng thái v là con của trạng thái u hiện tại
            v = (State *) malloc(sizeof(State));
            for (int j = 0; j < 9; j++) {
                v->matrix[j] = u->matrix[j];
            }
            v->matrix[nextRow * 3 + nextCol] = 0; // đổi vị trí ô 0 với ô cần đổi
            v->matrix[zeroRow * 3 + zeroCol] = u->matrix[nextRow * 3 + nextCol]; // đổi vị trí ô 0 với ô cần đổi
            v->parent = u;

            // nếu v là trạng thái mới thì đưa vào queue
            if (jrb_find_gen(visited, new_jval_v(v), compare) == NULL) {
                dll_append(queue, new_jval_v(v));
                jrb_insert_gen(visited, new_jval_v(v), new_jval_i(1), compare); // trạng thái v đã tìm thấy
            }
        }
    }

    return;
}

int main() {
    // tạo trạng thái bắt đầu và kết thúc
    State start, finish;
    for (int i = 0; i < 9; i++) {
        start.matrix[i] = i;
        finish.matrix[i] = 8 - i;
    }
    start.parent = NULL;
    finish.parent = NULL;

    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", start.matrix[i * 3 + j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", finish.matrix[i * 3 + j]);
        }
        printf("\n");
    }*/

    // tạo dllist lưu kết quả
    Dllist result = new_dllist();

    // BFS tìm cách tạo trạng thái finish từ trạng thái start
    bfs(&start, &finish, result);

    // in kết quả
    Dllist node;
    State *cur;
    while (!dll_empty(result)) {
        node = dll_last(result);
        cur = (State *) jval_v(node->val);
        dll_delete_node(node);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", cur->matrix[i * 3 + j]);
            }
            printf("\n");
        }

        printf("\n");
    }
    return 0;
}