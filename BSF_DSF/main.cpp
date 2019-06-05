#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
using namespace std;
class Node {
public:
	Node() {};
	int x;
	int y;
	Node *f;
	Node(int X, int Y, Node *F) {
		x = X;
		y = Y;
		f = F;
	}
};
void dfs(int x, int y, int dx, int dy, int s);
void bfs(Node q, int dx, int dy);
bool move(int dir, int x, int y);
void print();
int a[10][10] = {
	0, 5, 0, 0, 0, 0, 0, 5, 0, 0,
	0, 5, 0, 5, 5, 5, 0, 0, 0, 0,
	0, 5, 0, 0, 0, 0, 0, 5, 0, 0,
	0, 5, 5, 5, 5, 5, 0, 5, 0, 0,
	0, 5, 0, 0, 0, 5, 0, 0, 0, 0,
	0, 5, 0, 5, 0, 5, 0, 5, 0, 0,
	0, 5, 0, 5, 0, 0, 0, 5, 0, 0,
	0, 5, 0, 5, 5, 5, 5, 5, 0, 0,
	0, 5, 0, 5, 0, 0, 0, 5, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
int main() {
	print();
	printf("DFS:\n");
	dfs(0, 0, 0, 2, 0);
	printf("BFS:\n");
	bfs(Node(0, 0, NULL), 0, 2);
	system("pause");
	return 0;
}

void dfs(int x, int y, int dx, int dy, int s) {
	static int mins = 999;
	if (s < mins) {
		if (x == dx && y == dy) {
			mins = s;
			print();
			return;
		}
		else {
			float s1, s2, s3, s4;
			if (x + 1 > 9 || a[x + 1][y] != 0) s1 = 999;
			else s1 = pow((x + 1 - dx), 2) + pow((y - dy), 2);
			if (y + 1 > 9 || a[x][y + 1] != 0) s2 = 999;
			else s2 = pow((x - dx), 2) + pow((y + 1 - dy), 2);
			if (x - 1 < 0 || a[x - 1][y] != 0) s3 = 999;
			else s3 = pow((x - 1 - dx), 2) + pow((y - dy), 2);
			if (y - 1 < 0 || a[x][y - 1] != 0) s4 = 999;
			else s4 = pow((x - dx), 2) + pow((y - 1 - dy), 2);
			float st[4][2] = { s1,1,s2,2,s3,3,s4,4 };
			float temp;
			for (int i = 0; i < 4; i++) {
				for (int j = 3; j > i; j--) {
					if (st[j][0] < st[j - 1][0]) {
						temp = st[j][0];
						st[j][0] = st[j - 1][0];
						st[j - 1][0] = temp;
						temp = st[j][1];
						st[j][1] = st[j - 1][1];
						st[j - 1][1] = temp;
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				if (st[i][1] == 1) {
					if (move(1, x, y)) {
						a[x][y] = 1;
						dfs(x + 1, y, dx, dy, s + 1);
						a[x][y] = 0;
					}
				}
				else if (st[i][1] == 2) {
					if (move(2, x, y)) {
						a[x][y] = 2;
						dfs(x, y + 1, dx, dy, s + 1);
						a[x][y] = 0;
					}
				}
				else if (st[i][1] == 3) {
					if (move(3, x, y)) {
						a[x][y] = 3;
						dfs(x - 1, y, dx, dy, s + 1);
						a[x][y] = 0;
					}
				}
				else if (st[i][1] == 4) {
					if (move(4, x, y)) {
						a[x][y] = 4;
						dfs(x, y - 1, dx, dy, s + 1);
						a[x][y] = 0;
					}
				}
			}	
		}
	}
}

bool move(int dir,int x,int y) {
	if (dir == 1) {
		if (x + 1 > 9 || a[x + 1][y] != 0) return false;
		else return true;
	}
	else if (dir == 2) {
		if (y + 1 > 9 || a[x][y + 1] != 0) return false;
		else return true;
	}
	else if (dir == 3) {
		if (x - 1 < 0 || a[x - 1][y] != 0) return false;
		else return true;
	}
	else if (dir == 4) {
		if (y - 1 < 0 || a[x][y - 1] != 0) return false;
		else return true;
	}
	return false;
}

void print() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (a[i][j] == 0) {
				printf("¡õ");
			}
			else if (a[i][j] == 1) {
				printf("¡ý");
			}
			else if (a[i][j] == 2) {
				printf("¡ú");
			}
			else if (a[i][j] == 3) {
				printf("¡ü");
			}
			else if (a[i][j] == 4) {
				printf("¡û");
			}
			else if (a[i][j] == 5) {
				printf("¡ö");
			}
			else if (a[i][j] == 6) {
				printf("¡õ");//¡ñ
			}
			else if (a[i][j] == 7) {
				printf("¦¯");
			}
		}
		putchar('\n');
	}
	putchar('\n');
}

void bfs(Node q, int dx, int dy) {
	int indexf, indexp;
	Node list[100];
	indexf = 0;
	indexp = 1;
	list[0] = q;
	a[list[0].x][list[0].y] = 7;
	while (indexp - indexf > 0) {
		if (move(1, list[indexf].x, list[indexf].y)) {
			list[indexp++] = Node(list[indexf].x + 1, list[indexf].y, &list[indexf]);
			if (list[indexp-1].x == dx && list[indexp-1].y == dy)break;
			a[list[indexf].x + 1][list[indexf].y] = 6;
		}
		if (move(2, list[indexf].x, list[indexf].y)) {
			list[indexp++] = Node(list[indexf].x, list[indexf].y + 1, &list[indexf]);
			if (list[indexp-1].x == dx && list[indexp-1].y == dy)break;
			a[list[indexf].x][list[indexf].y + 1] = 6;
		}
		if (move(3, list[indexf].x, list[indexf].y)) {
			list[indexp++] = Node(list[indexf].x - 1, list[indexf].y, &list[indexf]);
			if (list[indexp-1].x == dx && list[indexp-1].y == dy)break;
			a[list[indexf].x - 1][list[indexf].y] = 6;
		}
		if (move(4, list[indexf].x, list[indexf].y)) {
			list[indexp++] = Node(list[indexf].x, list[indexf].y - 1, &list[indexf]);
			if (list[indexp-1].x == dx && list[indexp-1].y == dy)break;
			a[list[indexf].x][list[indexf].y - 1] = 6;
		}
		indexf++;
	}
	if (indexp - indexf > 0) {
		Node d = list[indexf];
		while (d.f != NULL) {
			a[d.x][d.y] = 7;
			d = *d.f;
		}
		print();
	}
}
